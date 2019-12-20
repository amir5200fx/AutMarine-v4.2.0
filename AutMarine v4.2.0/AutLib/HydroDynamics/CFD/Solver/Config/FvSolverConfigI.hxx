#pragma once
inline
Scalar AutLib::FvLib::FvSolverConfig::Time() const
{
	return theTime_;
}

inline 
Label AutLib::FvLib::FvSolverConfig::MaxIterations() const
{
	return theMaxIters_;
}

inline 
Label AutLib::FvLib::FvSolverConfig::NbIterations() const
{
	return theIters_;
}

inline 
Scalar AutLib::FvLib::FvSolverConfig::MaxResidual() const
{
	return theMaxRes_;
}

inline 
Scalar AutLib::FvLib::FvSolverConfig::Residual() const
{
	return theRes_;
}