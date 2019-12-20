#pragma once
inline
const AutLib::FvLib::FvMatrix & AutLib::FvLib::FvSolver::Matrix() const
{
	return theMatrix_;
}

inline 
const AutLib::FvLib::FvSolverConfig & AutLib::FvLib::FvSolver::Parameters() const
{
	return theParameters_;
}