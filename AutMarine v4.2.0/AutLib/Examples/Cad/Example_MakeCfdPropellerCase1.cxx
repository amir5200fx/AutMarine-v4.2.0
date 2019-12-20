#include <Examples\Cad\Example_Solid.hxx>

#include <Prop_Propeller.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_SolidTools.hxx>
#include <Cad3d_MakeSolid.hxx>
#include <Cad3d_BooleanOperators.hxx>
#include <Cad3d_BlockEntityOnSolid.hxx>

#include <TopoDS_Shape.hxx>

using namespace AutLib;
using namespace CadLib;

void AutLib::Example_Solid::MakeCfdPropellerCase1()
{
	Open_OutputFile_TecPlot(Plot, "Example_MakeCfdPropellerCase1");

	Prop_Propeller Propeller;

	Get_Object(Parameters) = Propeller.Parameters();
	Parameters.SetToRemoveHubApex();

	Get_Object(Hub) = Parameters.HubParameters();
	Hub.SetShaftLength(30);

	Propeller.SetToDiscreteMyModel();
	Propeller.Make();
	Propeller.ExportMyModelToPlt(Plot);

	Geom_Pnt3d P0(-10, -7.5, -7.5);
	Geom_Pnt3d P1(29, 7.5, 7.5);

	TopoDS_Shape Box = Cad3d_MakeSolid::Box(P0, P1);

	TopoDS_Shape Domain = Cad3d_BooleanOperators::Subtract(Box, Propeller.Shape());
	Cad3d_SolidTools::ExportToIGES(Domain, "Example_MakeCfdPropellerCase1.igs");
}