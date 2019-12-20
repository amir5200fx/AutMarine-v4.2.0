#pragma once
inline
AutLib::FvLib::FvParameters_Solver AutLib::FvLib::FvParameters_SolverConfig::Solver() const
{
	return theSolver_;
}

inline 
AutLib::FvLib::FvParameters_Precondition AutLib::FvLib::FvParameters_SolverConfig::Precondition() const
{
	return thePrecondition_;
}

inline 
Standard_Real AutLib::FvLib::FvParameters_SolverConfig::Time() const
{
	return theTime_;
}

inline
Standard_Integer AutLib::FvLib::FvParameters_SolverConfig::MaxIterations() const
{
	return theMaxIters_;
}

inline 
Standard_Integer AutLib::FvLib::FvParameters_SolverConfig::NbIterations() const
{
	return theIters_;
}

inline 
Standard_Real AutLib::FvLib::FvParameters_SolverConfig::MaxResidual() const
{
	return theMaxRes_;
}

inline 
Standard_Real AutLib::FvLib::FvParameters_SolverConfig::Residual() const
{
	return theRes_;
}