#include <Cad3d_RingCurveOnPlane.hxx>

using namespace AutLib;
using namespace CadLib;

AutLib::CadLib::Cad3d_RingCurveOnPlane::Cad3d_RingCurveOnPlane()
{
}

AutLib::CadLib::Cad3d_RingCurveOnPlane::Cad3d_RingCurveOnPlane
(
	const Standard_Real theFirstParameter,
	const Standard_Real theLastParameter, 
	const Handle(Geom2d_Curve)& theCurve
)
	: Cad3d_CurveOnPlane(theFirstParameter, theLastParameter, theCurve)
{
}

AutLib::CadLib::Cad3d_RingCurveOnPlane::~Cad3d_RingCurveOnPlane()
{
}

void AutLib::CadLib::Cad3d_RingCurveOnPlane::Init
(
	const Standard_Real theFirstParameter,
	const Standard_Real theLastParameter,
	const Handle(Geom2d_Curve)& theCurve
)
{
	Cad3d_CurveOnPlane::Init(theFirstParameter, theLastParameter, theCurve);
}

Global_Handle(Cad3d_RingCurveOnPlane) AutLib::CadLib::Cad3d_RingCurveOnPlane::Copy() const
{
	return new Cad3d_RingCurveOnPlane(theFirst_, theLast_, theCurve_);
}