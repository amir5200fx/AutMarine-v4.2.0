#include <FvParameters.hxx>

#include <FvParameters_SolverConfigInfo.hxx>

AutLib::FvLib::FvParameters::FvParameters(const FvParameters_TimeConfig& theTime)
	: theTime_(theTime)
{
	theVelocity_.SetSolver(FvParameters_SolverConfigInfo::VelocitySolver());
	theVelocity_.SetPrecondition(FvParameters_SolverConfigInfo::VelocityPrecondition());
	theVelocity_.SetMaxIterations(FvParameters_SolverConfigInfo::VelocityMaxNbIterations());
	theVelocity_.SetMaxResidual(FvParameters_SolverConfigInfo::VelocityMaxResidual());

	thePressure_.SetSolver(FvParameters_SolverConfigInfo::PressureSolver());
	thePressure_.SetPrecondition(FvParameters_SolverConfigInfo::PressurePrecondition());
	thePressure_.SetMaxIterations(FvParameters_SolverConfigInfo::PressureMaxNbIterations());
	thePressure_.SetMaxResidual(FvParameters_SolverConfigInfo::PressureMaxResidual());
}