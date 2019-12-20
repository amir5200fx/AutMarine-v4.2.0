#include <SizeMap2d_UniformCurvesSizeMapTool.hxx>

#include <Entity_Box2dTools.hxx>
#include <Entity_Triangulation2d.hxx>
#include <Geom_BalancedPrQuadTree.hxx>
#include <GeoMesh_BackGroundMesh2d.hxx>
#include <GeoMesh_BackGroundMesh2dTools.hxx>
#include <Merge_Items2d.hxx>
#include <SizeMap2d_UniSize.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh2d_Curve.hxx>
#include <Mesh2d_SourcePoint.hxx>
#include <Mesh2d_SourcePointTools.hxx>
#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_Plane.hxx>
#include <TColEntity_HAry1dOfBox2d.hxx>
#include <TColCad2d_HAry1dOfEdgeOnPlane.hxx>
#include <TColMesh2d_HAry1dOfSourcePoint.hxx>
#include <TColMesh2d_HBasicQueueOfSourcePoint.hxx>

static const Standard_Integer DEFAULT_BUCKET_SIZE = 4;
static const Standard_Integer DEFAULT_LAPLACIAN_SMOOTHING = 5;
static const Standard_Real DEFAULT_LAPLACIAN_SMOOTHING_FACTOR = 0.1;

using namespace AutLib;
using namespace MeshLib;
using namespace CadLib;
using namespace GeoLib;

AutLib::MeshLib::SizeMap2d_UniformCurvesSizeMapTool::SizeMap2d_UniformCurvesSizeMapTool
(
	const Global_Handle(Mesh_ReferenceValues) theReference, 
	const Global_Handle(M_CAD Cad2d_Plane)thePlane
)
	: SizeMap2d_BoundarySizeMapTool(theReference, thePlane)
	, theBucketSize_(DEFAULT_BUCKET_SIZE)
{
}

AutLib::MeshLib::SizeMap2d_UniformCurvesSizeMapTool::~SizeMap2d_UniformCurvesSizeMapTool()
{
}

void AutLib::MeshLib::SizeMap2d_UniformCurvesSizeMapTool::SetBucketSize(const Standard_Integer BucketSize)
{
	theBucketSize_ = BucketSize;
}

void AutLib::MeshLib::SizeMap2d_UniformCurvesSizeMapTool::CreateSizeMap()
{
	TColCad2d_HAry1dOfEdgeOnPlane Edges;
	SizeMap2d_BoundarySizeMapTool::RetrieveCurvesTo(Edges);

	CreateSizeMap(Edges);
}

void AutLib::MeshLib::SizeMap2d_UniformCurvesSizeMapTool::CreateSizeMap(const TColCad2d_HAry1dOfEdgeOnPlane & theEdges)
{
	if (theEdges.IsEmpty()) { return; }

	//! Retrieve Element size
	Standard_Real ElementSize = SizeMap2d_BoundarySizeMapTool::RetrieveTargetSize();

	SizeMap2d_UniSize SizeMap(ElementSize);
	TColMesh2d_HBasicQueueOfSourcePoint QSources;
	forThose
	(
		Index,
		0,
		MaxIndexOf(theEdges)
	)
	{
		Debug_Null_Pointer(theEdges[Index]);
		Debug_Null_Pointer(theEdges[Index]->Curve());

		Mesh2d_Curve MeshCurve(SizeMap, theEdges[Index]->Curve());
		MeshCurve.Perform();

		Debug_If_Condition_Message(NOT MeshCurve.IsDone(), " Curve not discretized");

		Get_Const_Object(Points) = MeshCurve.Chain().Coords();
		forThose(I, 0, MaxIndexOf(Points))
			QSources.EnQueue(new Mesh2d_SourcePoint(Points[I], ElementSize));
	}
	TColMesh2d_HAry1dOfSourcePoint Sources;
	QSources.RetrieveTo(Sources);

	Merge_Items2d<Global_Handle(Mesh2d_SourcePoint)> Merge(&Sources, &Mesh2d_SourcePointTools::CoordinateOf);
	Merge.Perform();

	Debug_If_Condition_Message(NOT Merge.IsDone(), " Merging Items is not performed");
	TColMesh2d_HAry1dOfSourcePoint CompactItems = Merge.CompactItems();

	Entity_Box2d Box = thePlane_->BoundingBox();

	Geom_BalancedPrQuadTree<Global_Handle(Mesh2d_SourcePoint)> Tree;
	Tree.SetCoordinateFunction(&Mesh2d_SourcePointTools::CoordinateOf);
	Tree.SetRegion(Box.OffsetBox(0.15*Box.Diameter()));
	Tree.SetBucketSize(theBucketSize_);
	Tree.Insert(CompactItems);
	Tree.PostBalancing();

	TColEntity_HAry1dOfBox2d Boxes;
	Tree.RetrieveTo(Boxes);

	Entity_Triangulation2d Triangulation;
	Entity_Box2dTools::Triangulation(Boxes, &Triangulation);

	theBackMesh_ = new GeoMesh_BackGroundMesh2d;
	theBackMesh_->Mesh().Construct(Triangulation);
	theBackMesh_->InitiateCurrentElement();
	theBackMesh_->SetBoundingBox(Tree.BoundingBox());

	Try_Exception_Handle_Exit(GeoMesh_BackGroundMesh2dTools::SetSourcesToMesh(CompactItems, theReference_->BaseSize(), *theBackMesh_));

	theBackMesh_->HvCorrection(Mesh_VariationRate::Rate(theValues_.BoundaryGrowthRate()));
	theBackMesh_->LaplacianSmoothing(DEFAULT_LAPLACIAN_SMOOTHING, DEFAULT_LAPLACIAN_SMOOTHING_FACTOR);

	FreeMemory(Sources);
}