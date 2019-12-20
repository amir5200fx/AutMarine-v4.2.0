#pragma once
inline
Global_Handle(AutLib::CadLib::Cad2d_CurveOnPlane) AutLib::CadLib::Cad2d_EdgeOnPlane::Curve() const
{
	return theCurve_;
}

inline 
const Global_Handle(AutLib::CadLib::Cad2d_PointOnPlane) AutLib::CadLib::Cad2d_EdgeOnPlane::FirstPoint() const
{
	return theFirstPoint_;
}

inline 
const Global_Handle(AutLib::CadLib::Cad2d_PointOnPlane) AutLib::CadLib::Cad2d_EdgeOnPlane::LastPoint() const
{
	return theLastPoint_;
}

inline 
const Global_Handle(AutLib::CadLib::Cad2d_WireOnPlane) AutLib::CadLib::Cad2d_EdgeOnPlane::Wire() const
{
	return theWire_;
}

inline 
Standard_Integer AutLib::CadLib::Cad2d_EdgeOnPlane::Index() const
{
	return theIndex_;
}