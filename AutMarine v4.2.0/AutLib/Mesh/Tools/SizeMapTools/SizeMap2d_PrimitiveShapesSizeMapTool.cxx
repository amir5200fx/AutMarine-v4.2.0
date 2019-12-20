#include <SizeMap2d_PrimitiveShapesSizeMapTool.hxx>

#include <Entity_Metric2.hxx>
#include <Entity_Box2dTools.hxx>
#include <Entity_Triangulation2d.hxx>
#include <GeoMesh_TriangleMesh2d.hxx>
#include <GeoMesh_BackGroundMesh2d.hxx>
#include <Geom_Triangulation.hxx>
#include <SubDivide_BalancedQuadTree.hxx>
#include <Merge_Items2d.hxx>
#include <Mesh2d_Domain.hxx>
#include <Mesh2d_SourcePoint.hxx>
#include <Mesh2d_SourcePointTools.hxx>
#include <SizeMap2d_UniSize.hxx>
#include <Geom_BalancedPrQuadTree.hxx>
#include <Cad2d_Plane.hxx>
#include <TColEntity_HAry1dOfTriangulation2d.hxx>
#include <TColGeoMesh_HAry1dOfTriangleMesh2d.hxx>
#include <TColGeom_BasicQueueOfPnt2d.hxx>
#include <TColEntity_HAry1dOfElement2d.hxx>
#include <TColCad2d_HAry1dOfPlane.hxx>
#include <TColEntity_HAry1dOfStaticChain2d.hxx>
#include <TColMesh2d_HAry1dOfDomain.hxx>
#include <TColMesh2d_HBasicQueueOfSourcePoint.hxx>
#include <TColMesh2d_HAry1dOfSourcePoint.hxx>
#include <TColEntity_HAry1dOfBox2d.hxx>
#include <TColEntity_HBasicQueueOfNode2d.hxx>

static const Standard_Integer DEFAULT_BUCKET_SIZE = 2;
static const Standard_Integer DEFAULT_LAPLACIAN_SMOOTHING = 3;
static const Standard_Real DEFAULT_LAPLACIAN_SMOOTHING_FACTOR = 0.1;

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

AutLib::MeshLib::SizeMap2d_PrimitiveShapesSizeMapTool::SizeMap2d_PrimitiveShapesSizeMapTool
(
	const Global_Handle(Mesh_ReferenceValues) theReference,
	const Global_Handle(M_CAD Cad2d_Plane)thePlane
)
	: SizeMap2d_SizeMapTool(theReference, thePlane)
	, theBucketSize_(DEFAULT_BUCKET_SIZE)
	, theMetric_(NULL)
{
}

AutLib::MeshLib::SizeMap2d_PrimitiveShapesSizeMapTool::~SizeMap2d_PrimitiveShapesSizeMapTool()
{
	//FreePointer(theBackMesh_);
	FreePointer(theMetric_);
}

const TColEntity_HAry1dOfNode2d & AutLib::MeshLib::SizeMap2d_PrimitiveShapesSizeMapTool::InnerNodes() const
{
	return theInnerNodes_;
}

const TColEntity_HAry1dOfNode2d & AutLib::MeshLib::SizeMap2d_PrimitiveShapesSizeMapTool::OutterNodes() const
{
	return theOutterNodes_;
}

const Global_Handle(M_GEO Entity_Metric2) AutLib::MeshLib::SizeMap2d_PrimitiveShapesSizeMapTool::Metric() const
{
	return theMetric_;
}

void AutLib::MeshLib::SizeMap2d_PrimitiveShapesSizeMapTool::ImportShape(const Global_Handle(M_CAD Cad2d_Plane) theShape)
{
	theShapes_.EnQueue((Global_Handle(M_CAD Cad2d_Plane))theShape);
}

void AutLib::MeshLib::SizeMap2d_PrimitiveShapesSizeMapTool::SetMetric(const M_GEO Entity_Metric2 & theMetric)
{
	theMetric_ = new Entity_Metric2(theMetric);
}

namespace AutLib
{
	namespace MeshLib
	{
		inline static Standard_Real ElementSize(const Geom_Pnt2d& theCoord, TColEntity_HAry1dOfElement2d& theStarts, const TColGeoMesh_HAry1dOfTriangleMesh2d& theMeshes, const Standard_Real theBase, const Standard_Real theSize, Standard_Boolean& Inside)
		{
			forThose
			(
				Index,
				0,
				MaxIndexOf(theMeshes)
			)
			{
				Debug_Null_Pointer(theMeshes[Index]);

				Global_Handle(Entity_Element2d) Element = theMeshes[Index]->TriangleLocation(theStarts[Index], theCoord);
				if (Element)
				{
					theStarts[Index] = Element;
					Inside = Standard_True;
					return theSize;
				}
			}
			Inside = Standard_False;
			return theBase;
		}

		static void SetSourcesToBackMesh(GeoMesh_BackGroundMesh2d& theMesh, const TColMesh2d_HAry1dOfDomain& theDomains, const Standard_Real theBase, const Standard_Real theSize, TColEntity_HBasicQueueOfNode2d& QInners, TColEntity_HBasicQueueOfNode2d& QOutters)
		{
			Get_Object(Sources) = theMesh.Sources();
			Get_Const_Object(Mesh) = theMesh.Mesh();
			Get_Const_Object(Nodes) = Mesh.NodesSequence();

			Sources.Resize(Mesh.NbNodes());
			Sources.Init(theBase);

			TColEntity_HAry1dOfElement2d Starts(theDomains.Size());
			TColGeoMesh_HAry1dOfTriangleMesh2d Triangulated(theDomains.Size());
			forThose
			(
				Index,
				0,
				MaxIndexOf(Triangulated)
			)
			{
				Entity_Triangulation2d Triangulation;
				Geom_Triangulation::DelaunayTriangulation(theDomains[Index]->Merged().Coords(), &Triangulation);

				Triangulated[Index] = new GeoMesh_TriangleMesh2d;
				Triangulated[Index]->Construct(Triangulation);

				Starts[Index] = Triangulated[Index]->FirstElement();
			}

			forThose(Index, 0, MaxIndexOf(Sources))
			{
				Standard_Boolean Inside;
				Sources[Index] = ElementSize(Nodes[Index]->Coord(), Starts, Triangulated, theBase, theSize, Inside);

				if (Inside) QInners.EnQueue(Nodes[Index]);
				else QOutters.EnQueue(Nodes[Index]);
			}

			FreeMemory(Triangulated);
		}
	}
}

void AutLib::MeshLib::SizeMap2d_PrimitiveShapesSizeMapTool::CreateSizeMap()
{
	TColCad2d_HAry1dOfPlane Shapes;
	theShapes_.RetrieveTo(Shapes);

	if (Shapes.IsEmpty()) { return; }

	Standard_Real ElementSize = GetTargetSurfaceSize();
	SizeMap2d_UniSize Uniform(ElementSize);

	TColMesh2d_HAry1dOfDomain Domains(Shapes.Size());
	Domains.Init(0);
	Entity_Box2d Union = Shapes[0]->BoundingBox();
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Domains)
	)
	{
		Domains[Index] = new Mesh2d_Domain(Uniform, Shapes[Index], 1.0E-6);
		Union = Entity_Box2dTools::Union(Union, Shapes[Index]->BoundingBox());
		Try_Exception_Handle_Exit(Domains[Index]->Perform());
	}
	
	TColMesh2d_HBasicQueueOfSourcePoint QSources;
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Domains)
	)
	{
		Debug_Null_Pointer(Domains[Index]);

		Get_Const_Object(Points) = Domains[Index]->Merged().Coords();
		forThose(I, 0, MaxIndexOf(Points))
			QSources.EnQueue(new Mesh2d_SourcePoint(Points[I], ElementSize));
	}
	
	TColMesh2d_HAry1dOfSourcePoint Sources;
	QSources.RetrieveTo(Sources);

	Merge_Items2d<Global_Handle(Mesh2d_SourcePoint)> Merge(&Sources, &Mesh2d_SourcePointTools::CoordinateOf);
	Merge.Perform();

	Debug_If_Condition_Message(NOT Merge.IsDone(), " Merging Items is not performed");

	TColMesh2d_HAry1dOfSourcePoint CompactItems = Merge.CompactItems();

	Entity_Box2d Box = Entity_Box2dTools::Union(thePlane_->BoundingBox(), Union);

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

	TColEntity_HBasicQueueOfNode2d QInners, QOutters;
	SetSourcesToBackMesh(*theBackMesh_, Domains, GetBaseSize(), GetTargetSurfaceSize(), QInners, QOutters);
	QInners.RetrieveTo(theInnerNodes_);
	QOutters.RetrieveTo(theOutterNodes_);

	theBackMesh_->HvCorrection(GetBoundaryGrowthRate());

	//theBackMesh_->LaplacianSmoothing(DEFAULT_LAPLACIAN_SMOOTHING, DEFAULT_LAPLACIAN_SMOOTHING_FACTOR);

	FreeMemory(Sources);
	FreeMemory(Domains);
}