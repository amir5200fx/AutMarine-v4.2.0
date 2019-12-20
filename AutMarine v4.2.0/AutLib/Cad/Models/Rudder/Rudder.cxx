#include <Rudder.hxx>

#include <Cad3d_MakeSolid.hxx>
#include <IO_Tecplot.hxx>

#include <gp_Trsf.hxx>
#include <gp_Ax2.hxx>
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <GeomAPI_IntCS.hxx>
#include <Geom_Surface.hxx>
#include <Geom_Plane.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_SurfaceOfLinearExtrusion.hxx>
#include <GeomFill_BSplineCurves.hxx>
#include <GeomConvert.hxx>
#include <BRep_Tool.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepOffsetAPI_Sewing.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Solid.hxx>
#include <TopExp_Explorer.hxx>
#include <TColGeom_Array1OfBSplineCurve.hxx>

using namespace AutLib;
using namespace CadLib;

AutLib::CadLib::Rudder::Rudder()
	: toMakeShaft_(Standard_False)
{
	DefaultParameters();

	theSystem_ = gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
}

AutLib::CadLib::Rudder::~Rudder()
{
}

void AutLib::CadLib::Rudder::DefaultParameters()
{
	theSection_.SetNbOffsets(20);

	theParameters_.SetChord(3.0);
	theParameters_.SetSpan(5.0);
	theParameters_.SetThickness(40);

	theParameters_.SetShaftLength(4.0);
	theParameters_.SetShaftPosition(0.25);
	theParameters_.SetShaftDiameter(0.8);
}

void AutLib::CadLib::Rudder::Make()
{
	theSection_.SetChord(theParameters_.Chord());
	theSection_.SetThickness(theParameters_.Thickness());

	theSection_.Perform();

	Debug_If_Condition_Message(NOT theSection_.IsDone(), "The Section is not Created");

	CreateMyFaces();

	MakeClosedRudder();

	if (toMakeShaft_)
	{
		MakeShaft();
	}

	if (toSolid_)
	{
		MakeSolid();
	}
	else
	{
		//if (toMakeShaft_) myModel_ = BRepAlgoAPI_Fuse(myModel_, myShaft_);
	}

	if (toMakeShaft_)
	{
		Standard_Real X = theParameters_.ShaftPosition()*theParameters_.Chord();
		Geom_Pnt3d C(X, 0, theParameters_.Span());

		gp_Trsf Trsf;
		Trsf.SetTranslation(C, gp_Pnt(0, 0, 0));

		BRepBuilderAPI_Transform Transform(Trsf);
		Transform.Perform(myModel_, Standard_True);
		myModel_ = Transform.Shape();

		theSystem_.SetLocation(gp_Pnt(0, 0, 0));
	}
	else
	{
		Geom_Pnt3d C(0, 0, -theParameters_.Span());
		Cad3d_MarineModel::TransformTo(gp_Ax2(C, gp_Dir(0, 0, 1), gp_Dir(1, 0, 0)));

		gp_Trsf Trsf;
		Trsf.SetTranslation(C, gp_Pnt(0, 0, 0));

		BRepBuilderAPI_Transform Transform(Trsf);
		Transform.Perform(myModel_, Standard_True);
		myModel_ = Transform.Shape();

		theSystem_.SetLocation(gp_Pnt(0, 0, 0));
	}

	if (toDiscrete_)
	{
		Cad3d_MarineModel::DiscreteMyModel();
	}
}

void AutLib::CadLib::Rudder::SetToMakeShaft()
{
	toMakeShaft_ = Standard_True;
}

void AutLib::CadLib::Rudder::CreateMyFaces()
{
	Handle(Geom_Surface) Upper = new Geom_SurfaceOfLinearExtrusion(theSection_.UpperCurve(), gp_Dir(0, 0, 1));
	Handle(Geom_Surface) Lower = new Geom_SurfaceOfLinearExtrusion(theSection_.LowerCurve(), gp_Dir(0, 0, 1));

	BRepBuilderAPI_MakeFace UpperFace(Upper, theSection_.UpperCurve()->FirstParameter(), theSection_.UpperCurve()->LastParameter(), 0, theParameters_.Span(), 1.0E-6);
	BRepBuilderAPI_MakeFace LowerFace(Lower, theSection_.LowerCurve()->FirstParameter(), theSection_.LowerCurve()->LastParameter(), 0, theParameters_.Span(), 1.0E-6);

	Debug_If_Condition_Message(NOT UpperFace.IsDone(), "MakeFace is not performed");
	Debug_If_Condition_Message(NOT LowerFace.IsDone(), "MakeFace is not performed");

	myModel_ = BRepAlgoAPI_Fuse(UpperFace.Shape(), LowerFace.Shape());
}

void AutLib::CadLib::Rudder::MakeClosedRudder()
{
	TColGeom_Array1OfBSplineCurve Curves(1, 8);
	Standard_Integer K = 0;
	for (TopExp_Explorer Explorer(myModel_, TopAbs_EDGE); Explorer.More(); Explorer.Next())
	{
		TopoDS_Edge Edge = TopoDS::Edge(Explorer.Current());
		TopLoc_Location Loc;
		Standard_Real First, Last;
		Handle(Geom_Curve) Curve = BRep_Tool::Curve(Edge, First, Last);

		Handle(Geom_BSplineCurve) BSplCurve = Handle(Geom_BSplineCurve)::DownCast(Curve);
		if (BSplCurve.IsNull())
		{
			Handle(Geom_TrimmedCurve) Trimmed = new Geom_TrimmedCurve(Curve, First, Last);
			BSplCurve = GeomConvert::CurveToBSplineCurve(Trimmed);
		}
		if (BSplCurve.IsNull()) { THROW_STANDARD_EXCEPTION(" Null Curve"); }
		
		Curves.SetValue(++K, BSplCurve);
	}

	GeomFill_BSplineCurves Root(Curves.Value(2), Curves.Value(6), GeomFill_CoonsStyle);
	myModel_ = BRepAlgoAPI_Fuse(myModel_, BRepBuilderAPI_MakeFace(Root.Surface(), 1.0E-6));

	GeomFill_BSplineCurves TE(Curves.Value(4), Curves.Value(8), GeomFill_CoonsStyle);
	myModel_ = BRepAlgoAPI_Fuse(myModel_, BRepBuilderAPI_MakeFace(TE.Surface(), 1.0E-6));

	GeomFill_BSplineCurves Tip(Curves.Value(3), Curves.Value(7), GeomFill_CoonsStyle);
	myModel_ = BRepAlgoAPI_Fuse(myModel_, BRepBuilderAPI_MakeFace(Tip.Surface(), 1.0E-6));
}

void AutLib::CadLib::Rudder::MakeShaft()
{
	Handle(Geom_Curve) Curve = theSection_.UpperCurve();
	Standard_Real X = theParameters_.ShaftPosition()*theParameters_.Chord();

	Handle(Geom_Plane) Plane = new Geom_Plane(gp_Pnt(X, 0, 0), gp_Dir(1, 0, 0));

	GeomAPI_IntCS Intersection;
	Intersection.Perform(Curve, Plane);

	if (Intersection.NbPoints() NOT_EQUAL 1) { THROW_STANDARD_EXCEPTION("Invalid Data"); }

	Standard_Real Radius = 0.85*MIN(Intersection.Point(1).Y()* theParameters_.ShaftDiameter(), X);

	//Geom_Pnt3d C(X, 0, theParameters_.Span() - 0.001*theParameters_.Span());
	Geom_Pnt3d C(X, 0, theParameters_.Span());

	myShaft_ = Cad3d_MakeSolid::Cylinder(gp_Ax2(C, gp_Dir(0, 0, 1)), Radius, theParameters_.ShaftLength());
}

void AutLib::CadLib::Rudder::MakeSolid()
{
	BRepOffsetAPI_Sewing Sewing;
	Sewing.Add(myModel_);
	Sewing.Perform();

	TopoDS_Shape Sewed = Sewing.SewedShape();

	BRepBuilderAPI_MakeSolid brep_solid2(TopoDS::Shell(Sewed));
	myModel_ = brep_solid2.Solid();

	if (toMakeShaft_)
	{
		gp_Trsf Translation;
		Translation.SetTranslation(gp_Vec(0, 0, -0.001*theParameters_.Span()));

		BRepBuilderAPI_Transform Transform(Translation);
		Transform.Perform(myShaft_);
		myShaft_ = Transform.ModifiedShape(myShaft_);
	}

	if (toMakeShaft_) myModel_ = BRepAlgoAPI_Cut(myModel_, myShaft_);
}
