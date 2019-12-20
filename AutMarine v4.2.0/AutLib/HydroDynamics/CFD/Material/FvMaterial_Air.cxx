#include <FvMaterial_Air.hxx>

#include <FvMaterial_Info.hxx>

AutLib::FvLib::FvMaterial_Air::FvMaterial_Air()
	: FvMaterial(FvMaterial_Info::Density_Air(), FvMaterial_Info::Viscosity_Air())
{
}