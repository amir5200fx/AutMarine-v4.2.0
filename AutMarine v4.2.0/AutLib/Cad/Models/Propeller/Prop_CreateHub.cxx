#include <Prop_Propeller.hxx>

#include <Entity_Box3d.hxx>
#include <Entity_Box3dTools.hxx>
#include <Prop_WrappedSection.hxx>

using namespace AutLib;
using namespace GeoLib;

#include <gp_Lin.hxx>
#include <gp_Trsf.hxx>
#include <Geom_Line.hxx>
#include <Geom_BSplineCurve.hxx>
#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Builder.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepPrimAPI_MakeRevolution.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <GeomFill_BSplineCurves.hxx>
#include <TColgp_Array1OfPnt.hxx>

void AutLib::CadLib::Prop_Propeller::MakeMyHub()
{
	Get_Const_Object(Wrapped) = thePropView_.WrappedSection(0);
	Entity_Box3d Box = Entity_Box3dTools::BoxOf(Wrapped->BackOffsets(), 0);
	Box.Expand(0.25*(Box.Zmax() - Box.Zmin()));

	//gp_Trsf Trsf;
	//Trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), M_PI);

	//BRepBuilderAPI_Transform Transform(Trsf);

	TopoDS_Compound Compound;
	TopoDS_Builder Builder;
	Builder.MakeCompound(Compound);

	Standard_Real Zmin = Box.Zmin();
	Standard_Real Zmax = Box.Zmax();
	Standard_Real HubRadius = theParameters_.HubRadius() + 0.001*theParameters_.HubRadius();
	//cout << Zmin << "   " << Zmax << endl;
	Geom_Pnt3d P0(HubRadius, 0, Zmin);
	Geom_Pnt3d P1(HubRadius, 0, Zmax);

	Standard_Integer NbPoles = 2;
	Standard_Integer Degree = 1;

	TColgp_Array1OfPnt Poles0(1, NbPoles);
	Poles0.SetValue(1, P0);
	Poles0.SetValue(2, P1);

	TColStd_Array1OfReal Weights0(1, NbPoles);
	Weights0.Init(1);

	TColStd_Array1OfReal Knots0(1, 2);
	Knots0.SetValue(1, 0);
	Knots0.SetValue(2, 1);

	TColStd_Array1OfInteger Mults0(1, 2);
	Mults0.SetValue(1, 2);
	Mults0.SetValue(2, 2);

	Handle(Geom_BSplineCurve) Curve0 = new Geom_BSplineCurve(Poles0, Weights0, Knots0, Mults0, Degree);

	BRepPrimAPI_MakeRevolution Rev0(Curve0, Curve0->FirstParameter(), Curve0->LastParameter(), 2 * M_PI);
	//cout << Curve0->FirstParameter() << "   " << Curve0->LastParameter() << endl;
	
	//cout << Rev0.IsDone() << endl;
	//PAUSE;
	//Debug_If_Condition_Message(NOT Rev0.IsDone(), "Revolution is not performed");

	//myHub_ = Rev0.Face();
	Builder.Add(Compound, Rev0.Face());

	//Transform.Perform(Rev0.Face(), Standard_True);
	//myHub_ = BRepAlgoAPI_Fuse(myHub_, Transform.Shape());
	//Builder.Add(Compound, Transform.Shape());

	Standard_Real X0 = 0;
	if (theParameters_.RemoveHubApex()) X0 = 0.1*HubRadius;
	//Standard_Real X0 = 0;

	NbPoles = 3;
	Degree = 2;

	Geom_Pnt3d P2(X0, 0, Zmin - theParameters_.HubParameters().HubLength());
	Geom_Pnt3d P3(HubRadius, 0, Zmin - theParameters_.HubParameters().HubLength());
	Geom_Pnt3d P4 = P0;

	P3 = P3 + theParameters_.HubParameters().HubWeight()*(P4 - P3);

	if (theParameters_.HubParameters().HubLength() > 0)
	{
		TColgp_Array1OfPnt Poles1(1, NbPoles);
		Poles1.SetValue(1, P2);
		Poles1.SetValue(2, P3);
		Poles1.SetValue(3, P4);

		TColStd_Array1OfReal Weights1(1, NbPoles);
		Weights1.Init(1);

		TColStd_Array1OfReal Knots1(1, 2);
		Knots1.SetValue(1, 0);
		Knots1.SetValue(2, 1);

		TColStd_Array1OfInteger Mults1(1, 2);
		Mults1.SetValue(1, 3);
		Mults1.SetValue(2, 3);

		Handle(Geom_BSplineCurve) Curve1 = new Geom_BSplineCurve(Poles1, Weights1, Knots1, Mults1, Degree);

		BRepPrimAPI_MakeRevolution Rev1(Curve1, Curve1->FirstParameter(), Curve1->LastParameter(), 2 * M_PI);

		//Debug_If_Condition_Message(NOT Rev1.IsDone(), "Revolution is not performed");

		//myHub_ = BRepAlgoAPI_Fuse(myHub_, Rev1.Face());
		Builder.Add(Compound, Rev1.Face());

		//Transform.Perform(Rev1.Face(), Standard_True);
		//myHub_ = BRepAlgoAPI_Fuse(myHub_, Transform.Shape());
		//Builder.Add(Compound, Transform.Shape());
	}

	Geom_Pnt3d P5 = P1;
	Geom_Pnt3d P6(theParameters_.HubParameters().ShaftRadius(), 0, Zmax + theParameters_.HubParameters().ShaftOffset());

	NbPoles = 2;
	Degree = 1;

	TColgp_Array1OfPnt Poles2(1, NbPoles);
	Poles2.SetValue(1, P5);
	Poles2.SetValue(2, P6);

	TColStd_Array1OfReal Weights2(1, NbPoles);
	Weights2.Init(1);

	TColStd_Array1OfReal Knots2(1, 2);
	Knots2.SetValue(1, 0);
	Knots2.SetValue(2, 1);

	TColStd_Array1OfInteger Mults2(1, 2);
	Mults2.SetValue(1, 2);
	Mults2.SetValue(2, 2);

	Handle(Geom_BSplineCurve) Curve2 = new Geom_BSplineCurve(Poles2, Weights2, Knots2, Mults2, Degree);

	BRepPrimAPI_MakeRevolution Rev2(Curve2, Curve2->FirstParameter(), Curve2->LastParameter(), 2 * M_PI);

	//Debug_If_Condition_Message(NOT Rev2.IsDone(), "Revolution is not performed");

	//myHub_ = BRepAlgoAPI_Fuse(myHub_, Rev2.Face());
	Builder.Add(Compound, Rev2.Face());

	//Transform.Perform(Rev2.Face(), Standard_True);
	//myHub_ = BRepAlgoAPI_Fuse(myHub_, Transform.Shape());
	//Builder.Add(Compound, Transform.Shape());

	Geom_Pnt3d P7 = P6;
	Geom_Pnt3d P8(theParameters_.HubParameters().ShaftRadius(), 0, P7.Z() + theParameters_.HubParameters().ShaftLength());

	if (theParameters_.HubParameters().ShaftLength())
	{
		NbPoles = 2;
		Degree = 1;

		TColgp_Array1OfPnt Poles3(1, NbPoles);
		Poles3.SetValue(1, P7);
		Poles3.SetValue(2, P8);

		TColStd_Array1OfReal Weights3(1, NbPoles);
		Weights3.Init(1);

		TColStd_Array1OfReal Knots3(1, 2);
		Knots3.SetValue(1, 0);
		Knots3.SetValue(2, 1);

		TColStd_Array1OfInteger Mults3(1, 2);
		Mults3.SetValue(1, 2);
		Mults3.SetValue(2, 2);

		Handle(Geom_BSplineCurve) Curve3 = new Geom_BSplineCurve(Poles3, Weights3, Knots3, Mults3, Degree);

		BRepPrimAPI_MakeRevolution Rev3(Curve3, Curve3->FirstParameter(), Curve3->LastParameter(), 2 * M_PI);

		//Debug_If_Condition_Message(NOT Rev3.IsDone(), "Revolution is not performed");

		//myHub_ = BRepAlgoAPI_Fuse(myHub_, Rev3.Face());
		Builder.Add(Compound, Rev3.Face());

		//Transform.Perform(Rev3.Face(), Standard_True);
		//myHub_ = BRepAlgoAPI_Fuse(myHub_, Transform.Shape());
		//Builder.Add(Compound, Transform.Shape());
	}

	Geom_Pnt3d P9(0, 0, P8.Z());
	Geom_Pnt3d P10 = P8;

	NbPoles = 2;
	Degree = 1;

	TColgp_Array1OfPnt Poles4(1, NbPoles);
	Poles4.SetValue(1, P9);
	Poles4.SetValue(2, P10);

	TColStd_Array1OfReal Weights4(1, NbPoles);
	Weights4.Init(1);

	TColStd_Array1OfReal Knots4(1, 2);
	Knots4.SetValue(1, 0);
	Knots4.SetValue(2, 1);

	TColStd_Array1OfInteger Mults4(1, 2);
	Mults4.SetValue(1, 2);
	Mults4.SetValue(2, 2);

	Handle(Geom_BSplineCurve) Curve4 = new Geom_BSplineCurve(Poles4, Weights4, Knots4, Mults4, Degree);

	BRepPrimAPI_MakeRevolution Rev4(Curve4, Curve4->FirstParameter(), Curve4->LastParameter(), 2 * M_PI);

	//Debug_If_Condition_Message(NOT Rev4.IsDone(), "Revolution is not performed");

	//myHub_ = BRepAlgoAPI_Fuse(myHub_, Rev4.Face());
	Builder.Add(Compound, Rev4.Face());

	//Transform.Perform(Rev4.Face(), Standard_True);
	//myHub_ = BRepAlgoAPI_Fuse(myHub_, Transform.Shape());
	//Builder.Add(Compound, Transform.Shape());

	if (theParameters_.RemoveHubApex() AND theParameters_.HubParameters().HubLength() > 0)
	{
		Geom_Pnt3d P11 = P2;
		Geom_Pnt3d P12(0, 0, Zmin - theParameters_.HubParameters().HubLength());

		NbPoles = 2;
		Degree = 1;

		TColgp_Array1OfPnt Poles5(1, NbPoles);
		Poles5.SetValue(1, P11);
		Poles5.SetValue(2, P12);

		TColStd_Array1OfReal Weights5(1, NbPoles);
		Weights5.Init(1);

		TColStd_Array1OfReal Knots5(1, 2);
		Knots5.SetValue(1, 0);
		Knots5.SetValue(2, 1);

		TColStd_Array1OfInteger Mults5(1, 2);
		Mults5.SetValue(1, 2);
		Mults5.SetValue(2, 2);

		Handle(Geom_BSplineCurve) Curve5 = new Geom_BSplineCurve(Poles5, Weights5, Knots5, Mults5, Degree);

		BRepPrimAPI_MakeRevolution Rev5(Curve5, Curve5->FirstParameter(), Curve5->LastParameter(), 2 * M_PI);

		//Debug_If_Condition_Message(NOT Rev5.IsDone(), "Revolution is not performed");

		//myHub_ = BRepAlgoAPI_Fuse(myHub_, Rev5.Face());
		Builder.Add(Compound, Rev5.Face());

		//Transform.Perform(Rev5.Face(), Standard_True);
		//myHub_ = BRepAlgoAPI_Fuse(myHub_, Transform.Shape());
		//Builder.Add(Compound, Transform.Shape());
	}

	if (theParameters_.HubParameters().HubLength() EQUAL 0)
	{
		Geom_Pnt3d P11 = P0;
		Geom_Pnt3d P12(0, 0, Zmin);

		NbPoles = 2;
		Degree = 1;

		TColgp_Array1OfPnt Poles5(1, NbPoles);
		Poles5.SetValue(1, P11);
		Poles5.SetValue(2, P12);

		TColStd_Array1OfReal Weights5(1, NbPoles);
		Weights5.Init(1);

		TColStd_Array1OfReal Knots5(1, 2);
		Knots5.SetValue(1, 0);
		Knots5.SetValue(2, 1);

		TColStd_Array1OfInteger Mults5(1, 2);
		Mults5.SetValue(1, 2);
		Mults5.SetValue(2, 2);

		Handle(Geom_BSplineCurve) Curve5 = new Geom_BSplineCurve(Poles5, Weights5, Knots5, Mults5, Degree);

		BRepPrimAPI_MakeRevolution Rev5(Curve5, Curve5->FirstParameter(), Curve5->LastParameter(), 2 * M_PI);

		//Debug_If_Condition_Message(NOT Rev5.IsDone(), "Revolution is not performed");

		//myHub_ = BRepAlgoAPI_Fuse(myHub_, Rev5.Face());
		Builder.Add(Compound, Rev5.Face());

		//Transform.Perform(Rev5.Face(), Standard_True);
		//myHub_ = BRepAlgoAPI_Fuse(myHub_, Transform.Shape());
		//Builder.Add(Compound, Transform.Shape());
	}
	myHub_ = Compound;
}