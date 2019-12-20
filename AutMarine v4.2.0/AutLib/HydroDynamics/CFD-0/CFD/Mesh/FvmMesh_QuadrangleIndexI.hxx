#pragma once
inline
Standard_Integer AutLib::FvmLib::FvmMesh_QuadrangleIndex::V0() const
{
	return theValue_[0];
}

inline
Standard_Integer AutLib::FvmLib::FvmMesh_QuadrangleIndex::V1() const
{
	return theValue_[1];
}

inline
Standard_Integer AutLib::FvmLib::FvmMesh_QuadrangleIndex::V2() const
{
	return theValue_[2];
}

inline
Standard_Integer AutLib::FvmLib::FvmMesh_QuadrangleIndex::V3() const
{
	return theValue_[3];
}

inline 
Standard_Integer AutLib::FvmLib::FvmMesh_QuadrangleIndex::Value(const Standard_Integer theIndex) const
{
	Debug_If_Condition_Message(NOT INSIDE(theIndex, 0, 3), "Invalid Index");
	return theValue_[theIndex];
}