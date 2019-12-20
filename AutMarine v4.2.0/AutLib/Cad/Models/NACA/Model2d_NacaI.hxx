#pragma once
inline
Handle(Geom2d_Curve) AutLib::CadLib::Model2d_Naca::UpperCurve() const
{
	return theUpper_;
}

inline 
Handle(Geom2d_Curve) AutLib::CadLib::Model2d_Naca::LowerCurve() const
{
	return theLower_;
}