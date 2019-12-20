#include <SizeMap3d_UnionSizeMaps.hxx>

#include <Entity_Box3d.hxx>
#include <Entity_Box3dTools.hxx>
#include <Entity_Tetrahedralization.hxx>
#include <GeoMesh_BackGroundMesh3d.hxx>
#include <GeoMesh_BackGroundMesh3dTools.hxx>
#include <SubDivide_BalancedOctree.hxx>
#include <SizeMap3d_SizeMapTool.hxx>
#include <Mesh3d_SourcePoint.hxx>
#include <TColEntity_HAry1dOfBox3d.hxx>
#include <TColMesh3d_HAry1dOfSourcePoint.hxx>
#include <TColGeoMesh_HAry1dOfBackGroundMesh3d.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;

static const Standard_Real DEFAULT_TOLERANCE = 0.2;
static const Standard_Integer DEFAULT_MIN_SUBDIVIDE = 2;
static const Standard_Integer DEFAULT_MAX_SUBDIVIDE = 9;

static const Standard_Integer DEFAULT_LAPLACIAN_SMOOTHING = 3;
static const Standard_Real DEFAULT_LAPLACIAN_SMOOTHING_FACTOR = 0.1;

#define TOLERANCE(X1, X2)  ABS(X1 - X2) / MAX(ABS(X1), ABS(X2))

AutLib::MeshLib::SizeMap3d_UnionSizeMaps::SizeMap3d_UnionSizeMaps()
	: theTolerance_(DEFAULT_TOLERANCE)
	, theMinSubdivision_(DEFAULT_MIN_SUBDIVIDE)
	, theMaxSubdivision_(DEFAULT_MAX_SUBDIVIDE)
	, theBackMesh_(NULL)
	, IsDone_(Standard_False)
{
}

AutLib::MeshLib::SizeMap3d_UnionSizeMaps::~SizeMap3d_UnionSizeMaps()
{
}

void AutLib::MeshLib::SizeMap3d_UnionSizeMaps::SetTolerance(const Standard_Real theTolerance)
{
	theTolerance_ = theTolerance;
}

void AutLib::MeshLib::SizeMap3d_UnionSizeMaps::SetMinSubdivide(const Standard_Integer theValue)
{
	theMinSubdivision_ = theValue;
}

void AutLib::MeshLib::SizeMap3d_UnionSizeMaps::SetMaxSubdivide(const Standard_Integer theValue)
{
	theMaxSubdivision_ = theValue;
}

namespace AutLib
{
	namespace MeshLib
	{

		TColGeom_Ary1dOfPnt3d GetCoords(const Standard_Integer theN, const Geom_Pnt3d& theP1, const Geom_Pnt3d& theP2)
		{
			TColGeom_Ary1dOfPnt3d Pts(theN + 1);

			Standard_Real dx = 1.0 / (Standard_Real)theN;
			Geom_Pnt3d dP = (theP2 - theP1);
			forThose(Index, 0, theN)
				Pts[Index] = theP1 + dx*dP;
			MOVE(Pts);
		}

		class QuadTreeObjectSizeMap3d
		{

		public:

			QuadTreeObjectSizeMap3d(const TColGeoMesh_HAry1dOfBackGroundMesh3d& theSizeMaps, const Standard_Real theTolerance);

			const TColGeoMesh_HAry1dOfBackGroundMesh3d& theSizeMaps_;

			Standard_Real theTolerance_;

			Standard_Real ElementSize(const Geom_Pnt3d& Coord) const;

			Standard_Boolean Subdivide(const Entity_Box3d& Box) const;

			Standard_Real CaptureMinSize(const TColGeom_Ary1dOfPnt3d& theQ) const;

			Standard_Real CaptureMinSize(const Entity_Box3d& Box) const;

		};

		inline QuadTreeObjectSizeMap3d::QuadTreeObjectSizeMap3d(const TColGeoMesh_HAry1dOfBackGroundMesh3d & theSizeMaps, const Standard_Real theTolerance)
			: theSizeMaps_(theSizeMaps)
			, theTolerance_(theTolerance)
		{
		}

		inline Standard_Real QuadTreeObjectSizeMap3d::ElementSize(const Geom_Pnt3d & Coord) const
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

		inline Standard_Boolean QuadTreeObjectSizeMap3d::Subdivide(const Entity_Box3d & Box) const
		{
			const Geom_Pnt3d P1 = Box.Bwd_SwCorner();
			const Geom_Pnt3d P2 = Box.Bwd_SeCorner();
			const Geom_Pnt3d P3 = Box.Bwd_NeCorner();
			const Geom_Pnt3d P4 = Box.Bwd_NwCorner();
			const Geom_Pnt3d P5 = Box.Fwd_SwCorner();
			const Geom_Pnt3d P6 = Box.Fwd_SeCorner();
			const Geom_Pnt3d P7 = Box.Fwd_NeCorner();
			const Geom_Pnt3d P8 = Box.Fwd_NwCorner();

			/*const Geom_Pnt3d PBm = (Standard_Real)0.25*(P1 + P2 + P3 + P4);
			const Geom_Pnt3d PFm = (Standard_Real)0.25*(P5 + P6 + P7 + P8);*/

			const Standard_Real H1 = ElementSize(P1);
			const Standard_Real H2 = ElementSize(P2);
			const Standard_Real H3 = ElementSize(P3);
			const Standard_Real H4 = ElementSize(P4);
			const Standard_Real H5 = ElementSize(P5);
			const Standard_Real H6 = ElementSize(P6);
			const Standard_Real H7 = ElementSize(P7);
			const Standard_Real H8 = ElementSize(P8);

			TColGeom_Ary1dOfPnt3d Q1 = GetCoords(5, P1, P7);
			TColGeom_Ary1dOfPnt3d Q2 = GetCoords(5, P2, P8);
			TColGeom_Ary1dOfPnt3d Q3 = GetCoords(5, P3, P5);
			TColGeom_Ary1dOfPnt3d Q4 = GetCoords(5, P4, P6);

			Standard_Real Min1 = CaptureMinSize(Q1);
			Standard_Real Min2 = CaptureMinSize(Q2);
			Standard_Real Min3 = CaptureMinSize(Q3);
			Standard_Real Min4 = CaptureMinSize(Q4);

			Standard_Real MinSize = Min1;
			if (Min2 < MinSize) MinSize = Min2;
			if (Min3 < MinSize) MinSize = Min3;
			if (Min4 < MinSize) MinSize = Min4;

			const Standard_Real Tolerance = theTolerance_;

			if (TOLERANCE(H1, MinSize) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H2, MinSize) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H3, MinSize) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H4, MinSize) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H5, MinSize) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H6, MinSize) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H7, MinSize) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H8, MinSize) > Tolerance)
				return Standard_True;

			return Standard_False;
		}

		inline Standard_Real AutLib::MeshLib::QuadTreeObjectSizeMap3d::CaptureMinSize(const TColGeom_Ary1dOfPnt3d & theQ) const
		{
			Standard_Real MinSize = RealLast();
			forThose
			(
				Index,
				0, 
				MaxIndexOf(theQ)
			)
			{
				Standard_Real Size = ElementSize(theQ[Index]);
				if (Size < MinSize) MinSize = Size;
			}
			return MinSize;
		}

		inline Standard_Real AutLib::MeshLib::QuadTreeObjectSizeMap3d::CaptureMinSize(const Entity_Box3d & Box) const
		{
			const Geom_Pnt3d P1 = Box.Bwd_SwCorner();
			const Geom_Pnt3d P2 = Box.Bwd_SeCorner();
			const Geom_Pnt3d P3 = Box.Bwd_NeCorner();
			const Geom_Pnt3d P4 = Box.Bwd_NwCorner();
			const Geom_Pnt3d P5 = Box.Fwd_SwCorner();
			const Geom_Pnt3d P6 = Box.Fwd_SeCorner();
			const Geom_Pnt3d P7 = Box.Fwd_NeCorner();
			const Geom_Pnt3d P8 = Box.Fwd_NwCorner();

			/*const Geom_Pnt3d PBm = (Standard_Real)0.25*(P1 + P2 + P3 + P4);
			const Geom_Pnt3d PFm = (Standard_Real)0.25*(P5 + P6 + P7 + P8);*/

			const Standard_Real H1 = ElementSize(P1);
			const Standard_Real H2 = ElementSize(P2);
			const Standard_Real H3 = ElementSize(P3);
			const Standard_Real H4 = ElementSize(P4);
			const Standard_Real H5 = ElementSize(P5);
			const Standard_Real H6 = ElementSize(P6);
			const Standard_Real H7 = ElementSize(P7);
			const Standard_Real H8 = ElementSize(P8);

			TColGeom_Ary1dOfPnt3d Q1 = GetCoords(5, P1, P7);
			TColGeom_Ary1dOfPnt3d Q2 = GetCoords(5, P2, P8);
			TColGeom_Ary1dOfPnt3d Q3 = GetCoords(5, P3, P5);
			TColGeom_Ary1dOfPnt3d Q4 = GetCoords(5, P4, P6);

			Standard_Real Min1 = CaptureMinSize(Q1);
			Standard_Real Min2 = CaptureMinSize(Q2);
			Standard_Real Min3 = CaptureMinSize(Q3);
			Standard_Real Min4 = CaptureMinSize(Q4);

			Standard_Real MinSize = Min1;
			if (Min2 < MinSize) MinSize = Min2;
			if (Min3 < MinSize) MinSize = Min3;
			if (Min4 < MinSize) MinSize = Min4;

			return MinSize;
		}

		class QuadTreeObjectTool
		{

		public:

			static Standard_Boolean Subdivide(const Entity_Box3d& theBox, const Global_Handle(QuadTreeObjectSizeMap3d) theObject);
		};

		inline Standard_Boolean QuadTreeObjectTool::Subdivide(const Entity_Box3d & theBox, const Global_Handle(QuadTreeObjectSizeMap3d) theObjectPtr)
		{
			Get_Const_Object(Object) = *theObjectPtr;

			if (Object.Subdivide(theBox.Bwd_SwOctant()))
				return Standard_True;

			if (Object.Subdivide(theBox.Bwd_SeOctant()))
				return Standard_True;

			if (Object.Subdivide(theBox.Bwd_NeOctant()))
				return Standard_True;

			if (Object.Subdivide(theBox.Bwd_NwOctant()))
				return Standard_True;

			if (Object.Subdivide(theBox.Fwd_SwOctant()))
				return Standard_True;

			if (Object.Subdivide(theBox.Fwd_SeOctant()))
				return Standard_True;

			if (Object.Subdivide(theBox.Fwd_NeOctant()))
				return Standard_True;

			if (Object.Subdivide(theBox.Fwd_NwOctant()))
				return Standard_True;

			return Standard_False;
		}

		Entity_Box3d RetrieveBoundingBoxOf(const TColGeoMesh_HAry1dOfBackGroundMesh3d& theSizeMaps)
		{
			if (theSizeMaps.IsEmpty()) return Entity_Box3d(0, 0, 0, 0, 0, 0);

			Debug_Null_Pointer(theSizeMaps.First());
			Debug_Null_Pointer(theSizeMaps.First()->BoundingBox());

			Entity_Box3d Box = *theSizeMaps.First()->BoundingBox();
			forThose
			(
				Index,
				1,
				MaxIndexOf(theSizeMaps)
			)
			{
				Debug_Null_Pointer(theSizeMaps[Index]);
				Debug_Null_Pointer(theSizeMaps[Index]->BoundingBox());

				Box = Entity_Box3dTools::Intersect(Box, *theSizeMaps[Index]->BoundingBox());
			}
			MOVE(Box);
		}
	}
}

void AutLib::MeshLib::SizeMap3d_UnionSizeMaps::Perform()
{
	// Retrieve maps 
	TColGeoMesh_HAry1dOfBackGroundMesh3d SizeMaps;
	theSizeMaps_.RetrieveTo(SizeMaps);

	if (SizeMaps.IsEmpty()) { return; }
	if (SizeMaps.Size() EQUAL 1)
	{
		Debug_Null_Pointer(SizeMaps[0]);

		theBackMesh_ = SizeMaps[0];
		return;
	}

	Entity_Box3d BoundingBox = ::RetrieveBoundingBoxOf(SizeMaps);
	//BoundingBox.Exapnd(0.05*BoundingBox.Diameter());

	// Generate a quadtree to adapt to the sources. The object of the tree
	// has two kind of maps: Boundary map and feature map
	QuadTreeObjectSizeMap3d Object(SizeMaps, theTolerance_);

	SubDivide_BalancedOctree<QuadTreeObjectSizeMap3d> Tree;

	// Set bounding box of the Plane to the tree
	Tree.SetDomain(BoundingBox);

	Tree.SetMinLevel(theMinSubdivision_);
	Tree.SetMaxLevel(theMaxSubdivision_);

	Tree.SetObject(&Object);
	Tree.SetSubDivider(&QuadTreeObjectTool::Subdivide);

	Tree.Init();
	Tree.SetMinLevel(theMaxSubdivision_);
	Tree.Perform();
	Tree.PostBalancing();
	
	// Retrieve Boxes of the leaves
	TColEntity_HAry1dOfBox3d Boxes;
	Tree.RetrieveTo(Boxes);

	// Triangulation of the boxes to generate a background mesh
	Entity_Tetrahedralization Triangulation;
	Entity_Box3dTools::Triangulation(Boxes, &Triangulation);

	/*Get_Const_Object(Points) = Triangulation.Points();

	TColMesh2d_HAry1dOfSourcePoint Sources(Points.Size());
	forThose(Index, 0, MaxIndexOf(Points))
	Sources[Index] = new Mesh2d_SourcePoint(Points[Index], Object.ElementSize(Points[Index]));*/

	/*TColMesh3d_HAry1dOfSourcePoint Sources(Boxes.Size());
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Sources)
	)
	{
		Debug_Null_Pointer(Boxes[Index]);
		Sources[Index] = new Mesh3d_SourcePoint(Boxes[Index]->CalcCentre(), Object.CaptureMinSize(*Boxes[Index]));
	}*/

	theBackMesh_ = new GeoMesh_BackGroundMesh3d;
	theBackMesh_->Mesh().Construct(Triangulation);
	theBackMesh_->InitiateCurrentElement();
	theBackMesh_->SetBoundingBox(BoundingBox);

	Get_Object(Sources1) = theBackMesh_->Sources();
	Get_Const_Object(Nodes) = theBackMesh_->Mesh().NodesSequence();
	Sources1.Resize(Nodes.Size());
	forThose(Index, 0, MaxIndexOf(Sources1))
	{
		Sources1[Index] = Object.ElementSize(Nodes[Index]->Coord());
	}

	//Try_Exception_Handle_Exit(GeoMesh_BackGroundMesh3dTools::SetSourcesToMesh(Sources, 1.0, *theBackMesh_));

	theBackMesh_->HvCorrection(0.25, 3);
	/*Open_OutputFile_TecPlot(Plot, "test");
	theBackMesh_->ExportToPlt(Plot);
	exit(1);*/
	//theBackMesh_->LaplacianSmoothing(DEFAULT_LAPLACIAN_SMOOTHING, DEFAULT_LAPLACIAN_SMOOTHING_FACTOR);

	//FreeMemory(Sources);

	IsDone_ = Standard_True;
}

void AutLib::MeshLib::SizeMap3d_UnionSizeMaps::ExportBackMeshToPlt(fstream & File) const
{
	if (NOT IsDone_) { return; }

	Debug_Null_Pointer(theBackMesh_);

	theBackMesh_->ExportToPlt(File);
}