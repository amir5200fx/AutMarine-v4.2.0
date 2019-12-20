#include <FvInterpolation.hxx>

AutLib::FvLib::FvInterpolation::FvInterpolation
(
	const FvVariables_Faces2d & thePhif,
	const FvVariables_Elements2d & thePhi
)
	: thePhif_(thePhif)
	, thePhi_(thePhi)
{
}