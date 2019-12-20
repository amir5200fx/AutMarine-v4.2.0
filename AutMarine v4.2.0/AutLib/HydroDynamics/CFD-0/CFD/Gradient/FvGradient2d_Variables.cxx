#include <FvGradient2d_Variables.hxx>

AutLib::FvLib::FvGradient2d_Variables::FvGradient2d_Variables
(
	const FvGradient2d_Pressure & thePressure,
	const FvGradient2d_xVelocity & thexVelocity,
	const FvGradient2d_yVelocity & theyVelocity
)
	: thePressure_(thePressure)
	, thexVelocity_(thexVelocity)
	, theyVelocity_(theyVelocity)
{
}