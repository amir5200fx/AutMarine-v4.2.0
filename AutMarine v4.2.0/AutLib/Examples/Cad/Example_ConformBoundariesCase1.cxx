#include <Examples\Cad\Example_Solid.hxx>

#include <IO_IGESRead.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_SolidTools.hxx>

#include <TopoDS_Shape.hxx>

using namespace AutLib;
using namespace CadLib;

void AutLib::Example_Solid::ConformBoundariesCase1()
{
	Open_OutputFile_txt(ReportFile, "Example_ConformBoundariesCase1");
	Open_OutputFile_TecPlot(Plot, "Example_ConformBoundariesCase1");

	TopoDS_Shape Shape;
	M_IO IO_IGESRead::ReadFile("rod.igs", Shape, 0.01, 1.0);

	Cad3d_Solid Solid, Conformed;
	Cad3d_SolidTools::MakeSolid(Shape, Solid);

	Cad3d_SolidTools::ConformBoundaries(Solid, Conformed, 1.0E-4);

	Solid.Report(ReportFile);
	Conformed.Report(ReportFile);

	Solid.ExportShellsToPlt(Plot);
	Conformed.ExportShellsToPlt(Plot);
}