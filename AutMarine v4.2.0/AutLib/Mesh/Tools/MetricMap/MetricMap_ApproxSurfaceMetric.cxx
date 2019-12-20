#include <MetricMap_ApproxSurfaceMetric.hxx>

#include <Entity_Box2d.hxx>
#include <Entity_Box2dTools.hxx>
#include <Entity_Metric1.hxx>
#include <Entity_Triangulation2d.hxx>
#include <Entity_StaticChain2d.hxx>
#include <Entity_StaticChain2dTools.hxx>
#include <Entity_Polygon2d.hxx>
#include <Mesh3d_SizeMap.hxx>
#include <Geometry_Distance.hxx>
#include <SubDivide_QuadTree.hxx>
#include <Cad3d_SurfaceOnSolid.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColGeom_BasicQueueOfPnt2d.hxx>

typedef M_GEO Entity_Metric1 Metric;
typedef M_GEO Entity_Box2d Box2d;

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

#include <Geom_Surface.hxx>

#define TOLERANCE(X1, X2)  ABS(X1 - X2) / MAX(ABS(X1), ABS(X2))
#define GET_DOMAIN_NAME theSurfaceName_

static const Standard_Real DEFAULT_TOLERANCE = 0.3;
static const Standard_Real DEFAULT_DEGENERACY = 1.0E-6;
static const Standard_Integer DEFAULT_MIN_LEVELS = 2;
static const Standard_Integer DEFAULT_MAX_LEVELS = 5;

AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::MetricMap_ApproxSurfaceMetric(const M_CAD Cad3d_SurfaceOnSolid& theSurface)
	: MetricMap_SurfaceMetricMap(theSurface)
	, theDegeneracy_(DEFAULT_DEGENERACY)
	, theTolerance_(DEFAULT_TOLERANCE)
	, theNb_MIN_LEVELS_(DEFAULT_MIN_LEVELS)
	, theNb_MAX_LEVELS_(DEFAULT_MAX_LEVELS)
{
}

AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::~MetricMap_ApproxSurfaceMetric()
{
}

namespace AutLib
{
	namespace MeshLib
	{

		class Metric_BalancedQuadTreeObject
		{

		public:

			const Geom_Surface& thePatch_;

			Standard_Real theTolerance_;
			Standard_Real theDegeneracy_;

		public:

			Metric_BalancedQuadTreeObject(const Geom_Surface& thePatch)
				: thePatch_(thePatch)
			{}

			Metric MetricAt(const M_GEO Geom_Pnt2d& PCoord) const;
		};

		inline Metric AutLib::MeshLib::Metric_BalancedQuadTreeObject::MetricAt(const M_GEO Geom_Pnt2d & PCoord) const
		{
			gp_Vec D1U, D1V;
			gp_Pnt Pt;

			thePatch_.D1(PCoord.X(), PCoord.Y(), Pt, D1U, D1V);

			Standard_Real A = D1U.Dot(D1U);
			Standard_Real B = D1U.Dot(D1V);
			Standard_Real C = D1V.Dot(D1V);

			return Metric(A, B, C);
		}

		class Metric_BalancedQuadTreeObjectTools
		{

		public:

			static Standard_Boolean doSubdivide(const Box2d& Box, const Global_Handle(Metric_BalancedQuadTreeObject) Object);
		};

		Standard_Boolean AutLib::MeshLib::Metric_BalancedQuadTreeObjectTools::doSubdivide(const Box2d & Box, const Global_Handle(Metric_BalancedQuadTreeObject) ObjectPtr)
		{
			Debug_Null_Pointer(ObjectPtr);

			Get_Const_Object(Object) = *ObjectPtr;

			Geom_Pnt2d P0 = Box.GetSwPoint();
			Geom_Pnt2d P1 = Box.GetSePoint();
			Geom_Pnt2d P2 = Box.GetNePoint();
			Geom_Pnt2d P3 = Box.GetNwPoint();

			Metric M0 = Object.MetricAt(P0);
			Metric M1 = Object.MetricAt(P1);
			Metric M2 = Object.MetricAt(P2);
			Metric M3 = Object.MetricAt(P3);

			Standard_Real L01 = Geometry_Distance::Distance(P0, P1, M0);
			Standard_Real L10 = Geometry_Distance::Distance(P1, P0, M1);

			if (L01*L10 < Object.theDegeneracy_) return Standard_True;
			if (TOLERANCE(L01, L10) > Object.theTolerance_) return Standard_True;

			Standard_Real L02 = Geometry_Distance::Distance(P0, P2, M0);
			Standard_Real L20 = Geometry_Distance::Distance(P2, P0, M2);

			if (L02*L20 < Object.theDegeneracy_) return Standard_True;
			if (TOLERANCE(L02, L20) > Object.theTolerance_) return Standard_True;

			Standard_Real L03 = Geometry_Distance::Distance(P0, P3, M0);
			Standard_Real L30 = Geometry_Distance::Distance(P3, P0, M3);

			if (L03*L30 < Object.theDegeneracy_) return Standard_True;
			if (TOLERANCE(L03, L30) > Object.theTolerance_) return Standard_True;

			Standard_Real L12 = Geometry_Distance::Distance(P1, P2, M1);
			Standard_Real L21 = Geometry_Distance::Distance(P2, P1, M2);

			if (L12*L21 < Object.theDegeneracy_) return Standard_True;
			if (TOLERANCE(L12, L21) > Object.theTolerance_) return Standard_True;

			Standard_Real L23 = Geometry_Distance::Distance(P2, P3, M2);
			Standard_Real L32 = Geometry_Distance::Distance(P3, P2, M3);

			if (L23*L32 < Object.theDegeneracy_) return Standard_True;
			if (TOLERANCE(L23, L32) > Object.theTolerance_) return Standard_True;

			Standard_Real L13 = Geometry_Distance::Distance(P1, P3, M1);
			Standard_Real L31 = Geometry_Distance::Distance(P3, P1, M3);

			if (L13*L31 < Object.theDegeneracy_) return Standard_True;
			if (TOLERANCE(L13, L31) > Object.theTolerance_) return Standard_True;

			return Standard_False;
		}
	}
}

void AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::SetTolerance(Standard_Real Tolerance)
{
	theTolerance_ = Tolerance;
}

void AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::SetDegeneracy(Standard_Real Degeneracy)
{
	theDegeneracy_ = Degeneracy;
}

void AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::SetMinLevels(Standard_Integer MinLevels)
{
	theNb_MIN_LEVELS_ = MinLevels;
}

void AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::SetMaxLevels(Standard_Integer MaxLevels)
{
	theNb_MAX_LEVELS_ = MaxLevels;
}

void AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::SetIntersection(M_GEO Entity_Metric1(*InterSection)(const M_GEO Entity_Metric1 &, const M_GEO Entity_Metric1 &))
{
	theMetric_.SetIntersection(InterSection);
}

void AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::Perform()
{
	Handle(Geom_Surface) PatchPtr = theSurface_.Geometry();

	Metric_BalancedQuadTreeObject Object(*PatchPtr);

	Object.theTolerance_ = theTolerance_;
	Object.theDegeneracy_ = theDegeneracy_;

	SubDivide_QuadTree<Metric_BalancedQuadTreeObject> Tree;

	Tree.SetMinLevel(theNb_MIN_LEVELS_);
	Tree.SetMaxLevel(theNb_MAX_LEVELS_);

	Tree.SetObject(&Object);
	Tree.SetSubDivider(&Metric_BalancedQuadTreeObjectTools::doSubdivide);

	Tree.SetDomain(Mesh2d_MetricMap::BoundingBox());

	Tree.Init();

	Tree.Perform();

	TColEntity_HAry1dOfBox2d Boxes;
	Tree.RetrieveTo(Boxes);

	Entity_Triangulation2d Triangulation;
	Entity_Box2dTools::TessellatedTriangulation(Boxes, &Triangulation);

	theMetric_.Mesh().Construct(Triangulation);
	theMetric_.InitiateCurrentElement();
	theMetric_.SetBoundingBox(Mesh2d_MetricMap::BoundingBox());

	Get_Const_Object(Points) = Triangulation.Points();
	Get_Object(Sources) = theMetric_.Sources();

	Sources.Resize(Points.Size());
	forThose(Index, 0, MaxIndexOf(Sources))
	{
		Sources[Index] = Object.MetricAt(Points[Index]);
	}

	IdentifySingularityHorizon();

	if (theSingularityHorizons_.Size() > 1)
	{
		/*cout << "  The case that has two or more the Singularity horizon are not supported yet!\n";
		CloseProgram(" Fatal Error @ Mesh2d_SurfaceMetric::Construct() - The nb. of Singularity horizon is greater than 1");*/

		//THROW_BAD_BOUNDARY_EXCEPTION(" The case that has two or more the Singularity horizon are not supported yet");
	}
}

void AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::HvCorrection
(
	const Standard_Real theFactor,
	const Standard_Integer theMaxLevel
)
{
	theMetric_.HvCorrection(theFactor, theMaxLevel);
}

void AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::LaplacianSmoothing()
{
	theMetric_.LaplacianSmoothing();
}

void AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::ExportMetricToPlt
(
	const Mesh3d_SizeMap & SizeMap,
	fstream & File
) const
{
	Handle(Geom_Surface) PatchPtr = theSurface_.Geometry();

	Get_Const_Object(Points) = theMetric_.Mesh().NodesSequence();
	Get_Const_Object(Metrics) = theMetric_.Sources();

	forThose
	(
		Index,
		0,
		MaxIndexOf(Points)
	)
	{
		Get_Const_Object(Point) = Points[Index]->Coord();
		Standard_Real H = SizeMap.ElementSize(PatchPtr->Value(Point.X(), Point.Y()));
		Entity_Metric1 Mp = (1.0 / (H*H))*Metrics[Index];

		Mp.ExportToPlt(Point, File);
	}
}

void AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::IdentifySingularityHorizon()
{
	Get_Object(Sources) = theMetric_.Sources();
	TColStd_Ary1dOfReal D(Sources.Size());

	forThose(Index, 0, MaxIndexOf(Sources))
	{
		D[Index] = MAX(0, Sources[Index].Determinant());
	}

	Standard_Real Dmax = D[0];
	forThose(Index, 0, MaxIndexOf(D)) if (D[Index] > Dmax) Dmax = D[Index];

	theMaxMetricDet_ = Dmax;

	D /= Dmax;

	const Standard_Real Criteria = theDegeneracy_ * 10;

	TColGeom_BasicQueueOfPnt2d QIps;
	Get_Const_Object(Elements) = theMetric_.Mesh().ElementsSequence();

	forThose
	(
		Index,
		0,
		MaxIndexOf(Elements)
	)
	{
		Debug_Null_Pointer(Elements[Index]);

		Get_Const_Object(Element) = *Elements[Index];

		Standard_Integer V0 = Element.Node0()->Index();
		Standard_Integer V1 = Element.Node1()->Index();
		Standard_Integer V2 = Element.Node2()->Index();

		if (D[Index_Of(V0)] > Criteria AND D[Index_Of(V1)] > Criteria AND D[Index_Of(V2)] > Criteria)
			continue;
		if (D[Index_Of(V0)] < Criteria AND D[Index_Of(V1)] < Criteria AND D[Index_Of(V2)] < Criteria)
			continue;

		Standard_Integer K = 0;

		forThose
		(
			I,
			0,
			2
		)
		{
			Debug_Null_Pointer(Element.Edge(I));

			Get_Const_Object(Edge) = *Element.Edge(I);

			V0 = Edge.Node(0)->Index();
			V1 = Edge.Node(1)->Index();

			if (ABS(D[Index_Of(V0)] - D[Index_Of(V1)]) < EPS12) continue;

			Standard_Real D0 = D[Index_Of(V0)];
			Standard_Real D1 = D[Index_Of(V1)];

			Standard_Real t = (Criteria - D0) / (D1 - D0);

			if (t > 1) continue;
			if (t < 0) continue;

			++K;

			Get_Const_Object(P0) = Edge.Node(0)->Coord();
			Get_Const_Object(P1) = Edge.Node(1)->Coord();

			QIps.EnQueue(P0 + t*(P1 - P0));
		}

		if (K != 2) CloseProgram(" Fatal Error @ Mesh2d_SurfaceMetric::StaticChain(): Failed to Identify Intersection Points");
	}

	if (NOT QIps.Size()) return;

	TColEntity_Ary1dOfEdgeIndex Edges(QIps.Size() / 2);
	Standard_Integer K = 0;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Edges[Index].SetV12(K + 1, K + 2);
		K += 2;
	}

	Entity_StaticChain2d Chain;
	Chain.Init(QIps.Retrive(), Edges);

	theSingularityHorizons_ = Entity_StaticChain2dTools::GetPolygons(Chain);

	forThose
	(
		Index,
		0,
		MaxIndexOf(theSingularityHorizons_)
	)
	{
		theSingularityHorizons_[Index]->Smoothing(0.95, 5);
	}
}