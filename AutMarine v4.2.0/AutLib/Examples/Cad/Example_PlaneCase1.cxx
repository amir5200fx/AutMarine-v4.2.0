#include <Examples\Cad\Example_Plane.hxx>

#include <Cad2d_MakePlane.hxx>

using namespace AutLib;
using namespace CadLib;

#include <gp_Ax22d.hxx>

void AutLib::Example_Plane::PlaneCase1()
{
	Open_OutputFile_TecPlot(Plot, "Example_PlaneCase1");

	gp_Ax2d A(gp_Pnt2d(0.3, 0.85), gp_Dir2d(1.0, 0.3));

	Cad2d_MakePlane Shape;
	Shape.Box(A, 0.68, 0.17);

	Shape.ExportToPlt(Plot);
}