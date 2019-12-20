#pragma once
inline
const Geom_Pnt3d & AutLib::CadLib::Cad3d_Datum::Coord() const
{
	return theCoord_;
}

inline 
const Standard_String & AutLib::CadLib::Cad3d_Datum::Name() const
{
	return theName_;
}