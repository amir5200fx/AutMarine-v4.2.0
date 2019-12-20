#pragma once
inline
void AutLib::FvLib::FvEntity_Node2d::RetrieveElementsTo(FvList_Element2d & theElements) const
{
	theElements_.RetrieveTo(theElements);
}

inline 
Label AutLib::FvLib::FvEntity_Node2d::Index() const
{
	return theIndex_;
}

inline 
const Geom_Pnt2d & AutLib::FvLib::FvEntity_Node2d::Coord() const
{
	return theCoord_;
}