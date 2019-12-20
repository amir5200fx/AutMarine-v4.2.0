#include <Examples\Mesh\Example_Mesh2d.hxx>

#include <Model2d_Naca4Digit.hxx>
#include <Cad2d_MakePlane.hxx>
#include <Cad2d_BooleanOperators.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh2d_NodeTools.hxx>
#include <Mesh2d_BasicAft.hxx>
#include <SizeMap2d_ModifyBackSize.hxx>
#include <SizeMap2d_SharpCornersSizeMapTool.hxx>
#include <SizeMap2d_AdaptiveCurvesSizeMapTool.hxx>
#include <TColMesh2d_ADTree2dOfNode.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;

#include <gp_Ax22d.hxx>

//void AutLib::Example_Mesh2d::MeshCase5()
//{
//	Open_OutputFile_TecPlot(Plot, "Example_MeshCase5");
//
//	Cad2d_MakePlane Box;
//	Box.Box(Geom_Pnt2d(), Geom_Pnt2d(3.0, 1.0));
//
//	Model2d_Naca4Digit Naca;
//	Naca.Parameters().Init(1.0, 4, 40, 10);
//	Naca.Perform();
//
//	gp_Ax22d A(gp_Pnt2d(1.0, 0.3), gp_Dir2d(1.0, 0));
//
//	Global_Handle(Cad2d_Plane) Shape = Naca.ExportAsPart(A);
//
//	Cad2d_Plane Sum;
//	Cad2d_BooleanOperators::Subtract(&Box, Shape, &Sum);
//	//Sum.ExportToPlt(Plot);
//
//	Get_Const_Pointer(Edges) = Sum.Edges();
//	Debug_Null_Pointer(Edges);
//
//	Edges->Print(Standard_True);
//
//	Mesh_ReferenceValues Reference(0.25);
//
//	SizeMap2d_SharpCornersSizeMapTool SizeMap(&Reference, &Sum);
//	//SizeMap.ImportCurvePatch("Default Inner Block 1");
//	SizeMap.ImportCurvePatch("Default Block Edge");
//	SizeMap.MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
//	SizeMap.MeshValues().SurfaceSize().SetTargetSize(5);
//	SizeMap.MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_FAST);
//	SizeMap.SetAngle(100);
//	SizeMap.CreateSizeMap();
//
//	Debug_Null_Pointer(SizeMap.BackGroundMesh());
//
//	SizeMap2d_ModifyBackSize Map(Reference.BaseSize(), *SizeMap.BackGroundMesh());
//	//Map.ExportToPlt(Plot);
//
//	TColMesh2d_ADTree2dOfNode Engine;
//	Engine.SetCoordinateFunction(&Mesh2d_NodeTools::GetCoordOf);
//
//	Mesh2d_BasicAft Aft(Map, &Engine);
//	Aft.Import(Sum);
//	Aft.SetVerbosity(1);
//	Try_Exception_Handle_Exit(Aft.Perform());
//
//	Aft.ExportToPlt(Plot);
//
//	FreePointer(Shape);
//}

void AutLib::Example_Mesh2d::MeshCase5()
{
	Open_OutputFile_TecPlot(Plot, "Example_MeshCase5");

	Cad2d_MakePlane Box;
	Box.Box(Geom_Pnt2d(), Geom_Pnt2d(3.0, 1.0));

	Model2d_Naca4Digit Naca;
	Naca.Parameters().Init(1.0, 4, 40, 10);
	Naca.Perform();

	gp_Ax22d A(gp_Pnt2d(1.0, 0.3), gp_Dir2d(1.0, 0));

	Global_Handle(Cad2d_Plane) Shape = Naca.ExportAsPart(A);

	Cad2d_Plane Sum;
	Cad2d_BooleanOperators::Subtract(&Box, Shape, &Sum);
	//Sum.ExportToPlt(Plot);

	Get_Const_Pointer(Edges) = Sum.Edges();
	Debug_Null_Pointer(Edges);

	Edges->Print(Standard_True);

	Mesh_ReferenceValues Reference(0.5);

	SizeMap2d_AdaptiveCurvesSizeMapTool SizeMap(&Reference, &Sum);

	SizeMap.ImportCurvePatch("Default Inner Block 1");

	SizeMap.MeshConditions().SetCustomSurfaceSize(Standard_True);
	SizeMap.MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	SizeMap.MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	SizeMap.MeshValues().SurfaceSize().SetTargetSize(15);
	SizeMap.MeshValues().SurfaceSize().SetMinSize(1);
	SizeMap.MeshValues().SurfaceCurvature().SetSpanAngle(20);
	SizeMap.MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_FAST);
	SizeMap.CreateSizeMap();

	SizeMap.ExportContourToPlt(Plot);

	return;

	Debug_Null_Pointer(SizeMap.BackGroundMesh());

	SizeMap2d_ModifyBackSize Map(Reference.BaseSize(), *SizeMap.BackGroundMesh());
	//Map.ExportToPlt(Plot);

	TColMesh2d_ADTree2dOfNode Engine;
	Engine.SetCoordinateFunction(&Mesh2d_NodeTools::GetCoordOf);

	Mesh2d_BasicAft Aft(Map, &Engine);
	Aft.Import(Sum);
	Aft.SetVerbosity(1);
	Try_Exception_Handle_Exit(Aft.Perform());

	Aft.ExportToPlt(Plot);

	FreePointer(Shape);
}