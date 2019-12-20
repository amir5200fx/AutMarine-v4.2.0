#pragma once
inline
Standard_Integer AutLib::FvLib::FvGeom_GeneralConnectivity2d::Size() const
{
	return theValues_.Size();
}

inline 
Standard_Integer AutLib::FvLib::FvGeom_GeneralConnectivity2d::Value(const Standard_Integer theIndex) const
{
	return theValues_[theIndex];
}