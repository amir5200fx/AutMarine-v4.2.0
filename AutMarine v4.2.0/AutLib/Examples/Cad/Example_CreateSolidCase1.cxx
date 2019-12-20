#include <Examples\Cad\Example_Solid.hxx>

#include <Cad3d_Solid.hxx>
#include <Cad3d_MakeSolid.hxx>
#include <Cad3d_SolidTools.hxx>
#include <Cad3d_SurfaceOnSolidTools.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <Mesh3d_SolidMesher.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;

#include <TopoDS_Shape.hxx>

void AutLib::Example_Solid::CreateSolidCase1()
{
	Open_OutputFile_TecPlot(Plot, "Example_CreateSolidCase1");

	TopoDS_Shape Shape = Cad3d_MakeSolid::Box(Geom_Pnt3d(0, 0, 0), Geom_Pnt3d(1, 1, 1));
	
	Cad3d_Solid Solid;
	Solid.Make(Cad3d_SolidTools::GetSurfaces(Shape));

	//Solid.ExportSurfacesToPlt(Plot);
	//Solid.ExportNormalsToPlt(Plot, 0.1);

	SizeMap3d_UniSize UniSize(0.08);

	Mesh3d_SolidMesher Mesher(UniSize, Solid);
	Mesher.SetVerbosity(1);
	Mesher.Perform();

	Debug_If_Condition_Message(NOT Mesher.IsDone(), "The Ship is not discretized!");

	Mesher.ExportMeshToPlt(Plot);
	Mesher.ExportNormalsToPlt(Plot);
}