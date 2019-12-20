#pragma once
inline
const Handle(Geom_Curve)& AutLib::CadLib::Cad3d_CurveOnSurface::Curve() const
{
	return theCurve_;
}

inline 
Standard_Real AutLib::CadLib::Cad3d_CurveOnSurface::FirstParameter() const
{
	return theFirst_;
}

inline 
Standard_Real AutLib::CadLib::Cad3d_CurveOnSurface::LastParameter() const
{
	return theLast_;
}
