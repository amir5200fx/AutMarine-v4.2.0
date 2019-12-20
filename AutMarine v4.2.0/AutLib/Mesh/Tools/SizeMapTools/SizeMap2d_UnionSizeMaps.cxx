#include <SizeMap2d_UnionSizeMaps.hxx>

#include <Entity_Box2d.hxx>
#include <Entity_Box2dTools.hxx>
#include <Entity_Triangulation2d.hxx>
#include <GeoMesh_BackGroundMesh2d.hxx>
#include <GeoMesh_BackGroundMesh2dTools.hxx>
#include <SubDivide_BalancedQuadTree.hxx>
#include <SizeMap2d_SizeMapTool.hxx>
#include <Mesh2d_SourcePoint.hxx>
#include <TColEntity_HAry1dOfBox2d.hxx>
#include <TColMesh2d_HAry1dOfSourcePoint.hxx>
#include <TColGeoMesh_HAry1dOfBackGroundMesh2d.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;

static const Standard_Real DEFAULT_TOLERANCE = 0.35;
static const Standard_Integer DEFAULT_MIN_SUBDIVIDE = 2;
static const Standard_Integer DEFAULT_MAX_SUBDIVIDE = 5;

static const Standard_Integer DEFAULT_LAPLACIAN_SMOOTHING = 3;
static const Standard_Real DEFAULT_LAPLACIAN_SMOOTHING_FACTOR = 0.1;

#define TOLERANCE(X1, X2)  ABS(X1 - X2) / MAX(ABS(X1), ABS(X2))

AutLib::MeshLib::SizeMap2d_UnionSizeMaps::SizeMap2d_UnionSizeMaps()
	: theTolerance_(DEFAULT_TOLERANCE)
	, theMinSubdivision_(DEFAULT_MIN_SUBDIVIDE)
	, theMaxSubdivision_(DEFAULT_MAX_SUBDIVIDE)
	, theBackMesh_(NULL)
	, IsDone_(Standard_False)
{
}

AutLib::MeshLib::SizeMap2d_UnionSizeMaps::~SizeMap2d_UnionSizeMaps()
{
}

void AutLib::MeshLib::SizeMap2d_UnionSizeMaps::SetTolerance(const Standard_Real theTolerance)
{
	theTolerance_ = theTolerance;
}

void AutLib::MeshLib::SizeMap2d_UnionSizeMaps::SetMinSubdivide(const Standard_Integer theValue)
{
	theMinSubdivision_ = theValue;
}

void AutLib::MeshLib::SizeMap2d_UnionSizeMaps::SetMaxSubdivide(const Standard_Integer theValue)
{
	theMaxSubdivision_ = theValue;
}

namespace AutLib
{
	namespace MeshLib
	{

		class QuadTreeObject
		{

		public:

			QuadTreeObject(const TColGeoMesh_HAry1dOfBackGroundMesh2d& theSizeMaps, const Standard_Real theTolerance);

			const TColGeoMesh_HAry1dOfBackGroundMesh2d& theSizeMaps_;

			Standard_Real theTolerance_;

			Standard_Real ElementSize(const Geom_Pnt2d& Coord) const;

			Standard_Boolean Subdivide(const Entity_Box2d& Box) const;


		};

		inline QuadTreeObject::QuadTreeObject(const TColGeoMesh_HAry1dOfBackGroundMesh2d & theSizeMaps, const Standard_Real theTolerance)
			: theSizeMaps_(theSizeMaps)
			, theTolerance_(theTolerance)
		{
		}

		inline Standard_Real QuadTreeObject::ElementSize(const Geom_Pnt2d & Coord) const
		{
			Standard_Real MinSize = RealLast();
			forThose
			(
				Index,
				0, 
				MaxIndexOf(theSizeMaps_)
			)
			{
				Debug_Null_Pointer(theSizeMaps_[Index]);
				Standard_Real Size = theSizeMaps_[Index]->ElementSize(Coord);

				if (Size < MinSize) MinSize = Size;
			}
			return MinSize;
		}

		inline Standard_Boolean QuadTreeObject::Subdivide(const Entity_Box2d & Box) const
		{
			const Standard_Real H1 = ElementSize(Box.GetSwPoint());
			const Standard_Real H2 = ElementSize(Box.GetSePoint());
			const Standard_Real H3 = ElementSize(Box.GetNePoint());
			const Standard_Real H4 = ElementSize(Box.GetNwPoint());

			const Standard_Real Tolerance = theTolerance_;

			if (TOLERANCE(H1, H2) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H1, H3) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H1, H4) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H2, H3) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H2, H4) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H3, H4) > Tolerance)
				return Standard_True;

			return Standard_False;
		}

		class QuadTreeObjectTool
		{

		public:

			static Standard_Boolean Subdivide(const Entity_Box2d& theBox, const Global_Handle(QuadTreeObject) theObject);
		};

		inline Standard_Boolean QuadTreeObjectTool::Subdivide(const Entity_Box2d & theBox, const Global_Handle(QuadTreeObject) theObjectPtr)
		{
			Get_Const_Object(Object) = *theObjectPtr;

			if (Object.Subdivide(theBox.SwQuarter()))
				return Standard_True;

			if (Object.Subdivide(theBox.SeQuarter()))
				return Standard_True;

			if (Object.Subdivide(theBox.NwQuarter()))
				return Standard_True;

			if (Object.Subdivide(theBox.NeQuarter()))
				return Standard_True;

			return Standard_False;
		}

		Entity_Box2d RetrieveBoundingBoxOf(const TColGeoMesh_HAry1dOfBackGroundMesh2d& theSizeMaps)
		{
			if (theSizeMaps.IsEmpty()) return Entity_Box2d(0, 0, 0, 0);
			
			Debug_Null_Pointer(theSizeMaps.First());
			Debug_Null_Pointer(theSizeMaps.First()->BoundingBox());

			Entity_Box2d Box = *theSizeMaps.First()->BoundingBox();
			forThose
			(
				Index,
				1, 
				MaxIndexOf(theSizeMaps)
			)
			{
				Debug_Null_Pointer(theSizeMaps[Index]);
				Debug_Null_Pointer(theSizeMaps[Index]->BoundingBox());

				Box = Entity_Box2dTools::Intersect(Box, *theSizeMaps[Index]->BoundingBox());
			}
			MOVE(Box);
		}
	}
}

void AutLib::MeshLib::SizeMap2d_UnionSizeMaps::Perform()
{
	// Retrieve maps 
	TColGeoMesh_HAry1dOfBackGroundMesh2d SizeMaps;
	theSizeMaps_.RetrieveTo(SizeMaps);

	if (SizeMaps.IsEmpty()) { return; }
	if (SizeMaps.Size() EQUAL 1)
	{
		Debug_Null_Pointer(SizeMaps[0]);

		theBackMesh_ = SizeMaps[0];
		return;
	}

	Entity_Box2d BoundingBox = RetrieveBoundingBoxOf(SizeMaps);
	//BoundingBox.Exapnd(0.05*BoundingBox.Diameter());

	// Generate a quadtree to adapt to the sources. The object of the tree
	// has two kind of maps: Boundary map and feature map
	QuadTreeObject Object(SizeMaps, theTolerance_);

	SubDivide_BalancedQuadTree<QuadTreeObject> Tree;

	// Set bounding box of the Plane to the tree
	Tree.SetDomain(BoundingBox);

	Tree.SetMinLevel(theMinSubdivision_);
	Tree.SetMaxLevel(theMaxSubdivision_);

	Tree.SetObject(&Object);
	Tree.SetSubDivider(&QuadTreeObjectTool::Subdivide);

	Tree.Init();
	Tree.Perform();

	// Retrieve Boxes of the leaves
	TColEntity_HAry1dOfBox2d Boxes;
	Tree.RetrieveTo(Boxes);

	// Triangulation of the boxes to generate a background mesh
	Entity_Triangulation2d Triangulation;
	Entity_Box2dTools::Triangulation(Boxes, &Triangulation);

	/*Get_Const_Object(Points) = Triangulation.Points();

	TColMesh2d_HAry1dOfSourcePoint Sources(Points.Size());
	forThose(Index, 0, MaxIndexOf(Points))
		Sources[Index] = new Mesh2d_SourcePoint(Points[Index], Object.ElementSize(Points[Index]));*/

	theBackMesh_ = new GeoMesh_BackGroundMesh2d;
	theBackMesh_->Mesh().Construct(Triangulation);
	theBackMesh_->InitiateCurrentElement();
	theBackMesh_->SetBoundingBox(BoundingBox);

	Get_Object(Sources) = theBackMesh_->Sources();
	Get_Const_Object(Nodes) = theBackMesh_->Mesh().NodesSequence();
	Sources.Resize(Nodes.Size());
	forThose(Index, 0, MaxIndexOf(Sources))
	{
		Sources[Index] = Object.ElementSize(Nodes[Index]->Coord());
	}

	//Try_Exception_Handle_Exit(GeoMesh_BackGroundMesh2dTools::SetSourcesToMesh(Sources, 1.0, *theBackMesh_));

	theBackMesh_->LaplacianSmoothing(DEFAULT_LAPLACIAN_SMOOTHING, DEFAULT_LAPLACIAN_SMOOTHING_FACTOR);

	//FreeMemory(Sources);

	IsDone_ = Standard_True;
}

void AutLib::MeshLib::SizeMap2d_UnionSizeMaps::ExportBackMeshToPlt(fstream & File) const
{
	if (NOT IsDone_) { return; }

	Debug_Null_Pointer(theBackMesh_);

	theBackMesh_->ExportToPlt(File);
}