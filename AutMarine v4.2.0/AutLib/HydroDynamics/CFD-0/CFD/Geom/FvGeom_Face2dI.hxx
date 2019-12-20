#pragma once
inline
Standard_Integer AutLib::FvLib::FvGeom_Face2d::Index() const
{
	return theIndex_;
}

inline 
AutLib::FvLib::FvBC_Physics AutLib::FvLib::FvGeom_Face2d::Physics() const
{
	return thePhysics_;
}

inline
const AutLib::FvLib::FvGeom_FaceConnectivity2d & AutLib::FvLib::FvGeom_Face2d::Connectivity() const
{
	return theConnectivity_;
}