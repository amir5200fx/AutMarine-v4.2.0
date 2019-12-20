#pragma once
inline
const Handle(Geom2d_Curve)& AutLib::CadLib::Cad2d_CurveOnPlane::Curve() const
{
	return theCurve_;
}

inline 
Standard_Boolean AutLib::CadLib::Cad2d_CurveOnPlane::IsClosed(const Standard_Real theTolerance) const
{
	return Distance(Cad2d_CurveOnPlane::FirstCoord(), Cad2d_CurveOnPlane::LastCoord()) <= theTolerance;
}

inline 
Standard_Real AutLib::CadLib::Cad2d_CurveOnPlane::FirstParameter() const
{
	return theFirst_;
}

inline 
Standard_Real AutLib::CadLib::Cad2d_CurveOnPlane::LastParameter() const
{
	return theLast_;
}