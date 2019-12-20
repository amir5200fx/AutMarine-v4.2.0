#include <Examples\Mesh\Example_Region2d.hxx>

#include <Model2d_Naca4Digit.hxx>
#include <Cad2d_MakePlane.hxx>
#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_BlockEdgeOnPlane.hxx>
#include <Cad2d_BooleanOperators.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh2d_Region.hxx>
#include <Mesh2d_Plane.hxx>
#include <SizeMap2d_AdaptiveCurvesSizeMapTool.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;

#include <gp_Ax22d.hxx>

void AutLib::Example_Region2d::Case1()
{
	Open_OutputFile_TecPlot(Plot, "Example_Region2dCase1");

	Cad2d_MakePlane Box;
	Box.Box(Geom_Pnt2d(-0, -1.5), Geom_Pnt2d(5.0, 1.5));

	Model2d_Naca4Digit Naca;
	Naca.Parameters().Init(1.0, 4, 40, 10);
	Naca.Perform();

	gp_Ax22d A(gp_Pnt2d(1.0, 0.3), gp_Dir2d(1.0, 0));

	Global_Handle(Cad2d_Plane) Shape = Naca.ExportAsPart(A);

	Cad2d_Plane Sum;
	Cad2d_BooleanOperators::Subtract(&Box, Shape, &Sum);

	Sum.ExportToPlt(Plot);

	Get_Pointer(Edges) = Sum.Edges();
	Debug_Null_Pointer(Edges);

	Get_Const_Pointer(Block) = Edges->SelectBlockCurve("Default Block Edge");
	Debug_Null_Pointer(Block);

	Block->SelectCurve(1);
	Block->SelectCurve(3);
	Edges->Split("Wall");

	Edges->Print(Standard_True);

	Mesh_ReferenceValues Reference(0.5);

	Mesh2d_Region Region(&Reference, &Sum);
	
	Get_Object(Boundary) = Region.Boundaries();
	Boundary.CreateNewMap("Wall");
	Boundary.CreateNewMap("Hydrofoil");

	Get_Pointer(WallMap) = Boundary.SelectMap("Wall");
	Get_Pointer(HydroMap) = Boundary.SelectMap("Hydrofoil");

	WallMap->ImportCurvePatch("Wall");
	WallMap->MeshConditions().SetCustomSurfaceSize(Standard_True);
	WallMap->MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	WallMap->MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	WallMap->MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	WallMap->MeshValues().SurfaceSize().SetTargetSize(7);
	WallMap->MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_MODERATE);
	WallMap->CreateSizeMap();

	HydroMap->ImportCurvePatch("Default Inner Block 1");
	HydroMap->MeshConditions().SetCustomSurfaceSize(Standard_True);
	HydroMap->MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	HydroMap->MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	HydroMap->MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	HydroMap->MeshValues().SurfaceSize().SetTargetSize(2.5);
	HydroMap->MeshValues().SurfaceSize().SetMinSize(1);
	HydroMap->MeshValues().SurfaceCurvature().SetSpanAngle(15);
	HydroMap->MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_SLOW);
	HydroMap->CreateSizeMap();

	Region.SetVerbosity(2);
	Region.Perform();
	
	Debug_Null_Pointer(Region.Mesh());

	Region.Mesh()->ExportToPlt(Plot);
}