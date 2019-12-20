#include <Cad3d_RingOnSurface.hxx>

#include <Geom_Curve.hxx>

AutLib::CadLib::Cad3d_RingOnSurface::Cad3d_RingOnSurface()
{
}

AutLib::CadLib::Cad3d_RingOnSurface::Cad3d_RingOnSurface
(
	const Standard_Real First,
	const Standard_Real Last,
	const Handle(Geom_Curve)& Curve
)
	: Cad3d_CurveOnSurface(First,Last,Curve)
{
	theCentre_ = Curve->Value(MEAN(First, Last));
}

AutLib::CadLib::Cad3d_RingOnSurface::~Cad3d_RingOnSurface()
{
}

Standard_Boolean AutLib::CadLib::Cad3d_RingOnSurface::IsSameDirection(const Cad3d_RingOnSurface & theOther) const
{
	Geom_Pnt3d P0 = StartCoord();
	Geom_Pnt3d P1 = theCentre_;

	Geom_Pnt3d Q0 = theOther.StartCoord();
	Geom_Pnt3d Q1 = theOther.theCentre_;

	return DotProduct(P1 - P0, Q1 - Q0) > 0;
}

void AutLib::CadLib::Cad3d_RingOnSurface::SetCentre(const Geom_Pnt3d & Centre)
{
	theCentre_ = Centre;
}