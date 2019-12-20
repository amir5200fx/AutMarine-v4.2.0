#pragma once
inline
Standard_Integer AutLib::FvLib::FvEntity_Element2d::Index() const
{
	return theIndex_;
}

inline 
Standard_Real AutLib::FvLib::FvEntity_Element2d::Volume() const
{
	return theVolume_;
}

inline 
M_FV FvBC_Physics AutLib::FvLib::FvEntity_Element2d::Physics() const
{
	return thePhysics_;
}

inline
const Geom_Pnt2d & AutLib::FvLib::FvEntity_Element2d::Centre() const
{
	return theCentre_;
}