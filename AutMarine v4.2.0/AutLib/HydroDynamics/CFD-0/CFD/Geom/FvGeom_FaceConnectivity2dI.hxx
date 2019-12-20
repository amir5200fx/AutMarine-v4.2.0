#pragma once
inline
Standard_Integer AutLib::FvLib::FvGeom_FaceConnectivity2d::Value(const Standard_Integer theIndex) const
{
	return (&theV0_)[theIndex];
}