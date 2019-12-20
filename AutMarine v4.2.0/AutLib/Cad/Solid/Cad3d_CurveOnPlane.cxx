#include <Cad3d_CurveOnPlane.hxx>

#include <Entity_Box2d.hxx>
#include <Entity_Polygon2d.hxx>
#include <Geometry_Sort.hxx>
#include <IO_Tecplot.hxx>
#include <TColStd_BasicQueueOfReal.hxx>
#include <TColCad3d_HBasicQueueOfCurveOnPlane.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace CadLib;

#include <Bnd_Box2d.hxx>
#include <BndLib_Add2dCurve.hxx>
#include <Geom2d_Curve.hxx>

AutLib::CadLib::Cad3d_CurveOnPlane::Cad3d_CurveOnPlane()
	: theFirst_(0)
	, theLast_(0)
{
}

AutLib::CadLib::Cad3d_CurveOnPlane::Cad3d_CurveOnPlane
(
	const Standard_Real theFirstParameter,
	const Standard_Real theLastParameter,
	const Handle(Geom2d_Curve)& theCurve
)
	: theFirst_(theFirstParameter)
	, theLast_(theLastParameter)
{
	theCurve_ = theCurve;
}

void AutLib::CadLib::Cad3d_CurveOnPlane::Init
(
	const Standard_Real theFirstParameter,
	const Standard_Real theLastParameter,
	const Handle(Geom2d_Curve)& theCurve
)
{
	theFirst_ = theFirstParameter;
	theLast_ = theLastParameter;
	theCurve_ = theCurve;
}

Geom_Pnt2d AutLib::CadLib::Cad3d_CurveOnPlane::FirstCoord() const
{
	Debug_Null_Pointer(theCurve_);
	return theCurve_->Value(theFirst_);
}

Geom_Pnt2d AutLib::CadLib::Cad3d_CurveOnPlane::LastCoord() const
{
	Debug_Null_Pointer(theCurve_);
	return theCurve_->Value(theLast_);
}

Geom_Pnt2d AutLib::CadLib::Cad3d_CurveOnPlane::MidCoord() const
{
	Debug_Null_Pointer(theCurve_);
	return theCurve_->Value(MEAN(theFirst_, theLast_));
}

Geom_Pnt2d AutLib::CadLib::Cad3d_CurveOnPlane::Value(const Standard_Real theParameter) const
{
	Debug_Null_Pointer(theCurve_);
	return theCurve_->Value(theParameter);
}

Geom_Pnt2d AutLib::CadLib::Cad3d_CurveOnPlane::NormalizedParameterValue(const Standard_Real theParameter) const
{
	Debug_Null_Pointer(theCurve_);
	return theCurve_->Value(theFirst_ + theParameter*(theLast_ - theFirst_));
}

Entity_Box2d AutLib::CadLib::Cad3d_CurveOnPlane::BoundingBox(const Standard_Real theTolerance) const
{
	Debug_Null_Pointer(theCurve_);
	Bnd_Box2d BndBox;
	BndLib_Add2dCurve::Add(theCurve_, theFirst_, theLast_, theTolerance, BndBox);

	Standard_Real Xmin, Xmax, Ymin, Ymax;
	BndBox.Get(Xmin, Ymin, Xmax, Ymax);
	return Entity_Box2d(Xmin, Xmax, Ymin, Ymax);
}

Entity_Polygon2d AutLib::CadLib::Cad3d_CurveOnPlane::UniformParametricDiscretize(const Standard_Integer NbSegments) const
{
	if (NbSegments < 1) { THROW_STANDARD_EXCEPTION("Invalid Nb. of Segments"); }

	Entity_Polygon2d Polygon;
	Get_Object(Points) = Polygon.Points();

	Points.Resize(NbSegments + 1);

	Standard_Real Du = (LastParameter() - FirstParameter()) / (Standard_Real)(NbSegments);
	Standard_Real U0 = FirstParameter();

	Points.SetFirst(FirstCoord());

	forThose
	(
		Index,
		1,
		NbSegments - 1
	)
	{
		Standard_Real Parameter = (Standard_Real)Index*Du + U0;
		Points.SetValue(Index, Value(Parameter));
	}

	Points.SetLast(LastCoord());

	MOVE(Polygon);
}

void AutLib::CadLib::Cad3d_CurveOnPlane::Split
(
	const Standard_Real theParameter,
	Global_Handle(Cad3d_CurveOnPlane) theCurve1,
	Global_Handle(Cad3d_CurveOnPlane) theCurve2
) const
{
	if (NOT INSIDE(theParameter, theFirst_, theLast_)) { THROW_STANDARD_EXCEPTION("Bad Parameter"); }

	Debug_Null_Pointer(theCurve1);
	Debug_Null_Pointer(theCurve2);

	theCurve1->SetCurve(theCurve_);
	theCurve1->SetFirst(theFirst_);
	theCurve1->SetLast(theParameter);

	theCurve2->SetCurve(theCurve_);
	theCurve2->SetFirst(theParameter);
	theCurve2->SetLast(theLast_);
}

void AutLib::CadLib::Cad3d_CurveOnPlane::Split
(
	const Standard_Real theParameter, 
	Geom_Pnt2d & theCoord, 
	Global_Handle(Cad3d_CurveOnPlane) theCurve1,
	Global_Handle(Cad3d_CurveOnPlane) theCurve2
) const
{
	if (NOT INSIDE(theParameter, theFirst_, theLast_)) { THROW_STANDARD_EXCEPTION("Bad Parameter"); }

	Debug_Null_Pointer(theCurve1);
	Debug_Null_Pointer(theCurve2);

	theCurve1->SetCurve(theCurve_);
	theCurve1->SetFirst(theFirst_);
	theCurve1->SetLast(theParameter);

	theCurve2->SetCurve(theCurve_);
	theCurve2->SetFirst(theParameter);
	theCurve2->SetLast(theLast_);

	theCoord = theCurve_->Value(theParameter);
}

void AutLib::CadLib::Cad3d_CurveOnPlane::Split
(
	const TColStd_Ary1dOfReal & theParameters, 
	TColGeom_Ary1dOfPnt2d & theCoords, 
	TColCad3d_HAry1dOfCurveOnPlane & theCurves,
	const Standard_Real theTolerance
) const
{
	TColStd_Ary1dOfReal Parameters = theParameters;
	Geometry_Sort<Standard_Real>::Sort(Parameters);

	TColStd_BasicQueueOfReal QParameters;
	forThose(Index, 0, MaxIndexOf(Parameters))
		if (NOT ABS(Parameters[Index] - theFirst_) < theTolerance OR NOT ABS(Parameters[Index] - theLast_) < theTolerance) QParameters.EnQueue(Parameters[Index]);
	QParameters.RetrieveTo(Parameters);

	/*if (NOT INSIDE(Parameters.First(), theFirst_, theLast_)) { THROW_STANDARD_EXCEPTION("Bad Parameter"); }
	if (NOT INSIDE(Parameters.Last(), theFirst_, theLast_)) { THROW_STANDARD_EXCEPTION("Bad Parameter"); }*/

	theCoords.Resize(theParameters.Size());

	const Global_Handle(Cad3d_CurveOnPlane) Curve = this;

	Geom_Pnt2d Coord;

	TColCad3d_HBasicQueueOfCurveOnPlane QCurves;
	TColCad3d_HBasicQueueOfCurveOnPlane QRemoved;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Parameters)
	)
	{
		Standard_Real Parameter = Parameters[Index];

		Global_Handle(Cad3d_CurveOnPlane) Curve1 = new Cad3d_CurveOnPlane;
		Global_Handle(Cad3d_CurveOnPlane) Curve2 = new Cad3d_CurveOnPlane;

		Curve->Split(Parameter, Coord, Curve1, Curve2);

		theCoords.SetValue(Index, Coord);

		QCurves.EnQueue(Curve1);

		Curve = Curve2;

		if (Parameter NOT_EQUAL Parameters.Last()) QRemoved.EnQueue(Curve2);
	}
	QCurves.EnQueue((Global_Handle(Cad3d_CurveOnPlane))Curve);
	QCurves.RetrieveTo(theCurves);

	TColCad3d_HAry1dOfCurveOnPlane Removed;
	QRemoved.RetrieveTo(Removed);

	FreeMemory(Removed);
}

void AutLib::CadLib::Cad3d_CurveOnPlane::SetFirst(const Standard_Real theValue)
{
	theFirst_ = theValue;
}

void AutLib::CadLib::Cad3d_CurveOnPlane::SetLast(const Standard_Real theValue)
{
	theLast_ = theValue;
}

void AutLib::CadLib::Cad3d_CurveOnPlane::SetCurve(const Handle(Geom2d_Curve)& theCurve)
{
	theCurve_ = theCurve;
}

void AutLib::CadLib::Cad3d_CurveOnPlane::SetReverse(const Standard_Boolean Reversed)
{
	IsReversed_ = Reversed;
}

void AutLib::CadLib::Cad3d_CurveOnPlane::Reverse()
{
	theCurve_->Reverse();
	Standard_Real Temp = theLast_;
	theLast_ = theCurve_->ReversedParameter(theFirst_);
	theFirst_ = theCurve_->ReversedParameter(Temp);
}

void AutLib::CadLib::Cad3d_CurveOnPlane::ReleaseMemory()
{
}

void AutLib::CadLib::Cad3d_CurveOnPlane::Mirror(const gp_Pnt2d & P)
{
	theCurve_->Mirror(P);
}

void AutLib::CadLib::Cad3d_CurveOnPlane::Mirror(const gp_Ax2d & A)
{
	theCurve_->Mirror(A);
}

void AutLib::CadLib::Cad3d_CurveOnPlane::Rotate(const gp_Pnt2d & P, const Standard_Real Ang)
{
	theCurve_->Rotate(P, Ang);
}

void AutLib::CadLib::Cad3d_CurveOnPlane::Scale(const gp_Pnt2d & P, const Standard_Real S)
{
	theCurve_->Scale(P, S);
}

void AutLib::CadLib::Cad3d_CurveOnPlane::Translate(const gp_Vec2d & V)
{
	theCurve_->Translate(V);
}

void AutLib::CadLib::Cad3d_CurveOnPlane::Translate(const gp_Pnt2d & P1, const gp_Pnt2d & P2)
{
	theCurve_->Translate(P1, P2);
}

void AutLib::CadLib::Cad3d_CurveOnPlane::Transform(const gp_Trsf2d & T)
{
	theCurve_->Transform(T);
}

void AutLib::CadLib::Cad3d_CurveOnPlane::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportCurve(*theCurve_, theFirst_, theLast_, 40, File);
}

Global_Handle(Cad3d_CurveOnPlane) AutLib::CadLib::Cad3d_CurveOnPlane::Copy() const
{
	return new Cad3d_CurveOnPlane(theFirst_, theLast_, theCurve_);
}