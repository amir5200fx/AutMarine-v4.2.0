#pragma once
inline
Standard_Integer AutLib::FvLib::FvGeom_Element2d::Index() const
{
	return theIndex_;
}

inline 
AutLib::FvLib::FvBC_Physics AutLib::FvLib::FvGeom_Element2d::Physics() const
{
	return thePhysics_;
}

inline 
AutLib::FvLib::FvGeom_ElementType AutLib::FvLib::FvGeom_Element2d::Type() const
{
	return theType_;
}

inline
const Global_Handle(AutLib::FvLib::FvGeom_ElementConnectivity2d) AutLib::FvLib::FvGeom_Element2d::Connectivity() const
{
	return theConnectivity_;
}