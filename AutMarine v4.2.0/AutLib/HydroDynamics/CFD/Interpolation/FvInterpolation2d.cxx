#include <FvInterpolation2d.hxx>

AutLib::FvLib::FvInterpolation2d::FvInterpolation2d
(
	const FvVector & thePhif,
	const FvVector & thePhi
)
	: thePhif_(thePhif)
	, thePhi_(thePhi)
{
}