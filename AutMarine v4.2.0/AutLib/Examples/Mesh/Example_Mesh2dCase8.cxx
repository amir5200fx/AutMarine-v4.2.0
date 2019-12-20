#include <Examples\Mesh\Example_Mesh2d.hxx>

#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_Sketch.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_BlockEdgeOnPlane.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh2d_NodeTools.hxx>
#include <Mesh2d_BasicAft.hxx>
#include <SizeMap2d_AdaptiveCurvesSizeMapTool.hxx>
#include <SizeMap2d_UniSize.hxx>
#include <SizeMap2d_ModifyBackSize.hxx>
#include <TColMesh2d_ADTree2dOfNode.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;

void AutLib::Example_Mesh2d::MeshCase8()
{
	Open_OutputFile_TecPlot(Plot, "Example_MeshCase8");

	Cad2d_Sketch Sketch;

	TColGeom_BasicQueueOfPnt2d Points;
	Points.EnQueue(Geom_Pnt2d());
	Points.EnQueue(Geom_Pnt2d(0.1, 0.3));
	Points.EnQueue(Geom_Pnt2d(0.15, 0.68));
	Points.EnQueue(Geom_Pnt2d(0.175, 1.05));
	Points.EnQueue(Geom_Pnt2d(0.19, 1.1));
	Points.EnQueue(Geom_Pnt2d(0.2, 1.15));
	Points.EnQueue(Geom_Pnt2d(0.21, 1.15));
	Points.EnQueue(Geom_Pnt2d(0.22, 1.05));
	Points.EnQueue(Geom_Pnt2d(0.24, 0.75));
	Points.EnQueue(Geom_Pnt2d(0.3, 0.55));
	Points.EnQueue(Geom_Pnt2d(0.55, 0.23));
	Points.EnQueue(Geom_Pnt2d(0.8, 0.21));
	Points.EnQueue(Geom_Pnt2d(1.2, 0.18));

	Sketch.CreateInterpolation(Points);

	Sketch.CreateLine(Geom_Pnt2d(1.2, 0.18), Geom_Pnt2d(1.6, 2.0));
	Sketch.CreateLine(Geom_Pnt2d(1.6, 2.0), Geom_Pnt2d(-0.5, 1.0));
	Sketch.CreateLine(Geom_Pnt2d(-0.5, 1.0), Geom_Pnt2d(-0.5, 0));
	Sketch.CreateLine(Geom_Pnt2d(-0.5, 0), Geom_Pnt2d());

	Global_Handle(Cad2d_Plane) Shape = Sketch.MakePlane();

	Get_Pointer(Edges) = Shape->Edges();
	Debug_Null_Pointer(Edges);

	Get_Const_Pointer(Block) = Edges->SelectBlockCurve("Default Block Edge");
	Debug_Null_Pointer(Block);

	Block->SelectCurve(1);
	Edges->Split("Source");

	Edges->Print(Standard_True);

	Mesh_ReferenceValues Reference(0.15);

	SizeMap2d_AdaptiveCurvesSizeMapTool SizeMap(&Reference, Shape);

	SizeMap.ImportCurvePatch("Source");

	SizeMap.MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	SizeMap.MeshConditions().SetCustomSurfaceSize(Standard_True);
	SizeMap.MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	SizeMap.MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	SizeMap.MeshValues().SurfaceSize().SetTargetSize(60);
	SizeMap.MeshValues().SurfaceSize().SetMinSize(2);
	SizeMap.MeshValues().SurfaceCurvature().SetSpanAngle(15);
	SizeMap.MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_MODERATE);

	SizeMap.CreateSizeMap();

	Debug_Null_Pointer(SizeMap.BackGroundMesh());

	SizeMap2d_ModifyBackSize Map(Reference.BaseSize(), *SizeMap.BackGroundMesh());

	TColMesh2d_ADTree2dOfNode Engine;
	Engine.SetCoordinateFunction(&Mesh2d_NodeTools::GetCoordOf);

	Mesh2d_BasicAft Aft(Map, &Engine);
	Aft.Import(*Shape);
	Aft.SetVerbosity(1);
	Try_Exception_Handle_Exit(Aft.Perform());

	Aft.ExportToPlt(Plot);

	FreePointer(Shape);
}