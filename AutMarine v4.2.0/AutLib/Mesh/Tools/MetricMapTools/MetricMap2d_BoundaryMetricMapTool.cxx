#include <MetricMap2d_BoundaryMetricMapTool.hxx>

#include <Geom_BalancedPrQuadTree.hxx>
#include <GeoMesh_BackGroundMetric2d.hxx>
#include <GeoMesh_BackGroundMetric2dTools.hxx>
#include <Entity_Triangulation2d.hxx>
#include <Entity_Metric1Tools.hxx>
#include <Entity_Box2dTools.hxx>
#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_Plane.hxx>
#include <Mesh2d_Curve.hxx>
#include <Mesh2d_MetricSourcePoint.hxx>
#include <Mesh2d_MetricSourcePointTools.hxx>
#include <SizeMap2d_StdBackSize.hxx>
#include <SizeMap2d_BoundarySizeMapTool.hxx>
#include <TColEntity_HAry1dOfBox2d.hxx>
#include <TColCad2d_HAry1dOfEdgeOnPlane.hxx>
#include <TColMesh2d_HAry1dOfMetricSourcePoint.hxx>
#include <TColMesh2d_HBasicQueueOfMetricSourcePoint.hxx>

using namespace AutLib;
using namespace MeshLib;
using namespace CadLib;
using namespace GeoLib;

static const Standard_Integer DEFAULT_BUCKET_SIZE = 4;

AutLib::MeshLib::MetricMap2d_BoundaryMetricMapTool::MetricMap2d_BoundaryMetricMapTool(const Global_Handle(SizeMap2d_BoundarySizeMapTool) theBoundarySize)
	: MetricMap2d_MetricMapTool()
	, theBoundarySize_(theBoundarySize)
	, theBucketSize_(DEFAULT_BUCKET_SIZE)
{
}

void AutLib::MeshLib::MetricMap2d_BoundaryMetricMapTool::SetBucketSize(const Standard_Integer theBucketSize)
{
	theBucketSize_ = theBucketSize;
}

void AutLib::MeshLib::MetricMap2d_BoundaryMetricMapTool::Perform()
{
	if (IsNULL(theBoundarySize_)) { THROW_STANDARD_EXCEPTION("Null Boundary Size"); }

	TColCad2d_HAry1dOfEdgeOnPlane Edges;
	theBoundarySize_->RetrieveCurvesTo(Edges);

	if (Edges.IsEmpty()) { return; }

	Standard_Real Lamda1 = 1.0 / (theH1_*theH1_);
	Standard_Real Lamda2 = 1.0 / (theH2_*theH2_);

	SizeMap2d_StdBackSize SizeMap(1.0, *theBoundarySize_->BackGroundMesh());
	TColMesh2d_HBasicQueueOfMetricSourcePoint QSources;
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Edges))
	{
		Debug_Null_Pointer(Edges[Index]);
		Debug_Null_Pointer(Edges[Index]->Curve());

		Mesh2d_Curve MeshCurve(SizeMap, Edges[Index]->Curve());
		MeshCurve.Perform();

		Debug_If_Condition_Message(NOT MeshCurve.IsDone(), " Curve not discretized");

		Get_Const_Object(Points) = MeshCurve.Chain().Coords();
		Get_Const_Object(E) = MeshCurve.Chain().Edges();

		forThose
		(
			I,
			0, 
			MaxIndexOf(E)
		)
		{
			Standard_Integer V0 = E[I].V0() - 1;
			Standard_Integer V1 = E[I].V1() - 1;

			Geom_Pnt2d Pm = MEAN(Points[V0], Points[V1]);
			Geom_Pnt2d t = (Points[V1] - Points[V0]).UnitLength();
			Geom_Pnt2d n = t;
			n.Rotate90ccw();

			QSources.EnQueue(new Mesh2d_MetricSourcePoint(Pm, Entity_Metric1Tools::CalcMetric(Lamda1, Lamda2, t, n)));
		}
	}
	TColMesh2d_HAry1dOfMetricSourcePoint Sources;
	QSources.RetrieveTo(Sources);

	Entity_Box2d Box = theBoundarySize_->BoundingBox();

	Geom_BalancedPrQuadTree<Global_Handle(Mesh2d_MetricSourcePoint)> Tree;
	Tree.SetCoordinateFunction(&Mesh2d_MetricSourcePointTools::CoordinateOf);
	Tree.SetRegion(Box);
	Tree.SetBucketSize(theBucketSize_);
	Tree.Insert(Sources);
	Tree.PostBalancing();

	TColEntity_HAry1dOfBox2d Boxes;
	Tree.RetrieveTo(Boxes);

	Entity_Triangulation2d Triangulation;
	Entity_Box2dTools::Triangulation(Boxes, &Triangulation);

	theBackMetric_ = new GeoMesh_BackGroundMetric2d;
	theBackMetric_->Mesh().Construct(Triangulation);
	theBackMetric_->InitiateCurrentElement();
	theBackMetric_->SetBoundingBox(Tree.BoundingBox());

	Try_Exception_Handle_Exit(GeoMesh_BackGroundMetric2dTools::SetSourcesToMesh(Sources, *theBackMetric_, InterSection));

	theBackMetric_->SetIntersection(InterSection);
	theBackMetric_->HvCorrection(3.5, 3);

	FreeMemory(Sources);
}