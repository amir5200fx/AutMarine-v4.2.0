#pragma once
inline
Global_Handle(M_CAD Cad3d_CurveOnPlane) AutLib::CadLib::Cad3d_EdgeOnPlane::Curve() const
{
	return theCurve_;
}

inline 
const Global_Handle(M_CAD Cad3d_PointOnPlane) AutLib::CadLib::Cad3d_EdgeOnPlane::FirstPoint() const
{
	return theFirstPoint_;
}

inline 
const Global_Handle(M_CAD Cad3d_PointOnPlane) AutLib::CadLib::Cad3d_EdgeOnPlane::LastPoint() const
{
	return theLastPoint_;
}

inline 
const Global_Handle(M_CAD Cad3d_WireOnPlane) AutLib::CadLib::Cad3d_EdgeOnPlane::Wire() const
{
	return theWire_;
}

inline 
Standard_Integer AutLib::CadLib::Cad3d_EdgeOnPlane::Index() const
{
	return theIndex_;
}