#include <Examples\Cad\Example_Solid.hxx>

#include <Rudder.hxx>

using namespace AutLib;
using namespace CadLib;

void AutLib::Example_Solid::MakeRudderCase1()
{
	Open_OutputFile_TecPlot(Plot, "Example_MakeRudderCase1");

	Rudder MarineRudder;

	MarineRudder.SetToDiscreteMyModel();
	MarineRudder.SetToMakeShaft();
	MarineRudder.SetToMakeAsSolid();

	MarineRudder.Make();

	MarineRudder.ExportMyModelToPlt(Plot);

	MarineRudder.SetIGESFileName("MyRudder.igs");
	MarineRudder.ExportToIGES();
}