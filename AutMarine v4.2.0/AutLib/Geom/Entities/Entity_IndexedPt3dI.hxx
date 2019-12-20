#pragma once
inline
Standard_Integer AutLib::GeoLib::Entity_IndexedPt3d::Index() const
{
	return theIndex_;
}

inline 
const Geom_Pnt3d & AutLib::GeoLib::Entity_IndexedPt3d::Coord() const
{
	return theCoord_;
}

inline 
void AutLib::GeoLib::Entity_IndexedPt3d::SetIndex(const Standard_Integer theIndex)
{
	theIndex_ = theIndex;
}

inline 
void AutLib::GeoLib::Entity_IndexedPt3d::SetCoord(const Geom_Pnt3d & theCoord)
{
	theCoord_ = theCoord;
}