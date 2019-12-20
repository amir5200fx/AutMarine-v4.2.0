#pragma once
inline
Label AutLib::FvLib::FvEntity_Element2d::Index() const
{
	return theIndex_;
}

inline 
Scalar AutLib::FvLib::FvEntity_Element2d::Volume() const
{
	return theVolume_;
}

inline
AutLib::FvLib::FvBC_Physics AutLib::FvLib::FvEntity_Element2d::Physics() const
{
	return thePhysics_;
}

inline 
const Geom_Pnt2d & AutLib::FvLib::FvEntity_Element2d::Centre() const
{
	return theCentre_;
}