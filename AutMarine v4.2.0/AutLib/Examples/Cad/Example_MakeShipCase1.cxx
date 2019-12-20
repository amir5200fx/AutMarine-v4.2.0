#include <Examples\Cad\Example_Solid.hxx>

#include <Ship_Hull.hxx>

using namespace AutLib;
using namespace CadLib;

void AutLib::Example_Solid::MakeShipCase1()
{
	//Open_OutputFile_TecPlot(Profiles, "Example_MakeShipCase1_Profiles");

	Open_OutputFile_TecPlot(Plot, "Example_MakeShipCase1");

	Ship_Hull Hull;

	Hull.SetToMakeAsSolid();
	Hull.SetToDiscreteMyModel();

	Hull.Make();

	Hull.CalcMyStations(20, 1, 158);
	Hull.CalcMyWaters(6, 1, 17);
	Hull.CalcMyButtocks(12, -12, 12);

	Debug_If_Condition_Message(NOT Hull.IsDone(), "Making Hull is not performed");

	Hull.ExportMyModelToPlt(Plot);

	Hull.SetIGESFileName("MyHull.igs");
	Hull.ExportToIGES();
	Hull.ExportMySectionsToIGES();
}