#include <FvInterpolation_Geometric2d.hxx>

AutLib::FvLib::FvInterpolation_Geometric2d::FvInterpolation_Geometric2d
(
	const FvVector & thePhif, 
	const FvVector & thePhi
)
	: FvInterpolation2d(thePhif, thePhi)
{
}