#include <FvMaterial_Viscosity.hxx>

AutLib::FvLib::FvMaterial_Viscosity::FvMaterial_Viscosity()
	: theValue_(0)
{
}

AutLib::FvLib::FvMaterial_Viscosity::FvMaterial_Viscosity(const Scalar theValue)
	: theValue_(theValue)
{
}

void AutLib::FvLib::FvMaterial_Viscosity::SetValue(const Scalar theValue)
{
	theValue_ = theValue;
}