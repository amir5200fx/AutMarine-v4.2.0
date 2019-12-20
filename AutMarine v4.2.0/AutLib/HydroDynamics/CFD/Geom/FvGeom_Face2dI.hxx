#pragma once
inline
Label AutLib::FvLib::FvGeom_Face2d::Index() const
{
	return theIndex_;
}

inline 
AutLib::FvLib::FvBC_Physics AutLib::FvLib::FvGeom_Face2d::Physics() const
{
	return thephysics_;
}

inline 
const AutLib::FvLib::FvConnectivities_Dual & AutLib::FvLib::FvGeom_Face2d::Connectivity() const
{
	return theConnectivity_;
}