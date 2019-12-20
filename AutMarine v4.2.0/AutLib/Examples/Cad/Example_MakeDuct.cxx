#include <Examples\Cad\Example_Solid.hxx>

#include <Duct_Hull.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_BlockEntityOnSolid.hxx>

using namespace AutLib;
using namespace CadLib;

void AutLib::Example_Solid::MakeDuctCase1()
{
	Open_OutputFile_TecPlot(Plot, "Example_MakeDuctCase1");

	Duct_Hull Duct;
	Duct.Make();

	Duct.ExportToIGES();
}