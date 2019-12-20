#include <Cad3d_CurveOnSurface.hxx>

#include <Entity_Box3d.hxx>
#include <Geom_Curve.hxx>
#include <Bnd_Box.hxx>
#include <BndLib_Add3dCurve.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <Global_Debug.hxx>
#include <IO_Tecplot.hxx>
#include <Global_DefineException.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace CadLib;

AutLib::CadLib::Cad3d_CurveOnSurface::Cad3d_CurveOnSurface()
{
}

AutLib::CadLib::Cad3d_CurveOnSurface::Cad3d_CurveOnSurface
(
	const Standard_Real First,
	const Standard_Real Last, 
	const Handle(Geom_Curve)& Curve
)
	: theFirst_(First)
	, theLast_(Last)
	, theCurve_(Curve)
{
}

AutLib::CadLib::Cad3d_CurveOnSurface::~Cad3d_CurveOnSurface()
{
}

void AutLib::CadLib::Cad3d_CurveOnSurface::Init
(
	const Standard_Real First, 
	const Standard_Real Last,
	const Handle(Geom_Curve)& Curve
)
{
	theFirst_ = First;
	theLast_ = Last;

	theCurve_ = Curve;
}

Geom_Pnt3d AutLib::CadLib::Cad3d_CurveOnSurface::StartCoord() const
{
	Debug_Null_Pointer(theCurve_);

	return theCurve_->Value(theFirst_);
}

Geom_Pnt3d AutLib::CadLib::Cad3d_CurveOnSurface::LastCoord() const
{
	Debug_Null_Pointer(theCurve_);

	return theCurve_->Value(theLast_);
}

Geom_Pnt3d AutLib::CadLib::Cad3d_CurveOnSurface::MidCoord() const
{
	Debug_Null_Pointer(theCurve_);

	return theCurve_->Value(MEAN(theFirst_, theLast_));
}

Geom_Pnt3d AutLib::CadLib::Cad3d_CurveOnSurface::Value(const Standard_Real Parameter) const
{
	Debug_Null_Pointer(theCurve_);

	return theCurve_->Value(Parameter);
}

Standard_Boolean AutLib::CadLib::Cad3d_CurveOnSurface::IsClosed(const Standard_Real Tolerance) const
{
	return Distance(StartCoord(), LastCoord()) <= Tolerance;
}

Standard_Boolean AutLib::CadLib::Cad3d_CurveOnSurface::Split
(
	const Standard_Real theParameter,
	Global_Handle(Cad3d_CurveOnSurface) theLeft, 
	Global_Handle(Cad3d_CurveOnSurface) theRight,
	const Standard_Real theTolerance
) const
{
	Debug_Null_Pointer(theLeft);
	Debug_Null_Pointer(theRight);

	if (ABS(theParameter - theFirst_) < theTolerance OR ABS(theParameter - theLast_) < theTolerance)
	{
		return Standard_False;
	}

	if (theParameter <= theFirst_ OR theParameter >= theLast_) { THROW_STANDARD_EXCEPTION("Invalid Parameter to Splitt Edge"); }

	theLeft->Init(theFirst_, theParameter, theCurve_);
	theRight->Init(theParameter, theLast_, theCurve_);

	return Standard_True;
}

Standard_Boolean AutLib::CadLib::Cad3d_CurveOnSurface::IsSameDirection(const Cad3d_CurveOnSurface & theOther) const
{
	Geom_Pnt3d P0 = StartCoord();
	Geom_Pnt3d P1 = LastCoord();

	Geom_Pnt3d Q0 = theOther.StartCoord();
	Geom_Pnt3d Q1 = theOther.LastCoord();
	/*cout << P0 << endl;
	cout << P1 << endl;
	cout << Q0 << endl;
	cout << Q1 << endl;
	PAUSE;*/
	return DotProduct(P1 - P0, Q1 - Q0) > 0;
}

Entity_Box3d AutLib::CadLib::Cad3d_CurveOnSurface::BoundingBox(const Standard_Real Offset) const
{
	Bnd_Box BndBox;
	BndLib_Add3dCurve::Add(GeomAdaptor_Curve(theCurve_), theFirst_, theLast_, Offset, BndBox);

	Standard_Real Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
	BndBox.Get(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);

	return Entity_Box3d(Xmin, Xmax, Ymin, Ymax, Zmin, Zmax);
}

Global_Handle(Cad3d_CurveOnSurface) AutLib::CadLib::Cad3d_CurveOnSurface::Copy() const
{
	return new Cad3d_CurveOnSurface(theFirst_, theLast_, theCurve_);
}

void AutLib::CadLib::Cad3d_CurveOnSurface::SetFirst(const Standard_Real Value)
{
	theFirst_ = Value;
}

void AutLib::CadLib::Cad3d_CurveOnSurface::SetLast(const Standard_Real Value)
{
	theLast_ = Value;
}

void AutLib::CadLib::Cad3d_CurveOnSurface::SetCurve(const Handle(Geom_Curve)& Curve)
{
	theCurve_ = Curve;
}

void AutLib::CadLib::Cad3d_CurveOnSurface::Reverse()
{
	theCurve_->Reverse();
	Standard_Real Temp = theLast_;
	theLast_ = theCurve_->ReversedParameter(theFirst_);
	theFirst_ = theCurve_->ReversedParameter(Temp);
}

void AutLib::CadLib::Cad3d_CurveOnSurface::ExportToPlt(fstream & File) const
{
	Debug_Null_Pointer(theCurve_);

	M_IO IO_TecPlot::ExportCurve(*theCurve_, theFirst_, theLast_, 40, File);
}

void AutLib::CadLib::Cad3d_CurveOnSurface::ExportTopologyToPlt(fstream & File) const
{
	Debug_Null_Pointer(theCurve_);

	M_IO IO_TecPlot::ExportCurve(*theCurve_, theFirst_, theLast_, 1, File);
}