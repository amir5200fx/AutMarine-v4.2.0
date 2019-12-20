#include <SizeMap3d_UniformCurvesSizeMapTool.hxx>

#include <Entity_Tetrahedralization.hxx>
#include <Entity_Box3dTools.hxx>
#include <Geom_BalancedPrOctTree.hxx>
#include <GeoMesh_BackGroundMesh3d.hxx>
#include <GeoMesh_BackGroundMesh3dTools.hxx>
#include <Merge_Items3d.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_CurveOnSurface.hxx>
#include <Cad3d_EdgeOnSolid.hxx>
#include <Cad3d_PairedOnSolid.hxx>
#include <Cad3d_BlockEntityOnSolid.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <Mesh3d_Curve.hxx>
#include <Mesh3d_SourcePoint.hxx>
#include <Mesh3d_SourcePointTools.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh_VariationRate.hxx>
#include <TColCad3d_HBasicQueueOfEntityOnSolid.hxx>
#include <TColMesh3d_HBasicQueueOfSourcePoint.hxx>
#include <TColMesh3d_HAry1dOfSourcePoint.hxx>

static const Standard_Integer DEFAULT_BUCKET_SIZE = 4;
static const Standard_Integer DEFAULT_LAPLACIAN_SMOOTHING = 3;
static const Standard_Real DEFAULT_LAPLACIAN_SMOOTHING_FACTOR = 0.1;

using namespace AutLib;
using namespace MeshLib;
using namespace CadLib;
using namespace GeoLib;

AutLib::MeshLib::SizeMap3d_UniformCurvesSizeMapTool::SizeMap3d_UniformCurvesSizeMapTool
(
	const Global_Handle(Mesh_ReferenceValues) theReference,
	const Global_Handle(M_CAD Cad3d_Solid) theSolid
)
	: SizeMap3d_BoundarySizeMapTool(theReference, theSolid)
	, theBucketSize_(DEFAULT_BUCKET_SIZE)
{
}

AutLib::MeshLib::SizeMap3d_UniformCurvesSizeMapTool::~SizeMap3d_UniformCurvesSizeMapTool()
{
}

void AutLib::MeshLib::SizeMap3d_UniformCurvesSizeMapTool::SetBucketSize(const Standard_Integer BucketSize)
{
	theBucketSize_ = BucketSize;
}

void AutLib::MeshLib::SizeMap3d_UniformCurvesSizeMapTool::CreateSizeMap()
{
	TColCad3d_HAry1dOfEntityOnSolid Entities;
	RetrieveEntitiesTo(Entities);

	if (NOT Entities.Size()) { return; }

	//! Retrieve Element size
	Standard_Real ElementSize, dummy;
	SpecifyValues(ElementSize, dummy, dummy);

	SizeMap3d_UniSize SizeMap(ElementSize);

	TColMesh3d_HBasicQueueOfSourcePoint QSources;
	forThose(Index, 0, MaxIndexOf(Entities))
	{
		Global_Handle(Cad3d_PairedOnSolid) Curve = Global_DownCast(Cad3d_PairedOnSolid, Entities.Value(Index));
		Debug_Null_Pointer(Curve);
		Debug_Null_Pointer(Curve->Edge0());
		Debug_Null_Pointer(Curve->Edge0()->CurveOnSurface());

		Mesh3d_Curve MeshCurve(SizeMap, *Curve->Edge0()->CurveOnSurface());
		MeshCurve.Perform();

		Debug_If_Condition_Message(NOT MeshCurve.IsDone(), " Curve not discretized");

		Get_Const_Object(Points) = MeshCurve.Chain().Coords();

		forThose(I, 0, MaxIndexOf(Points))
			QSources.EnQueue(new Mesh3d_SourcePoint(Points[I], ElementSize));
	}
	TColMesh3d_HAry1dOfSourcePoint Sources;
	QSources.RetrieveTo(Sources);

	Merge_Items3d<Global_Handle(Mesh3d_SourcePoint)> Merge(&Sources, &Mesh3d_SourcePointTools::CoordinateOf);
	Merge.Perform();

	Debug_If_Condition_Message(NOT Merge.IsDone(), " Merging Items is not performed");

	TColMesh3d_HAry1dOfSourcePoint CompactItems = Merge.CompactItems();

	Geom_BalancedPrOctTree<Global_Handle(Mesh3d_SourcePoint)> Tree;

	Tree.SetCoordinateFunction(&Mesh3d_SourcePointTools::CoordinateOf);
	Tree.SetRegion(theSolid_->BoundingBox().OffsetBox(0.1*theSolid_->BoundingBox().Diameter()));
	Tree.SetBucketSize(theBucketSize_);

	Tree.Insert(CompactItems);
	Tree.PostBalancing();

	TColEntity_HAry1dOfBox3d Boxes;
	Tree.RetrieveTo(Boxes);

	Entity_Tetrahedralization Tetrahedralization;
	Entity_Box3dTools::Triangulation(Boxes, &Tetrahedralization);

	theBackMesh_ = new GeoMesh_BackGroundMesh3d;
	theBackMesh_->Mesh().Construct(Tetrahedralization);
	theBackMesh_->InitiateCurrentElement();

	Try_Exception_Handle_Exit(GeoMesh_BackGroundMesh3dTools::SetSourcesToMesh(CompactItems, theReference_->BaseSize(), *theBackMesh_));

	theBackMesh_->HvCorrection(Mesh_VariationRate::Rate(theValues_.BoundaryGrowthRate()));

	theBackMesh_->LaplacianSmoothing(DEFAULT_LAPLACIAN_SMOOTHING, DEFAULT_LAPLACIAN_SMOOTHING_FACTOR);

	FreeMemory(Sources);
}

void AutLib::MeshLib::SizeMap3d_UniformCurvesSizeMapTool::RetrieveEntitiesTo(TColCad3d_HAry1dOfEntityOnSolid & theEntities) const
{
	TColStd_Ary1dOfString Patches;
	theEntityPatches_.RetrieveTo(Patches);

	TColCad3d_HBasicQueueOfEntityOnSolid QEntities;

	if (NOT theSolid_->PairedEdges()) { THROW_STANDARD_EXCEPTION(" The solid has no Paired Edge"); }

	Get_Const_Object(Entities) = *theSolid_->PairedEdges();
	forThose
	(
		Index,
		0,
		MaxIndexOf(Patches)
	)
	{
		Global_Handle(Cad3d_BlockEntityOnSolid) Patch = Entities.GetBlockEntity(Patches[Index]);

		if (NOT Patch) { THROW_STANDARD_EXCEPTION(" Invalid Data"); }

		Patch->RetrieveTo(QEntities);
	}
	QEntities.RetrieveTo(theEntities);
}