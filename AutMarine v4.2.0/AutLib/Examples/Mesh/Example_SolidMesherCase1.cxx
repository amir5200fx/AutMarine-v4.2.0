#include <Examples\Mesh\Example_SolidMesher.hxx>

#include <Ship_Hull.hxx>
#include <Cad3d_SolidTools.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <Mesh3d_SolidMesher.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;

void AutLib::Example_SolidMesher::Case1()
{

	Open_OutputFile_TecPlot(Plot, "Example_SolidMesherCase1");

	Ship_Hull Hull;
	Hull.SetName("My Ship");
	Hull.Make();
	
	SizeMap3d_UniSize UniSize(1.5);

	Mesh3d_SolidMesher Mesher(UniSize, *Hull.GetSolid());
	Mesher.SetVerbosity(1);
	Mesher.Perform();

	Debug_If_Condition_Message(NOT Mesher.IsDone(), "The Ship is not discretized!");

	Mesher.ExportMeshToPlt(Plot);
	Mesher.ExportNormalsToPlt(Plot);
}