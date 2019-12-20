#include <Examples\Cad\Example_Solid.hxx>

#include <Prop_Propeller.hxx>

using namespace AutLib;
using namespace CadLib;

void AutLib::Example_Solid::MakePropellerReadFile()
{
	fstream InputParameters;
	InputParameters.open("MyPropellerParameters.txt", ios::in);

	Prop_Propeller Propeller;

	Get_Object(Parameters) = Propeller.Parameters();
	Parameters.SetToRemoveHubApex();
	Parameters.Import(InputParameters);

	Propeller.Make();

	Propeller.SetIGESFileName("MyPropeller.igs");
	Propeller.ExportToIGES();
}