#include <Examples\Cad\Example_Solid.hxx>

#include <Ship_Hull.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_SolidTools.hxx>
#include <Cad3d_MakeSolid.hxx>
#include <Cad3d_BooleanOperators.hxx>
#include <Cad3d_BlockEntityOnSolid.hxx>

#include <gp_Ax2.hxx>
#include <TopoDS_Shape.hxx>

using namespace AutLib;
using namespace CadLib;

void AutLib::Example_Solid::MakeCfdShipCase1()
{
	Open_OutputFile_TecPlot(Plot, "Example_MakeCfdShipCase1");

	Ship_Hull Hull;

	gp_Ax2 Local(Geom_Pnt3d(300, 0, 0), gp_Dir(0, 0, 1), gp_Dir(-1, 0, 0));

	//Hull.SetToDiscreteMyModel();
	Hull.Parameters().Hull().AftForm().SetDeadRise(0.5);
	Hull.Make();
	Hull.TransformTo(Local);
	//cout << Hull.CalcVolume() << endl;
	//Hull.ExportMyModelToPlt(Plot);
	//return;
	Geom_Pnt3d P0(0, -100, -120);
	Geom_Pnt3d P1(450, 100, 120);

	TopoDS_Shape Box = Cad3d_MakeSolid::Box(P0, P1);

	/*Cad3d_SolidTools::Triangulation(Box);
	Cad3d_SolidTools::Triangulation(Hull.Shape());
	Cad3d_SolidTools::ExportToPlt(Box, Plot);
	Cad3d_SolidTools::ExportToPlt(Hull.Shape(), Plot);
	return;*/
	//TopoDS_Shape Domain = Cad3d_BooleanOperators::Subtract(Box, Hull.Shape());

	//Cad3d_SolidTools::Triangulation(Domain);
	//Cad3d_SolidTools::ExportToPlt(Domain, Plot);

	Cad3d_SolidTools::ExportToIGES(Box, "Example_MakeCfdShipCase1_2.igs");
}