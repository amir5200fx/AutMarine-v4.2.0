#include <Examples\Cad\Example_Solid.hxx>

#include <Cad3d_Solid.hxx>
#include <Cad3d_MakeSolid.hxx>
#include <Cad3d_BooleanOperators.hxx>
#include <Cad3d_EntitiesOnSolid.hxx>

using namespace AutLib;
using namespace CadLib;

#include <Cad3d_SolidTools.hxx>
#include <TopoDS_Shape.hxx>

void AutLib::Example_Solid::SolidSolidBooleanCase1()
{
	Open_OutputFile_TecPlot(Plot, "Example_SolidSolidBooleanCase1");

	Geom_Pnt3d P1;
	Geom_Pnt3d P2(1, 2, 0.6);

	Geom_Pnt3d P3(0.5, 0.5, 0.5);
	Geom_Pnt3d P4(1.5, 2.5, 1.1);

	Geom_Pnt3d P5(0.1, 0.2, 0.05);
	Geom_Pnt3d P6(0.8, 1.2, 0.35);

	TopoDS_Shape Box1 = Cad3d_MakeSolid::Box(P1, P2);
	TopoDS_Shape Box2 = Cad3d_MakeSolid::Box(P3, P4);
	TopoDS_Shape Box3 = Cad3d_MakeSolid::Box(P5, P6);

	TopoDS_Shape Sum = Cad3d_BooleanOperators::Subtract(Box1, Box2);
	Sum = Cad3d_BooleanOperators::Subtract(Sum, Box3);

	Cad3d_Solid Solid;
	Solid.Make(Cad3d_SolidTools::GetSurfaces(Sum));

	Open_OutputFile_txt(File, "Example_SolidSolidBooleanCase1");

	Solid.ExportSurfacesToPlt(Plot);
	Solid.Report(File);

	Get_Const_Object(Block) = Solid.Surfaces();
	Block->Print(Standard_True, File);
}