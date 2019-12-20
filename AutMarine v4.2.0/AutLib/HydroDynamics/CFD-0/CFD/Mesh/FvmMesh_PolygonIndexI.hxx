#pragma once
inline
Standard_Integer AutLib::FvmLib::FvmMesh_PolygonIndex::Size() const
{
	return theValue_.Size();
}

inline 
Standard_Integer AutLib::FvmLib::FvmMesh_PolygonIndex::Value(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theValue_);
	return theValue_.Value(theIndex);
}

inline 
const M_AUT TColStd_Ary1dOfInteger & AutLib::FvmLib::FvmMesh_PolygonIndex::Value() const
{
	return theValue_;
}