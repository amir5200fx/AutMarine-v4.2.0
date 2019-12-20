#include <FvMaterial_Info.hxx>

#include <FvMaterial_Density.hxx>
#include <FvMaterial_Viscosity.hxx>

using namespace AutLib;
using namespace FvLib;

FvMaterial_Density AutLib::FvLib::FvMaterial_Info::Density_Water()
{
	return FvMaterial_Density((Standard_Real)997.0);
}

FvMaterial_Density AutLib::FvLib::FvMaterial_Info::Density_Air()
{
	return FvMaterial_Density((Standard_Real)1.225);
}

FvMaterial_Viscosity AutLib::FvLib::FvMaterial_Info::Viscosity_Water()
{
	return FvMaterial_Viscosity((Standard_Real)8.9E-4);
}

FvMaterial_Viscosity AutLib::FvLib::FvMaterial_Info::Viscosity_Air()
{
	return FvMaterial_Viscosity((Standard_Real)1.81E-5);
}