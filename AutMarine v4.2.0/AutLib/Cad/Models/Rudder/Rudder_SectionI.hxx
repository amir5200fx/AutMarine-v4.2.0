#pragma once
inline
Standard_Boolean AutLib::CadLib::Rudder_Section::IsDone() const
{
	return IsDone_;
}

inline
const Handle(Geom_Curve)& AutLib::CadLib::Rudder_Section::UpperCurve() const
{
	return theUpper_;
}

inline 
const Handle(Geom_Curve)& AutLib::CadLib::Rudder_Section::LowerCurve() const
{
	return theLower_;
}