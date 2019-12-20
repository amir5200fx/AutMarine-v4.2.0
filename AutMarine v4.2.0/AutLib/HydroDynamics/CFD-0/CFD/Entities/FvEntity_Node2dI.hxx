#pragma once
inline
void AutLib::FvLib::FvEntity_Node2d::RetrieveElementsTo(TColFvEntity_HAry1dOfElement2d & theElements) const
{
	theElements_.RetrieveTo(theElements);
}

inline 
Standard_Integer AutLib::FvLib::FvEntity_Node2d::Index() const
{
	return theIndex_;
}

inline 
const Geom_Pnt2d & AutLib::FvLib::FvEntity_Node2d::Coord() const
{
	return theCoord_;
}