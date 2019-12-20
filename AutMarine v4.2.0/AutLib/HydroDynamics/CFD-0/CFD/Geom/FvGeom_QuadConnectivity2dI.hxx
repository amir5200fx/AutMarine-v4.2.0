#pragma once
inline
Standard_Integer AutLib::FvLib::FvGeom_QuadConnectivity2d::Size() const
{
	return (Standard_Integer)4;
}

inline 
Standard_Integer AutLib::FvLib::FvGeom_QuadConnectivity2d::Value(const Standard_Integer theIndex) const
{
	return (&theV0_)[theIndex];
}