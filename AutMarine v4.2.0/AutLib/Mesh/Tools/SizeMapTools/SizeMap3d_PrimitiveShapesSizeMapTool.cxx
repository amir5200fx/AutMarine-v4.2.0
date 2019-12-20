#include <SizeMap3d_PrimitiveShapesSizeMapTool.hxx>

#include <Geom_BalancedPrOctTree.hxx>
#include <Merge_Items3d.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_SolidTools.hxx>
#include <Entity_Box3d.hxx>
#include <Entity_Box3dTools.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <SizeMap3d_PrimitiveShapeSource.hxx>
#include <Mesh3d_SolidMesher.hxx>
#include <Mesh3d_SourcePoint.hxx>
#include <Mesh3d_SourcePointTools.hxx>
#include <TColSizeMap3d_HAry1dOfPrimitiveShapeSource.hxx>
#include <TColMesh3d_HAry1dOfSolidMesher.hxx>
#include <TColMesh3d_HBasicQueueOfSourcePoint.hxx>
#include <TColMesh3d_HAry1dOfSourcePoint.hxx>
#include <TColGeoMesh_HAry1dOfTetrahedronMesh.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace CadLib;
using namespace MeshLib;

static const Standard_Integer DEFAULT_BUCKET_SIZE = 8;

AutLib::MeshLib::SizeMap3d_PrimitiveShapesSizeMapTool::SizeMap3d_PrimitiveShapesSizeMapTool
(
	const Global_Handle(Mesh_ReferenceValues) theReference, 
	const Global_Handle(M_CAD Cad3d_Solid)theSolid
)
	: SizeMap3d_SizeMapTool(theReference, theSolid)
	, theBucketSize_(DEFAULT_BUCKET_SIZE)
{
}

AutLib::MeshLib::SizeMap3d_PrimitiveShapesSizeMapTool::~SizeMap3d_PrimitiveShapesSizeMapTool()
{
}

void AutLib::MeshLib::SizeMap3d_PrimitiveShapesSizeMapTool::SetBucketSize(const Standard_Integer BucketSize)
{
	theBucketSize_ = BucketSize;
}

void AutLib::MeshLib::SizeMap3d_PrimitiveShapesSizeMapTool::ImportSource(const Global_Handle(SizeMap3d_PrimitiveShapeSource) theShape)
{
	theShapes_.EnQueue((Global_Handle(SizeMap3d_PrimitiveShapeSource))theShape);
}

namespace AutLib
{
	namespace MeshLib
	{

		inline static Standard_Real ElementSize(const Geom_Pnt3d& theCoord, const TColSizeMap3d_HAry1dOfPrimitiveShapeSource& theShapes, const Standard_Real theBase)
		{
			forThose
			(
				Index, 
				0, 
				MaxIndexOf(theShapes)
			)
			{
				Debug_Null_Pointer(theShapes[Index]);

				Standard_Boolean Sense;
				Standard_Real Size = theShapes[Index]->ElementSize(theCoord, Sense);
				if (Sense) return Size;
			}
			return theBase;
		}

		static void SetSourcesToBackMesh(GeoMesh_BackGroundMesh3d& theMesh, const TColSizeMap3d_HAry1dOfPrimitiveShapeSource& theShapes, const Standard_Real theBase)
		{
			Get_Object(Sources) = theMesh.Sources();
			Get_Const_Object(Nodes) = theMesh.Mesh().NodesSequence();

			Sources.Resize(Nodes.Size());
			forThose(Index, 0, MaxIndexOf(Sources))
			{
				Sources[Index] = ElementSize(Nodes[Index]->Coord(), theShapes, theBase);
			}
		}
	}
}

void AutLib::MeshLib::SizeMap3d_PrimitiveShapesSizeMapTool::CreateSizeMap()
{
	TColSizeMap3d_HAry1dOfPrimitiveShapeSource Shapes;
	theShapes_.RetrieveTo(Shapes);

	if (Shapes.IsEmpty()) { return; }
	Standard_Real ElementSize, dummy;
	SpecifyValues(ElementSize, dummy, dummy);
	
	forThose
	(
		Index,
		0,
		MaxIndexOf(Shapes)
	)
	{
		Debug_Null_Pointer(Shapes[Index]);
		Shapes[Index]->SetSize(ElementSize);
		Shapes[Index]->Construct();
	}

	SizeMap3d_UniSize Uniform(2*ElementSize);

	TColMesh3d_HAry1dOfSolidMesher Domains(Shapes.Size());
	Domains.Init(0);
	Entity_Box3d Union = Shapes[0]->BoundingBox();
	forThose
	(
		Index,
		0,
		MaxIndexOf(Domains)
	)
	{
		Cad3d_Solid Solid;
		Solid.Make(Cad3d_SolidTools::GetSurfaces(Shapes[Index]->Shape()));
		Domains[Index] = new Mesh3d_SolidMesher(Uniform, Solid);
		Domains[Index]->ApplySmoothing(Standard_False);
		Domains[Index]->ApplyOptimization(Standard_False);
		Try_Exception_Handle_Exit(Domains[Index]->Perform());
	}

	TColMesh3d_HBasicQueueOfSourcePoint QSources;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Domains)
	)
	{
		Debug_Null_Pointer(Domains[Index]);

		Get_Const_Object(Points) = Domains[Index]->Merged().Points();
		forThose(I, 0, MaxIndexOf(Points))
			QSources.EnQueue(new Mesh3d_SourcePoint(Points[I], ElementSize));
	}

	TColMesh3d_HAry1dOfSourcePoint Sources;
	QSources.RetrieveTo(Sources);

	Merge_Items3d<Global_Handle(Mesh3d_SourcePoint)> Merge(&Sources, &Mesh3d_SourcePointTools::CoordinateOf);
	Merge.Perform();

	Debug_If_Condition_Message(NOT Merge.IsDone(), " Merging Items is not performed");

	TColMesh3d_HAry1dOfSourcePoint CompactItems = Merge.CompactItems();

	Entity_Box3d Box = Entity_Box3dTools::Union(theSolid_->BoundingBox(), Union);

	Geom_BalancedPrOctTree<Global_Handle(Mesh3d_SourcePoint)> Tree;

	Tree.SetCoordinateFunction(&Mesh3d_SourcePointTools::CoordinateOf);
	Tree.SetRegion(Box.OffsetBox(0.1*Box.Diameter()));
	Tree.SetBucketSize(theBucketSize_);

	Tree.Insert(CompactItems);
	Tree.PostBalancing();
	
	TColEntity_HAry1dOfBox3d Boxes;
	Tree.RetrieveTo(Boxes);

	Entity_Tetrahedralization Triangulation;
	Entity_Box3dTools::Triangulation(Boxes, &Triangulation);

	theBackMesh_ = new GeoMesh_BackGroundMesh3d;
	theBackMesh_->Mesh().Construct(Triangulation);
	theBackMesh_->InitiateCurrentElement();
	theBackMesh_->SetBoundingBox(Tree.BoundingBox());

	::SetSourcesToBackMesh(*theBackMesh_, Shapes, GetBaseSize());

	theBackMesh_->HvCorrection(GetBoundaryGrowthRate());
}