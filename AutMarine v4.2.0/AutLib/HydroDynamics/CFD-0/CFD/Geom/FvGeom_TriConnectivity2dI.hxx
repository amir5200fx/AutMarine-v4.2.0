#pragma once
inline
Standard_Integer AutLib::FvLib::FvGeom_TriConnectivity2d::Size() const
{
	return (Standard_Integer)3;
}

inline 
Standard_Integer AutLib::FvLib::FvGeom_TriConnectivity2d::Value(const Standard_Integer theIndex) const
{
	return (&theV0_)[theIndex];
}