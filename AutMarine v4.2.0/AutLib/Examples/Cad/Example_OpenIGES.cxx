#include <Examples\Cad\Example_Solid.hxx>

#include <TopoDS_Shape.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_SolidTools.hxx>
#include <IO_IGESRead.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace IoLib;

void AutLib::Example_Solid::OpenIGES()
{
	TopoDS_Shape Shape;
	IO_IGESRead::ReadFile("MyPropeller.igs", Shape);

	Cad3d_Solid Solid;
	Solid.Make(Cad3d_SolidTools::GetSurfaces(Shape));

	Open_OutputFile_TecPlot(Plot, "Example_OpenIGES");
	Solid.ExportToPlt(Plot);
}