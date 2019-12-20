#include <Examples\Cad\Example_Plane.hxx>

#include <Cad2d_Plane.hxx>
#include <Cad2d_MakePlane.hxx>

using namespace AutLib;
using namespace CadLib;

void AutLib::Example_Plane::SharpCornersCase1()
{
	Open_OutputFile_TecPlot(Plot, "Example_MeshCase2");

	Cad2d_MakePlane Box;
	Box.Box(Geom_Pnt2d(), Geom_Pnt2d(0.3, 1.2));

	Get_Pointer(Corners) = Box.Corners();
	Debug_Null_Pointer(Corners);

	Corners->Print(Standard_True);

	Box.CreateSharpCornerBlock(100, "Default Sharp Corners");

	Corners->Print(Standard_True);
}