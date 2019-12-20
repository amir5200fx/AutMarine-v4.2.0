#pragma once
inline
Label AutLib::FvLib::FvGeom_Node2d::Index() const
{
	return theIndex_;
}

inline 
const Geom_Pnt2d & AutLib::FvLib::FvGeom_Node2d::Coord() const
{
	return theCoord_;
}