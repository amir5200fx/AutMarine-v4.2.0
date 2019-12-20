#include <Examples\Cad\Example_Intersection.hxx>

#include <Cad2d_MakePlane.hxx>
#include <Cad2d_PlanePlaneSubdivide.hxx>

using namespace AutLib;
using namespace CadLib;

#include <gp_Ax22d.hxx>

void AutLib::Example_Intersection::PlanePlaneSubdivideCase1()
{
	Open_OutputFile_TecPlot(Plot, "PlanePlaneSubdivideCase1");

	Cad2d_MakePlane Box, Circle;
	Box.Box(Geom_Pnt2d(), Geom_Pnt2d(0.3, 1.2));
	Circle.Circle(gp_Ax2d(Geom_Pnt2d(0.4, 0.5), gp_Dir2d(1.0, 0)), 0.5);

	//Box.ExportToPlt(Plot);
	//Circle.ExportToPlt(Plot);

	Cad2d_PlanePlaneSubdivide Intersection(&Box, &Circle);
	Intersection.Perform();

	Intersection.ExportToPlt(Plot);
}