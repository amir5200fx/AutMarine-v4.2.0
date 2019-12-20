#include <FvMaterial_Water.hxx>

#include <FvMaterial_Info.hxx>

AutLib::FvLib::FvMaterial_Water::FvMaterial_Water()
	: FvMaterial(FvMaterial_Info::Density_Water(), FvMaterial_Info::Viscosity_Water())
{
}