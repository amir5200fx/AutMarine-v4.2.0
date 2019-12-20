#include <Examples\Mesh\Example_AnIsoMesh2d.hxx>

#include <Entity_Metric1Tools.hxx>
#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_BlockEdgeOnPlane.hxx>
#include <Cad2d_MakePlane.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh2d_NodeTools.hxx>
#include <Mesh2d_BasicAft.hxx>
#include <Mesh2d_Domain.hxx>
#include <SizeMap2d_ModifyBackSize.hxx>
#include <SizeMap2d_UniformCurvesSizeMapTool.hxx>
#include <MetricMap2d_StdBackMetric.hxx>
#include <MetricMap2d_BoundaryMetricMapTool.hxx>
#include <SizeMap2d_FullIntAnIsoRefineSearchRefineElementSize.hxx>
#include <TColMesh2d_ADTree2dOfNode.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;
using namespace GeoLib;

void AutLib::Example_AnIsoMesh2d::Case1()
{
	Open_OutputFile_TecPlot(Plot, "Example_AnIsoMesh2dCase1");

	Cad2d_MakePlane Box;
	Box.Box(Geom_Pnt2d(), Geom_Pnt2d(1, 1));

	Get_Pointer(Edges) = Box.Edges();
	Debug_Null_Pointer(Edges);

	Edges->Print(Standard_True);

	Get_Const_Pointer(Block) = Edges->SelectBlockCurve("Default Block Edge");
	Debug_Null_Pointer(Block);

	Block->SelectCurve(4);
	Edges->Split("Source");

	Mesh_ReferenceValues Reference(0.1);

	SizeMap2d_UniformCurvesSizeMapTool SizeMapTool(&Reference, &Box);
	SizeMapTool.ImportCurvePatch("Source");
	SizeMapTool.MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	SizeMapTool.MeshValues().SurfaceSize().SetTargetSize(100);
	SizeMapTool.MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_FAST);
	SizeMapTool.CreateSizeMap();

	Debug_Null_Pointer(SizeMapTool.BackGroundMesh());

	MetricMap2d_BoundaryMetricMapTool MetricMapTool(&SizeMapTool);
	MetricMapTool.SetH2(0.1);
	MetricMapTool.SetIntersection(&Entity_Metric1Tools::IntersectionSR);
	MetricMapTool.Perform();

	MetricMap2d_StdBackMetric MetricMap(*MetricMapTool.Metric());

	SizeMap2d_ModifyBackSize SizeMap(Reference.BaseSize(), *SizeMapTool.BackGroundMesh());

	SizeMap2d_FullIntAnIsoRefineSearchRefineElementSize AnIsoMap(&SizeMap, &MetricMap);

	TColMesh2d_ADTree2dOfNode Engine;
	Engine.SetCoordinateFunction(&Mesh2d_NodeTools::GetCoordOf);

	Mesh2d_BasicAft Aft(AnIsoMap, &Engine);
	Aft.Import(Box);
	Aft.SetVerbosity(1);
	Try_Exception_Handle_Exit(Aft.Perform());

	Aft.ExportToPlt(Plot);
}