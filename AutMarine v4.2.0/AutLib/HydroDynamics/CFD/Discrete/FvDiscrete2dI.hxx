#pragma once
inline
const AutLib::FvLib::FvMatrix & AutLib::FvLib::FvDiscrete2d::Assembly() const
{
	return theAssembly_;
}

inline 
const AutLib::FvLib::FvMesh2d & AutLib::FvLib::FvDiscrete2d::Mesh() const
{
	return theMesh_;
}

//inline 
//const AutLib::FvLib::FvVectorField & AutLib::FvLib::FvDiscrete2d::VectorField() const
//{
//	return theVectorField_;
//}

inline 
AutLib::FvLib::FvMatrix & AutLib::FvLib::FvDiscrete2d::Assembly()
{
	return theAssembly_;
}

//inline 
//AutLib::FvLib::FvVectorField & AutLib::FvLib::FvDiscrete2d::VectorField()
//{
//	return theVectorField_;
//}