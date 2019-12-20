#include <Examples\Mesh\Example_SolidMesher.hxx>

#include <Prop_Propeller.hxx>
#include <Cad3d_SolidTools.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <Mesh3d_SolidMesher.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;

void AutLib::Example_SolidMesher::Case2()
{

	Open_OutputFile_TecPlot(Plot, "Example_SolidMesherCase2");

	Prop_Propeller Propeller;
	Propeller.Parameters().SetToRemoveHubApex();
	Propeller.Parameters().HubParameters().SetShaftLength(0);
	Propeller.SetName("My Propeller");
	Propeller.Make();

	SizeMap3d_UniSize UniSize(0.05);

	Mesh3d_SolidMesher Mesher(UniSize, *Propeller.GetSolid());
	Mesher.SetVerbosity(1);
	Mesher.Perform();

	Debug_If_Condition_Message(NOT Mesher.IsDone(), "The Ship is not discretized!");

	Mesher.ExportMergedMeshToPlt(Plot);
}