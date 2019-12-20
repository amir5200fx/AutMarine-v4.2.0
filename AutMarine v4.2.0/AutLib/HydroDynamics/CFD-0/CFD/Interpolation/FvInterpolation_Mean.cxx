#include <FvInterpolation_Mean.hxx>

AutLib::FvLib::FvInterpolation_Mean::FvInterpolation_Mean
(
	const FvVariables_Faces2d & thePhif,
	const FvVariables_Elements2d & thePhi
)
	: FvInterpolation(thePhif, thePhi)
{
}