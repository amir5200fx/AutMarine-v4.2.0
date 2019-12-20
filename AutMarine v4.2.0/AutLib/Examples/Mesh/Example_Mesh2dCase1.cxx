#include <Examples\Mesh\Example_Mesh2d.hxx>

#include <Cad2d_MakePlane.hxx>
#include <Cad2d_BooleanOperators.hxx>
#include <GeoMesh_TriangleMesh2d.hxx>
#include <GeoMesh_BackGroundMesh2dTools.hxx>
#include <Mesh2d_BasicAft.hxx>
#include <Mesh2d_NodeTools.hxx>
#include <SizeMap2d_UniSize.hxx>
#include <SizeMap2d_ModifyBackSize.hxx>
#include <SizeMap2d_FullIntBackSize.hxx>
#include <TColMesh2d_ADTree2dOfNode.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;
using namespace GeoLib;

#include <gp_Ax22d.hxx>

void AutLib::Example_Mesh2d::MeshCase1()
{
	Open_OutputFile_TecPlot(Plot, "Example_MeshCase1");

	Cad2d_MakePlane Box, Circle, Circle1, Circle2, Circle3;
	Box.Box(Geom_Pnt2d(), Geom_Pnt2d(0.3, 1.2));
	Circle.Circle(gp_Ax2d(Geom_Pnt2d(0.4, 0.5), gp_Dir2d(1.0, 0)), 0.5);
	Circle1.Circle(gp_Ax2d(Geom_Pnt2d(0.5, 0.75), gp_Dir2d(1.0, 0)), 0.15);
	Circle2.Circle(gp_Ax2d(Geom_Pnt2d(0.65, 0.25), gp_Dir2d(1.0, 0)), 0.08);
	Circle3.Circle(gp_Ax2d(Geom_Pnt2d(0.25, 0.45), gp_Dir2d(1.0, 0)), 0.05);

	/*Box.ExportToPlt(Plot);
	Circle.ExportToPlt(Plot);
	Circle1.ExportToPlt(Plot);
	Circle2.ExportToPlt(Plot);
	Circle3.ExportToPlt(Plot);
	return;*/

	Cad2d_Plane Sum;
	Cad2d_BooleanOperators::Union(&Box, &Circle, &Sum);
	Cad2d_BooleanOperators::Subtract(&Sum, &Circle1, &Sum);
	Cad2d_BooleanOperators::Subtract(&Sum, &Circle2, &Sum);
	Cad2d_BooleanOperators::Subtract(&Sum, &Circle3, &Sum);

	//Sum.ExportToPlt(Plot);
	
	fstream Input;
	Input.open("Example_MeshCase1Back.txt", ios::in);

	Global_Handle(GeoMesh_BackGroundMesh2d) Back = GeoMesh_BackGroundMesh2dTools::ReadBackMeshFrom(Input);
	//Back->ExportMeshToPlt(Plot);
	//return;
	SizeMap2d_ModifyBackSize Map(0.5, *Back);

	TColMesh2d_ADTree2dOfNode Engine;
	Engine.SetCoordinateFunction(&Mesh2d_NodeTools::GetCoordOf);

	SizeMap2d_UniSize UniSize(0.0005);

	Mesh2d_BasicAft Aft(Map, &Engine);
	Aft.Import(Sum);
	Aft.SetVerbosity(3);
	//Aft.LaplacianSmoothing().SetApply(Standard_False);
	Aft.Config().SetFrontType(Mesh2d_FrontType_FAST);

	Try_Exception_Handle_Exit(Aft.Perform());

	Aft.ExportQualityToPlt(Plot);

	FreePointer(Back);
}

//void AutLib::Example_Mesh2d::MeshCase1()
//{
//	Open_OutputFile_TecPlot(Plot, "Example_MeshCase1");
//
//	Cad2d_MakePlane Box, Circle;
//	Box.Box(Geom_Pnt2d(), Geom_Pnt2d(0.3, 1.2));
//	Circle.Circle(gp_Ax2d(Geom_Pnt2d(0.4, 0.5), gp_Dir2d(1.0, 0)), 0.5);
//
//	Cad2d_Plane Sum;
//	Cad2d_BooleanOperators::Union(&Box, &Circle, &Sum);
//
//	Sum.ExportToPlt(Plot);
//
//	SizeMap2d_UniSize Map(0.0025);
//
//	TColMesh2d_ADTree2dOfNode Engine;
//	Engine.SetCoordinateFunction(&Mesh2d_NodeTools::GetCoordOf);
//
//	Mesh2d_BasicAft Aft(Map, &Engine);
//	Aft.Import(Sum);
//	Aft.SetVerbosity(1);
//	Try_Exception_Handle_Exit(Aft.Perform());
//	Aft.ExportToPlt(Plot);
//}