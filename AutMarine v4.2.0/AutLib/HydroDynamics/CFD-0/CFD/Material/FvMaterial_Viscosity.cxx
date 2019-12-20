#include <FvMaterial_Viscosity.hxx>

AutLib::FvLib::FvMaterial_Viscosity::FvMaterial_Viscosity()
	: theValue_(0)
{
}

AutLib::FvLib::FvMaterial_Viscosity::FvMaterial_Viscosity(const Standard_Real theValue)
	: theValue_(theValue)
{
}

void AutLib::FvLib::FvMaterial_Viscosity::SetValue(const Standard_Real theValue)
{
	theValue_ = theValue;
}