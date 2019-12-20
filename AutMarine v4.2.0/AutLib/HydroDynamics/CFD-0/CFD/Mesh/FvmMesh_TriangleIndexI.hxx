#pragma once
inline
Standard_Integer AutLib::FvmLib::FvmMesh_TriangleIndex::V0() const
{
	return theValue_[0];
}

inline 
Standard_Integer AutLib::FvmLib::FvmMesh_TriangleIndex::V1() const
{
	return theValue_[1];
}

inline 
Standard_Integer AutLib::FvmLib::FvmMesh_TriangleIndex::V2() const
{
	return theValue_[2];
}

inline 
Standard_Integer AutLib::FvmLib::FvmMesh_TriangleIndex::Value(const Standard_Integer theIndex) const
{
	Debug_If_Condition_Message(NOT INSIDE(theIndex, 0, 2), "Invalid Index");
	return theValue_[theIndex];
}