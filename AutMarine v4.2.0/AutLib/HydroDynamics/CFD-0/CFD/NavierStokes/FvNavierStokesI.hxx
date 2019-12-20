#pragma once
inline
const AutLib::FvLib::FvMesh2d & AutLib::FvLib::FvNavierStokes::Mesh() const
{
	return theMesh_;
}

inline 
const AutLib::FvLib::FvParameters & AutLib::FvLib::FvNavierStokes::Parameters() const
{
	return theParameters_;
}

inline 
const AutLib::FvLib::FvBC & AutLib::FvLib::FvNavierStokes::BoundaryCondition() const
{
	return theBoundaryCondition_;
}

inline 
const AutLib::FvLib::FvVariables2d & AutLib::FvLib::FvNavierStokes::Variables() const
{
	return theVariables_;
}