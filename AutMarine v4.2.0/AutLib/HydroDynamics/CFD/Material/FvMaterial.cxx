#include <FvMaterial.hxx>

AutLib::FvLib::FvMaterial::FvMaterial()
{
}

AutLib::FvLib::FvMaterial::FvMaterial
(
	const FvMaterial_Density & theDensity,
	const FvMaterial_Viscosity & theViscosity
)
	: theDensity_(theDensity)
	, theViscosity_(theViscosity)
{
}

AutLib::FvLib::FvMaterial::~FvMaterial()
{
}