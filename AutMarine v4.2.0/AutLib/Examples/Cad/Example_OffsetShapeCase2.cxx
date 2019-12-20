#include <Examples\Cad\Example_Solid.hxx>

#include <Geom_Pnt3d.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_MakeSolid.hxx>
#include <Cad3d_SolidTools.hxx>
#include <Ship_Hull.hxx>
#include <Prop_Propeller.hxx>

#include <TopoDS_Shape.hxx>
#include <BRepOffsetAPI_MakeOffsetShape.hxx>

using namespace AutLib;
using namespace CadLib;

void AutLib::Example_Solid::OffsetShapeCase2()
{
	Open_OutputFile_TecPlot(Plot, "Example_OffsetShapeCase2");

	Prop_Propeller Propeller;

	Get_Object(Parameters) = Propeller.Parameters();
	Parameters.SetToRemoveHubApex();

	Get_Object(Hub) = Parameters.HubParameters();
	//Hub.SetHubLength(0);
	Hub.SetShaftLength(0);

	Propeller.SetToDiscreteMyModel();
	Propeller.Make();

	TopoDS_Shape Shape = Propeller.Shape();

	BRepOffsetAPI_MakeOffsetShape Offset;
	Offset.PerformByJoin(Shape, 0.1, 1.0e-6);

	TopoDS_Shape Offset1 = Offset.Shape();
	Cad3d_SolidTools::Triangulation(Offset1, 0.05, 0.25);

	Cad3d_SolidTools::ExportToPlt(Shape, Plot);
	Cad3d_SolidTools::ExportToPlt(Offset1, Plot);
}