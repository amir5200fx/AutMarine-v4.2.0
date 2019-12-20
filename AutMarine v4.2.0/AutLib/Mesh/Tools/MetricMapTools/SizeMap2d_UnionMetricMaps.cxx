#include <SizeMap2d_UnionMetricMaps.hxx>

#include <Entity_Metric1.hxx>
#include <Entity_Box2d.hxx>
#include <Entity_Box2dTools.hxx>
#include <Entity_Triangulation2d.hxx>
#include <Geometry_Distance.hxx>
#include <SubDivide_BalancedQuadTree.hxx>
#include <GeoMesh_BackGroundMetric2d.hxx>
#include <TColGeoMesh_HAry1dOfBackGroundMetric2d.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;

static const Standard_Real DEFAULT_TOLERANCE = 0.35;
static const Standard_Integer DEFAULT_MIN_SUBDIVIDE = 2;
static const Standard_Integer DEFAULT_MAX_SUBDIVIDE = 5;

static const Standard_Integer DEFAULT_LAPLACIAN_SMOOTHING = 3;
static const Standard_Real DEFAULT_LAPLACIAN_SMOOTHING_FACTOR = 0.1;

#define TOLERANCE(X1, X2)  ABS(X1 - X2) / MAX(ABS(X1), ABS(X2))

AutLib::MeshLib::SizeMap2d_UnionMetricMaps::SizeMap2d_UnionMetricMaps()
	: theTolerance_(DEFAULT_TOLERANCE)
	, theMinSubdivision_(DEFAULT_MIN_SUBDIVIDE)
	, theMaxSubdivision_(DEFAULT_MAX_SUBDIVIDE)
	, theBackMetric_(NULL)
	, IsDone_(Standard_False)
{
}

AutLib::MeshLib::SizeMap2d_UnionMetricMaps::~SizeMap2d_UnionMetricMaps()
{
}

void AutLib::MeshLib::SizeMap2d_UnionMetricMaps::SetTolerance(const Standard_Real theTolerance)
{
	theTolerance_ = theTolerance;
}

void AutLib::MeshLib::SizeMap2d_UnionMetricMaps::SetMinSubdivide(const Standard_Integer theValue)
{
	theMinSubdivision_ = theValue;
}

void AutLib::MeshLib::SizeMap2d_UnionMetricMaps::SetMaxSubdivide(const Standard_Integer theValue)
{
	theMaxSubdivision_ = theValue;
}

void AutLib::MeshLib::SizeMap2d_UnionMetricMaps::SetIntersection(GeoLib::Entity_Metric1(*theInterSection)(const M_GEO Entity_Metric1 &, const M_GEO Entity_Metric1 &))
{
	InterSection = theInterSection;
}

namespace AutLib
{
	namespace MeshLib
	{

		class UnionMetricQuadTreeObject
		{

		public:

			UnionMetricQuadTreeObject(const TColGeoMesh_HAry1dOfBackGroundMetric2d& theMetricMaps, const Standard_Real theTolerance);

			const TColGeoMesh_HAry1dOfBackGroundMetric2d& theMetricMaps_;

			Entity_Metric1(*InterSection_)(const Entity_Metric1&, const Entity_Metric1&);

			Standard_Real theTolerance_;

			Entity_Metric1 MetricAt(const Geom_Pnt2d& Coord) const;

			Standard_Boolean Subdivide(const Entity_Box2d& Box) const;
		};

		inline Entity_Metric1 AutLib::MeshLib::UnionMetricQuadTreeObject::MetricAt(const Geom_Pnt2d & Coord) const
		{
			Entity_Metric1 M = theMetricMaps_.First()->MetricAt(Coord);
			forThose(Index, 1, MaxIndexOf(theMetricMaps_))
			{
				M = InterSection_(M, theMetricMaps_[Index]->MetricAt(Coord));
			}
			MOVE(M);
		}

		inline Standard_Boolean AutLib::MeshLib::UnionMetricQuadTreeObject::Subdivide(const Entity_Box2d & Box) const
		{
			Geom_Pnt2d P0 = Box.GetSwPoint();
			Geom_Pnt2d P1 = Box.GetSePoint();
			Geom_Pnt2d P2 = Box.GetNePoint();
			Geom_Pnt2d P3 = Box.GetNwPoint();

			const Entity_Metric1 M0 = MetricAt(P0);
			const Entity_Metric1 M1 = MetricAt(P1);
			const Entity_Metric1 M2 = MetricAt(P2);
			const Entity_Metric1 M3 = MetricAt(P3);

			const Standard_Real Tolerance = theTolerance_;

			Standard_Real D01 = Geometry_Distance::Distance(P0, P1, M0);
			Standard_Real D10 = Geometry_Distance::Distance(P1, P0, M1);

			Standard_Real D02 = Geometry_Distance::Distance(P0, P2, M0);
			Standard_Real D20 = Geometry_Distance::Distance(P2, P0, M2);

			Standard_Real D03 = Geometry_Distance::Distance(P0, P3, M0);
			Standard_Real D30 = Geometry_Distance::Distance(P3, P0, M3);

			Standard_Real D12 = Geometry_Distance::Distance(P1, P2, M1);
			Standard_Real D21 = Geometry_Distance::Distance(P2, P1, M2);

			Standard_Real D13 = Geometry_Distance::Distance(P1, P3, M1);
			Standard_Real D31 = Geometry_Distance::Distance(P3, P1, M3);

			Standard_Real D23 = Geometry_Distance::Distance(P2, P3, M2);
			Standard_Real D32 = Geometry_Distance::Distance(P3, P2, M3);

			if (TOLERANCE(D01, D10) > Tolerance) return Standard_True;
			if (TOLERANCE(D02, D20) > Tolerance) return Standard_True;
			if (TOLERANCE(D03, D30) > Tolerance) return Standard_True;
			if (TOLERANCE(D12, D21) > Tolerance) return Standard_True;
			if (TOLERANCE(D13, D31) > Tolerance) return Standard_True;
			if (TOLERANCE(D23, D32) > Tolerance) return Standard_True;

			return Standard_False;
		}

		class UnionMetricQuadTreeObjectTools
		{

		public:

			static Standard_Boolean Subdivide(const Entity_Box2d& theBox, const Global_Handle(UnionMetricQuadTreeObject) theObject);
		};

		inline Standard_Boolean AutLib::MeshLib::UnionMetricQuadTreeObjectTools::Subdivide(const Entity_Box2d & theBox, const Global_Handle(UnionMetricQuadTreeObject) theObjectPtr)
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

		Entity_Box2d RetrieveBoundingBoxOf(const TColGeoMesh_HAry1dOfBackGroundMetric2d& theSizeMaps)
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

AutLib::MeshLib::UnionMetricQuadTreeObject::UnionMetricQuadTreeObject
(
	const TColGeoMesh_HAry1dOfBackGroundMetric2d & theMetricMaps,
	const Standard_Real theTolerance
)
	: theMetricMaps_(theMetricMaps)
	, theTolerance_(theTolerance)
{
}

void AutLib::MeshLib::SizeMap2d_UnionMetricMaps::Perform()
{
	TColGeoMesh_HAry1dOfBackGroundMetric2d MetricMaps;
	theMetricMaps_.RetrieveTo(MetricMaps);

	if (MetricMaps.IsEmpty()) { return; }
	/*if (MetricMaps.Size() EQUAL 1)
	{
		Debug_Null_Pointer(MetricMaps[0]);

		theBackMetric_ = MetricMaps[0];
		IsDone_ = Standard_True;
		return;
	}*/

	Entity_Box2d BoundingBox = RetrieveBoundingBoxOf(MetricMaps);
	//BoundingBox.Exapnd(0.05*BoundingBox.Diameter());

	// Generate a quadtree to adapt to the sources. The object of the tree
	// has two kind of maps: Boundary map and feature map
	UnionMetricQuadTreeObject Object(MetricMaps, theTolerance_);
	Object.InterSection_ = InterSection;

	SubDivide_BalancedQuadTree<UnionMetricQuadTreeObject> Tree;

	// Set bounding box of the Plane to the tree
	Tree.SetDomain(BoundingBox);

	Tree.SetMinLevel(theMinSubdivision_);
	Tree.SetMaxLevel(theMaxSubdivision_);

	Tree.SetObject(&Object);
	Tree.SetSubDivider(&UnionMetricQuadTreeObjectTools::Subdivide);

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

	theBackMetric_ = new GeoMesh_BackGroundMetric2d;
	theBackMetric_->Mesh().Construct(Triangulation);
	theBackMetric_->InitiateCurrentElement();
	theBackMetric_->SetBoundingBox(BoundingBox);

	Get_Object(Sources) = theBackMetric_->Sources();
	Get_Const_Object(Nodes) = theBackMetric_->Mesh().NodesSequence();
	Sources.Resize(Nodes.Size());
	forThose(Index, 0, MaxIndexOf(Sources))
	{
		Sources[Index] = Object.MetricAt(Nodes[Index]->Coord());
	}

	//Try_Exception_Handle_Exit(GeoMesh_BackGroundMesh2dTools::SetSourcesToMesh(Sources, 1.0, *theBackMesh_));

	//theBackMetric_->LaplacianSmoothing(DEFAULT_LAPLACIAN_SMOOTHING, DEFAULT_LAPLACIAN_SMOOTHING_FACTOR);

	//FreeMemory(Sources);

	IsDone_ = Standard_True;
}