#include <Examples\Cad\Example_Solid.hxx>

#include <Geom_Pnt3d.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_MakeSolid.hxx>
#include <Cad3d_SolidTools.hxx>

#include <TopoDS_Shape.hxx>
#include <BRepOffsetAPI_MakeOffsetShape.hxx>

using namespace AutLib;
using namespace CadLib;

void AutLib::Example_Solid::OffsetShapeCase1()
{
	Open_OutputFile_TecPlot(Plot, "Example_OffsetShapeCase1");

	TopoDS_Shape Box = Cad3d_MakeSolid::Box(Geom_Pnt3d(0, 0, 0), Geom_Pnt3d(3, 1, 0.5));

	BRepOffsetAPI_MakeOffsetShape Offset;
	Offset.PerformByJoin(Box, -0.25, 1.0E-6);

	TopoDS_Shape New = Offset.Shape();
	Cad3d_SolidTools::Triangulation(New);

	Offset.PerformByJoin(New, 0.5, 1.0E-4);

	TopoDS_Shape New1 = Offset.Shape();
	Cad3d_SolidTools::Triangulation(New1);

	Cad3d_SolidTools::ExportToPlt(Box, Plot);
	Cad3d_SolidTools::ExportToPlt(New, Plot);
	Cad3d_SolidTools::ExportToPlt(New1, Plot);
}