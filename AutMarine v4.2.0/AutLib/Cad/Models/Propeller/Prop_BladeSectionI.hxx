#pragma once
inline
const Handle(Geom2d_Curve)& AutLib::CadLib::Prop_BladeSection::Face() const
{
	return theFace_;
}

inline 
const Handle(Geom2d_Curve)& AutLib::CadLib::Prop_BladeSection::Back() const
{
	return theBack_;
}