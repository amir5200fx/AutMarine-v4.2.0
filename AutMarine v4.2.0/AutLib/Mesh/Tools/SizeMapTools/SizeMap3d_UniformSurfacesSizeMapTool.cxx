#include <SizeMap3d_UniformSurfacesSizeMapTool.hxx>

#include <Geom_BalancedPrOctTree.hxx>
#include <Merge_Items3d.hxx>
#include <Entity_Box2d.hxx>
#include <Entity_Box2dTools.hxx>
#include <Entity_Box3dTools.hxx>
#include <Entity_Tetrahedralization.hxx>
#include <Entity_Triangulation2d.hxx>
#include <GeoMesh_TriangleMesh2d.hxx>
#include <GeoMesh_BackGroundMesh3d.hxx>
#include <GeoMesh_BackGroundMesh3dTools.hxx>
#include <SubDivide_QuadTree.hxx>
#include <Cad3d_SurfaceOnSolid.hxx>
#include <Cad3d_BlockEntityOnSolid.hxx>
#include <Cad3d_Solid.hxx>
#include <Mesh3d_SourcePoint.hxx>
#include <Mesh3d_SourcePointTools.hxx>
#include <Mesh_VariationRate.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <TColMesh3d_HBasicQueueOfSourcePoint.hxx>
#include <TColCad3d_HBasicQueueOfEntityOnSolid.hxx>
#include <TColCad3d_HAry1dOfSurfaceOnSolid.hxx>
#include <TColMesh3d_HAry1dOfSourcePoint.hxx>

static const Standard_Integer DEFAULT_BUCKET_SIZE = 8;
static const Standard_Integer DEFAULT_MIN_SUBDIVIDE = 2;
static const Standard_Integer DEFAULT_MAX_SUBDIVIDE = 4;
static const Standard_Integer DEFAULT_LAPLACIAN_SMOOTHING = 3;
static const Standard_Real DEFAULT_LAPLACIAN_SMOOTHING_FACTOR = 0.1;

using namespace AutLib;
using namespace MeshLib;
using namespace CadLib;
using namespace GeoLib;

#include <Geom_Surface.hxx>

AutLib::MeshLib::SizeMap3d_UniformSurfacesSizeMapTool::SizeMap3d_UniformSurfacesSizeMapTool
(
	const Global_Handle(Mesh_ReferenceValues) theReference,
	const Global_Handle(M_CAD Cad3d_Solid) theSolid
)
	: SizeMap3d_BoundarySizeMapTool(theReference, theSolid)
	, theBucketSize_(DEFAULT_BUCKET_SIZE)
{
}

AutLib::MeshLib::SizeMap3d_UniformSurfacesSizeMapTool::~SizeMap3d_UniformSurfacesSizeMapTool()
{
}

void AutLib::MeshLib::SizeMap3d_UniformSurfacesSizeMapTool::SetBucketSize(const Standard_Integer BucketSize)
{
	theBucketSize_ = BucketSize;
}

namespace AutLib
{
	namespace MeshLib
	{

		class SubDivide_QuadTreeObject
		{

			friend class SubDivide_QuadTreeObjectTools;

		private:

			const Geom_Surface& theGeometry_;

			Standard_Real theSize_;

		public:

			SubDivide_QuadTreeObject(const Geom_Surface& theGeometry, const Standard_Real theSize)
				: theGeometry_(theGeometry)
				, theSize_(theSize)
			{}
		};

		class SubDivide_QuadTreeObjectTools
		{

		public:

			static Standard_Boolean doSubdivide(const Entity_Box2d& theRegion, const Global_Handle(SubDivide_QuadTreeObject) theObject);
		};

		inline Standard_Boolean AutLib::MeshLib::SubDivide_QuadTreeObjectTools::doSubdivide(const Entity_Box2d & theRegion, const Global_Handle(SubDivide_QuadTreeObject) theObject)
		{
			Geom_Pnt2d p0 = theRegion.GetSwPoint();
			Geom_Pnt2d p1 = theRegion.GetSePoint();
			Geom_Pnt2d p2 = theRegion.GetNePoint();
			Geom_Pnt2d p3 = theRegion.GetNwPoint();

			Geom_Pnt2d centre = theRegion.CalcCentre();

			Geom_Pnt3d Centre = theObject->theGeometry_.Value(centre.X(), centre.Y());

			Standard_Real Length1 = Distance(theObject->theGeometry_.Value(p0.X(), p0.Y()), Centre) + Distance(theObject->theGeometry_.Value(p2.X(), p2.Y()), Centre);
			if (Length1 > theObject->theSize_) { return Standard_True; }

			Standard_Real Length2 = Distance(theObject->theGeometry_.Value(p1.X(), p1.Y()), Centre) + Distance(theObject->theGeometry_.Value(p3.X(), p3.Y()), Centre);
			if (Length2 > theObject->theSize_) { return Standard_True; }

			return Standard_False;
		}

		static void GetSources(const Cad3d_SurfaceOnSolid& theSurface, TColMesh3d_HBasicQueueOfSourcePoint& theSources, const Standard_Real theSize)
		{
			SubDivide_QuadTreeObject Object(*theSurface.Geometry().get(), theSize);

			SubDivide_QuadTree<SubDivide_QuadTreeObject> Tree;
			Tree.SetDomain(theSurface.ParametricBoundingBox());
			Tree.SetObject(&Object);
			Tree.SetSubDivider(&SubDivide_QuadTreeObjectTools::doSubdivide);

			Tree.SetMinLevel(DEFAULT_MIN_SUBDIVIDE);
			Tree.SetMaxLevel(DEFAULT_MAX_SUBDIVIDE);

			Tree.Init();
			Tree.Perform();

			TColEntity_HAry1dOfBox2d Boxes;
			Tree.RetrieveTo(Boxes);

			Get_Const_Object(Geometry) = *theSurface.Geometry().get();

			Entity_Triangulation2d Triangulation;
			Entity_Box2dTools::Triangulation(Boxes, &Triangulation);
			//theSurface.GetParametricTriangulation(Triangulation);

			GeoMesh_TriangleMesh2d TriangleMesh;
			TriangleMesh.Construct(Triangulation);

			Global_Handle(Entity_Element2d) Start = TriangleMesh.ElementsSequence().First();

			forThose
			(
				Index,
				0,
				MaxIndexOf(Boxes)
			)
			{
				Debug_Null_Pointer(Boxes[Index]);

				Geom_Pnt2d Pt = Boxes[Index]->CalcCentre();

				Global_Handle(Entity_Element2d) Element = TriangleMesh.TriangleLocation(Start, Pt);

				if (Element)
				{
					theSources.EnQueue(new Mesh3d_SourcePoint(Geometry.Value(Pt.X(), Pt.Y()), theSize));
					Start = Element;
				}
			}
		}

		static void GetSources(const TColCad3d_HAry1dOfEntityOnSolid& theSurfaces, TColMesh3d_HAry1dOfSourcePoint& theSources, const Standard_Real theSize)
		{
			TColMesh3d_HBasicQueueOfSourcePoint QSources;
			forThose
			(
				Index,
				0,
				MaxIndexOf(theSurfaces)
			)
			{
				Debug_Null_Pointer(theSurfaces[Index]);
				Debug_Null_Pointer(Global_DownCast(Cad3d_SurfaceOnSolid, theSurfaces[Index]));

				Get_Const_Object(Surface) = *Global_DownCast(Cad3d_SurfaceOnSolid, theSurfaces[Index]);

				TColMesh3d_HBasicQueueOfSourcePoint QCurrentSources;
				GetSources(Surface, QCurrentSources, theSize);

				QSources.EnQueue(QCurrentSources);
			}
			QSources.RetrieveTo(theSources);
		}
	}
}

void AutLib::MeshLib::SizeMap3d_UniformSurfacesSizeMapTool::CreateSizeMap()
{
	TColCad3d_HAry1dOfEntityOnSolid Surfaces;
	RetrieveEntitiesTo(Surfaces);

	if (Surfaces.IsEmpty()) { return; }
	Standard_Real ElementSize, dummy;
	SpecifyValues(ElementSize, dummy, dummy);

	SizeMap3d_UniSize SizeMap(ElementSize);

	// Get Sources from the surfaces
	TColMesh3d_HAry1dOfSourcePoint Sources;
	::GetSources(Surfaces, Sources, SizeMap.BaseSize());

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
	theBackMesh_->SetBoundingBox(Tree.BoundingBox());

	Try_Exception_Handle_Exit(GeoMesh_BackGroundMesh3dTools::SetSourcesToMesh(CompactItems, theReference_->BaseSize(), *theBackMesh_));

	theBackMesh_->HvCorrection(Mesh_VariationRate::Rate(theValues_.BoundaryGrowthRate()), 5);

	//theBackMesh_->LaplacianSmoothing(DEFAULT_LAPLACIAN_SMOOTHING, DEFAULT_LAPLACIAN_SMOOTHING_FACTOR);

	FreeMemory(Sources);
}

void AutLib::MeshLib::SizeMap3d_UniformSurfacesSizeMapTool::RetrieveEntitiesTo(TColCad3d_HAry1dOfEntityOnSolid & theEntities) const
{
	TColStd_Ary1dOfString Patches;
	theEntityPatches_.RetrieveTo(Patches);

	TColCad3d_HBasicQueueOfEntityOnSolid QEntities;

	if (NOT theSolid_->Surfaces()) { THROW_STANDARD_EXCEPTION(" The solid has no Surface"); }

	Get_Const_Object(Entities) = *theSolid_->Surfaces();
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