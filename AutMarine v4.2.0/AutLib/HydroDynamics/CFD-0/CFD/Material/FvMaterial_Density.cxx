#include <FvMaterial_Density.hxx>

AutLib::FvLib::FvMaterial_Density::FvMaterial_Density()
	: theValue_(0)
{
}

AutLib::FvLib::FvMaterial_Density::FvMaterial_Density(const Standard_Real theValue)
	: theValue_(theValue)
{
}

void AutLib::FvLib::FvMaterial_Density::SteValue(const Standard_Real theValue)
{
	theValue_ = theValue;
}