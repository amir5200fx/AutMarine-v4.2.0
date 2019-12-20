#include <Examples\Mesh\Example_Mesh2d.hxx>

#include <Model2d_Naca4Digit.hxx>
#include <Cad2d_MakePlane.hxx>
#include <Cad2d_BooleanOperators.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh2d_NodeTools.hxx>
#include <Mesh2d_BasicAft.hxx>
#include <SizeMap2d_ModifyBackSize.hxx>
#include <SizeMap2d_PrimitiveShapesSizeMapTool.hxx>
#include <TColMesh2d_ADTree2dOfNode.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;

#include <gp_Ax22d.hxx>

void AutLib::Example_Mesh2d::MeshCase6()
{
	Open_OutputFile_TecPlot(Plot, "Example_MeshCase6");

	Cad2d_MakePlane Box, Box1, Cir1, Cir2;
	Box.Box(Geom_Pnt2d(-0,-1.5), Geom_Pnt2d(5.0, 1.5));
	Box1.Box(Geom_Pnt2d(-0.1, 0.48), Geom_Pnt2d(5.1, 0.52));

	Model2d_Naca4Digit Naca;
	Naca.Parameters().Init(1.0, 4, 40, 10);
	Naca.Perform();

	gp_Ax22d A(gp_Pnt2d(1.0, 0.3), gp_Dir2d(1.0, 0));
	Cir1.Circle(A, 0.2);
	Cir2.Circle(gp_Ax22d(gp_Pnt2d(2.0, 0.3), gp_Dir2d(1.0, 0)), 0.15);

	Global_Handle(Cad2d_Plane) Shape = Naca.ExportAsPart(A);

	Cad2d_Plane Sum;
	Cad2d_BooleanOperators::Subtract(&Box, Shape, &Sum);
	Sum.ExportToPlt(Plot);
	Box1.ExportToPlt(Plot);
	Cir1.ExportToPlt(Plot);
	Cir2.ExportToPlt(Plot);

	Get_Const_Pointer(Edges) = Sum.Edges();
	Debug_Null_Pointer(Edges);

	Edges->Print(Standard_True);

	Mesh_ReferenceValues Reference(0.5);
	
	SizeMap2d_PrimitiveShapesSizeMapTool SizeMap(&Reference, &Sum);

	SizeMap.MeshConditions().SetCustomSurfaceSize(Standard_True);
	SizeMap.MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);

	SizeMap.ImportShape(&Box1);
	SizeMap.ImportShape(&Cir1);
	SizeMap.ImportShape(&Cir2);
	SizeMap.MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	SizeMap.MeshValues().SurfaceSize().SetTargetSize(3);
	SizeMap.MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_MODERATE);

	SizeMap.CreateSizeMap();

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