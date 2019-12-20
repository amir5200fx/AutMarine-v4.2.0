#include <FvVariables_Sources2d.hxx>

AutLib::FvLib::FvVariables_Sources2d::FvVariables_Sources2d
(
	FvVector & theU_Component,
	FvVector & theV_Component
)
	: theBu_(theU_Component)
	, theBv_(theV_Component)
{
}