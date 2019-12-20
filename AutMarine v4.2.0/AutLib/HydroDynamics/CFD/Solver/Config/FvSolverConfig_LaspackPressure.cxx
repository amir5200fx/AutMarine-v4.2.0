#include <FvSolverConfig_LaspackPressure.hxx>

#include <FvSolverConfig_LaspackSolverSetupInfo.hxx>

AutLib::FvLib::FvSolverConfig_LaspackPressure::FvSolverConfig_LaspackPressure()
	: FvSolverConfig_Laspack
	(
		FvSolverConfig_LaspackSolverSetupInfo::PressureMaxNbIterations(),
		FvSolverConfig_LaspackSolverSetupInfo::PressureMaxResidual(),
		FvSolverConfig_LaspackSolverSetupInfo::PressurePrecondition(), 
		FvSolverConfig_LaspackSolverSetupInfo::PressureSolver()
	)
{
}

AutLib::FvLib::FvSolverConfig_LaspackPressure::~FvSolverConfig_LaspackPressure()
{
}