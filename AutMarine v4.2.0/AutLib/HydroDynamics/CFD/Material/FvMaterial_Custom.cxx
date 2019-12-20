#include <FvMaterial_Custom.hxx>

AutLib::FvLib::FvMaterial_Custom::FvMaterial_Custom
(
	const FvMaterial_Density & theDensity,
	const FvMaterial_Viscosity & theViscosity
)
	: FvMaterial(theDensity, theViscosity)
{
}