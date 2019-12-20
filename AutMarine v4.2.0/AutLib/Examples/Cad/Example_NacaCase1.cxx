#include <Examples\Cad\Example_Plane.hxx>

#include <Model2d_Naca4Digit.hxx>
#include <Cad2d_MakePlane.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_BlockEdgeOnPlane.hxx>
#include <Cad2d_BooleanOperators.hxx>

using namespace AutLib;
using namespace CadLib;

#include <gp_Ax22d.hxx>

void AutLib::Example_Plane::NacaCase1()
{
	Open_OutputFile_TecPlot(Plot, "Example_NacaCase1");

	Cad2d_MakePlane Box;
	Box.Box(Geom_Pnt2d(), Geom_Pnt2d(2.0, 1.0));

	Model2d_Naca4Digit Naca;
	Naca.Parameters().Init(0.5, 4, 40, 10);
	Naca.Perform();

	gp_Ax22d A(gp_Pnt2d(0.75, 0.5), gp_Dir2d(1.0, 0));

	Global_Handle(Cad2d_Plane) Shape = Naca.ExportAsPart(A);

	Cad2d_Plane Sum;
	Cad2d_BooleanOperators::Subtract(&Box, Shape, &Sum);
	Sum.ExportToPlt(Plot);
	Sum.Report();

	Open_OutputFile_txt(Report, "Example_NacaCase1");

	Get_Pointer(Edges) = Sum.Edges();

	Get_Const_Pointer(OutterBlock) = Edges->SelectBlockCurve("Default Block Edge");
	Debug_Null_Pointer(OutterBlock);

	OutterBlock->SelectCurve(4);
	Edges->Split("Inlet");

	OutterBlock = Edges->SelectBlockCurve("Default Block Edge");
	OutterBlock->SelectCurve(2);
	Edges->Split("Outlet");

	OutterBlock = Edges->SelectBlockCurve("Default Block Edge");
	Edges->RenameBlock("Wall");

	Get_Const_Pointer(InnerBlock) = Edges->SelectBlockCurve("Default Inner Block 1");
	Debug_Null_Pointer(InnerBlock);

	Edges->RenameBlock("Body");

	Edges->Print(Standard_True, Report);

	FreePointer(Shape);

	/*Global_Handle(Cad2d_Plane) Copy = Sum.Copy();

	Get_Const_Pointer(Edges1) = Copy->Edges();
	Edges1->Print(Standard_True);

	FreePointer(Copy);*/
}