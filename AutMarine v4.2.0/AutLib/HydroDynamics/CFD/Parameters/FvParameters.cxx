#include <FvParameters.hxx>

AutLib::FvLib::FvParameters::FvParameters
(
	const FvParameters_TimeConfig & theTime, 
	const FvSolverConfig & theVelocitySolver,
	const FvSolverConfig & thePressureSolver
)
	: theTime_(theTime)
	, theVelocity_(theVelocitySolver)
	, thePressure_(thePressureSolver)
{
}