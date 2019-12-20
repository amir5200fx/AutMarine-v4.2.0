#include <FvInterpolation_Mean2d.hxx>

AutLib::FvLib::FvInterpolation_Mean2d::FvInterpolation_Mean2d
(
	const FvVector & thePhif, 
	const FvVector & thePhi
)
	: FvInterpolation2d(thePhif, thePhi)
{
}