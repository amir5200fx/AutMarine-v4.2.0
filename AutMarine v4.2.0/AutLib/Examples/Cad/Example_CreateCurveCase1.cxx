#include <Examples\Cad\Example_Plane.hxx>

#include <Cad2d_CurveOnPlane.hxx>

using namespace AutLib;
using namespace CadLib;

void AutLib::Example_Plane::CreateCurveCase1()
{
	Open_OutputFile_TecPlot(Plot, "Example_CreateCurveCase1");

	TColGeom_BasicQueueOfPnt2d Points;
	Points.EnQueue(Geom_Pnt2d());
	Points.EnQueue(Geom_Pnt2d(0.1, 0.3));
	Points.EnQueue(Geom_Pnt2d(0.15, 0.68));
	Points.EnQueue(Geom_Pnt2d(0.175, 1.05));
	Points.EnQueue(Geom_Pnt2d(0.19, 1.1));
	Points.EnQueue(Geom_Pnt2d(0.2, 1.15));
	Points.EnQueue(Geom_Pnt2d(0.21, 1.15));
	Points.EnQueue(Geom_Pnt2d(0.22, 1.05));
	Points.EnQueue(Geom_Pnt2d(0.24, 0.75));
	Points.EnQueue(Geom_Pnt2d(0.3, 0.55));
	Points.EnQueue(Geom_Pnt2d(0.55, 0.23));
	Points.EnQueue(Geom_Pnt2d(0.8, 0.21));
	Points.EnQueue(Geom_Pnt2d(1.2, 0.18));

	Cad2d_CurveOnPlane Curve;
	Curve.Interpolation(Points);

	Curve.ExportToPlt(Plot);
}