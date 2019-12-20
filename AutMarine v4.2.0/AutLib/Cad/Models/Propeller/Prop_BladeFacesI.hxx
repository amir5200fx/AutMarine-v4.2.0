#pragma once
inline
const Handle(Geom_Surface)& AutLib::CadLib::Prop_BladeFaces::Face() const
{
	return theFace_;
}

inline 
const Handle(Geom_Surface)& AutLib::CadLib::Prop_BladeFaces::Back() const
{
	return theBack_;
}