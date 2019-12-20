#include <FvSolverConfig_LaspackVelocity.hxx>

#include <FvSolverConfig_LaspackSolverSetupInfo.hxx>

AutLib::FvLib::FvSolverConfig_LaspackVelocity::FvSolverConfig_LaspackVelocity()
	: FvSolverConfig_Laspack
	(
		FvSolverConfig_LaspackSolverSetupInfo::VelocityMaxNbIterations(),
		FvSolverConfig_LaspackSolverSetupInfo::VelocityMaxResidual(),
		FvSolverConfig_LaspackSolverSetupInfo::VelocityPrecondition(),
		FvSolverConfig_LaspackSolverSetupInfo::VelocitySolver()
	)
{
}

AutLib::FvLib::FvSolverConfig_LaspackVelocity::~FvSolverConfig_LaspackVelocity()
{
}