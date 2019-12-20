#include <Examples\Cad\Example_Solid.hxx>

#include <Compound_Ship.hxx>

using namespace AutLib;
using namespace CadLib;

void AutLib::Example_Solid::MakeCompoundShipCase1()
{
	Open_OutputFile_TecPlot(Plot, "Example_MakeCompoundShipCase1");

	Compound_Ship Ship;
	Ship.Make();

	Ship.SetIGESFileName("CompoundShip.igs");
	Ship.ExportMyModelToPlt(Plot);
	Ship.ExportToIGES();
}