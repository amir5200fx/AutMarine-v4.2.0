#pragma once
inline
AutLib::FvLib::FvSolverConfig_LaspackPrecondition AutLib::FvLib::FvSolverConfig_Laspack::Precondition() const
{
	return thePrecondition_;
}

inline 
AutLib::FvLib::FvSolverConfig_LaspackSolverInfo AutLib::FvLib::FvSolverConfig_Laspack::Solver() const
{
	return theSolver_;
}

inline 
Scalar AutLib::FvLib::FvSolverConfig_Laspack::Omega() const
{
	return theOmega_;
}