#include <FvSolverConfig_Laspack.hxx>

#include <FvSolverConfig_LaspackSolverSetupInfo.hxx>

AutLib::FvLib::FvSolverConfig_Laspack::FvSolverConfig_Laspack
(
	const Label theMaxIters, 
	const Scalar theMaxRes,
	const FvSolverConfig_LaspackPrecondition thePrecondition, 
	const FvSolverConfig_LaspackSolverInfo theSolver
)
	: FvSolverConfig(theMaxIters, theMaxRes)
	, thePrecondition_(thePrecondition)
	, theSolver_(theSolver)
	, theOmega_(FvSolverConfig_LaspackSolverSetupInfo::Omeag())
{
}

AutLib::FvLib::FvSolverConfig_Laspack::~FvSolverConfig_Laspack()
{
}

void AutLib::FvLib::FvSolverConfig_Laspack::SetPrecondition(const FvSolverConfig_LaspackPrecondition thePrecondition)
{
	thePrecondition_ = thePrecondition;
}

void AutLib::FvLib::FvSolverConfig_Laspack::SetSolver(const FvSolverConfig_LaspackSolverInfo theSolver)
{
	theSolver_ = theSolver;
}

void AutLib::FvLib::FvSolverConfig_Laspack::SetOmega(const Scalar theOmega)
{
	theOmega_ = theOmega;
}