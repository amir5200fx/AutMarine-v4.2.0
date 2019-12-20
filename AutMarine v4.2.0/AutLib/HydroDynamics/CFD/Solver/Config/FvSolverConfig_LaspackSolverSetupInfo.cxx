#include <FvSolverConfig_LaspackSolverSetupInfo.hxx>

using namespace AutLib;
using namespace FvLib;

Label AutLib::FvLib::FvSolverConfig_LaspackSolverSetupInfo::VelocityMaxNbIterations()
{
	return (Label)1500;
}

Label AutLib::FvLib::FvSolverConfig_LaspackSolverSetupInfo::PressureMaxNbIterations()
{
	return (Label)1500;
}

Scalar AutLib::FvLib::FvSolverConfig_LaspackSolverSetupInfo::VelocityMaxResidual()
{
	return (Scalar)1.0E-8;
}

Scalar AutLib::FvLib::FvSolverConfig_LaspackSolverSetupInfo::PressureMaxResidual()
{
	return (Scalar)1.0E-8;
}

Scalar AutLib::FvLib::FvSolverConfig_LaspackSolverSetupInfo::Omeag()
{
	return (Scalar)1.0;
}

FvSolverConfig_LaspackPrecondition AutLib::FvLib::FvSolverConfig_LaspackSolverSetupInfo::VelocityPrecondition()
{
	return FvSolverConfig_LaspackPrecondition::FvSolverConfig_LaspackPrecondition_SOR;
}

FvSolverConfig_LaspackPrecondition AutLib::FvLib::FvSolverConfig_LaspackSolverSetupInfo::PressurePrecondition()
{
	return FvSolverConfig_LaspackPrecondition::FvSolverConfig_LaspackPrecondition_SOR;
}

FvSolverConfig_LaspackSolverInfo AutLib::FvLib::FvSolverConfig_LaspackSolverSetupInfo::VelocitySolver()
{
	return FvSolverConfig_LaspackSolverInfo::FvSolverConfig_LaspackSolverInfo_BICGS;
}

FvSolverConfig_LaspackSolverInfo AutLib::FvLib::FvSolverConfig_LaspackSolverSetupInfo::PressureSolver()
{
	return FvSolverConfig_LaspackSolverInfo::FvSolverConfig_LaspackSolverInfo_CGS;
}