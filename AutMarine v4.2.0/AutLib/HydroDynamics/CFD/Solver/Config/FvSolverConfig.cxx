#include <FvSolverConfig.hxx>

AutLib::FvLib::FvSolverConfig::FvSolverConfig(const Label theMaxIters, const Scalar theMaxRes)
	: theMaxIters_(theMaxIters)
	, theMaxRes_(theMaxRes)
{
}

AutLib::FvLib::FvSolverConfig::~FvSolverConfig()
{
}

void AutLib::FvLib::FvSolverConfig::SetTime(const Scalar theTime)
{
	theTime_ = theTime;
}

void AutLib::FvLib::FvSolverConfig::SetMaxIterations(const Label theMaxIters)
{
	theMaxIters_ = theMaxIters;
}

void AutLib::FvLib::FvSolverConfig::SetNbIterations(const Label theNbIterations)
{
	theIters_ = theNbIterations;
}

void AutLib::FvLib::FvSolverConfig::SetMaxResidual(const Scalar theValue)
{
	theMaxRes_ = theValue;
}

void AutLib::FvLib::FvSolverConfig::SetResidual(const Scalar theValue)
{
	theRes_ = theValue;
}