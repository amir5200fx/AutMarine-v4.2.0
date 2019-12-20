#include <FvVariables_Primitives2d.hxx>

AutLib::FvLib::FvVariables_Primitives2d::FvVariables_Primitives2d
(
	FvVector & theU_Component,
	FvVector & theV_Component,
	FvVector & thePressure
)
	: theU_(theU_Component)
	, theV_(theV_Component)
	, theP_(thePressure)
{
}