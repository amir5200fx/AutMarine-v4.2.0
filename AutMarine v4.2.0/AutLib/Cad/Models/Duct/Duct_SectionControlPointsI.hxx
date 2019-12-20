#pragma once
inline
Standard_Integer AutLib::CadLib::Duct_SectionControlPoints::NbPoints() const
{
	return theControlPoints_.Size();
}

inline 
const M_AUT TColGeom_Ary1dOfPnt3d & AutLib::CadLib::Duct_SectionControlPoints::ControlPoints() const
{
	return theControlPoints_;
}

inline 
const Geom_Pnt3d & AutLib::CadLib::Duct_SectionControlPoints::Coord(const Standard_Integer theIndex) const
{
	return theControlPoints_.Value(theIndex);
}

inline 
M_AUT TColGeom_Ary1dOfPnt3d & AutLib::CadLib::Duct_SectionControlPoints::ControlPoints()
{
	return theControlPoints_;
}