#include <FvParameters_SolverConfig.hxx>

AutLib::FvLib::FvParameters_SolverConfig::FvParameters_SolverConfig()
{
}

void AutLib::FvLib::FvParameters_SolverConfig::SetSolver(const FvParameters_Solver theSolver)
{
	theSolver_ = theSolver;
}

void AutLib::FvLib::FvParameters_SolverConfig::SetPrecondition(const FvParameters_Precondition thePrecondition)
{
	thePrecondition_ = thePrecondition;
}

void AutLib::FvLib::FvParameters_SolverConfig::SetTime(const Standard_Real theTime)
{
	theTime_ = theTime;
}

void AutLib::FvLib::FvParameters_SolverConfig::SetMaxIterations(const Standard_Integer theMaxIters)
{
	theMaxIters_ = theMaxIters;
}

void AutLib::FvLib::FvParameters_SolverConfig::SetNbIterations(const Standard_Integer theNbIterations)
{
	theIters_ = theNbIterations;
}

void AutLib::FvLib::FvParameters_SolverConfig::SetMaxResidual(const Standard_Real theValue)
{
	theMaxRes_ = theValue;
}

void AutLib::FvLib::FvParameters_SolverConfig::SetResidual(const Standard_Real theValue)
{
	theRes_ = theValue;
}