#include <MetricMap2d_PrimitivesMetricMapTool.hxx>

#include <Entity_Triangulation2d.hxx>
#include <Entity_Metric1Tools.hxx>
#include <Entity_Box2dTools.hxx>
#include <Entity_Node2d.hxx>
#include <Geom_BalancedPrQuadTree.hxx>
#include <GeoMesh_BackGroundMetric2d.hxx>
#include <GeoMesh_BackGroundMetric2dTools.hxx>
#include <SizeMap2d_StdBackSize.hxx>
#include <SizeMap2d_PrimitiveShapesSizeMapTool.hxx>
#include <Mesh2d_MetricSourcePoint.hxx>
#include <Mesh2d_MetricSourcePointTools.hxx>
#include <TColMesh2d_HAry1dOfMetricSourcePoint.hxx>

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

static const Standard_Integer DEFAULT_BUCKET_SIZE = 2;

AutLib::MeshLib::MetricMap2d_PrimitivesMetricMapTool::MetricMap2d_PrimitivesMetricMapTool(const Global_Handle(SizeMap2d_PrimitiveShapesSizeMapTool) theSizeMap)
	: theBucketSize_(DEFAULT_BUCKET_SIZE)
	, theSizeMap_(theSizeMap)
{
	//SetIntersection(&Entity_Metric1Tools::IntersectionSR);
}

void AutLib::MeshLib::MetricMap2d_PrimitivesMetricMapTool::SetBucketSize(const Standard_Integer theBucketSize)
{
	theBucketSize_ = theBucketSize;
}

void AutLib::MeshLib::MetricMap2d_PrimitivesMetricMapTool::Perform()
{
	if (IsNULL(theSizeMap_)) { THROW_STANDARD_EXCEPTION("Null Boundary Size"); }

	Standard_Real Lamda1 = 1.0 / (theH1_*theH1_);
	Standard_Real Lamda2 = 1.0 / (theH2_*theH2_);

	Get_Const_Object(BackMesh) = *theSizeMap_->BackGroundMesh();
	Get_Const_Object(Mesh) = BackMesh.Mesh();
	Get_Const_Object(Nodes) = Mesh.NodesSequence();
	Get_Const_Object(InnerNodes) = theSizeMap_->InnerNodes();
	Get_Const_Object(OutterNodes) = theSizeMap_->OutterNodes();

	Entity_Metric1 M = Entity_Metric1Tools::CalcMetric(Lamda1, Lamda2, theE1_, theE2_);
	Entity_Metric1 M0(1, 0, 1);

	TColMesh2d_HAry1dOfMetricSourcePoint Sources(InnerNodes.Size());
	Standard_Integer K = 0;
	forThose(Index, 0, MaxIndexOf(InnerNodes))
	{
		Sources[K] = new Mesh2d_MetricSourcePoint(InnerNodes[Index]->Coord(), M);
		K++;
	}
	/*forThose(Index, 0, MaxIndexOf(OutterNodes))
	{
		Sources[K] = new Mesh2d_MetricSourcePoint(OutterNodes[Index]->Coord(), M0);
		K++;
	}*/

	Entity_Box2d Box = theSizeMap_->BoundingBox();

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
	/*Open_OutputFile_TecPlot(Plot, "test");
	theBackMetric_->ExportMeshToPlt(Plot);
	theBackMetric_->ExportToPlt(Plot);
	exit(1);*/
	FreeMemory(Sources);
}