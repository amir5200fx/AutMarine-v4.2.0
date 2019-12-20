#include <FvMaterial_Density.hxx>

AutLib::FvLib::FvMaterial_Density::FvMaterial_Density()
	: theValue_(0)
{
}

AutLib::FvLib::FvMaterial_Density::FvMaterial_Density(const Scalar theValue)
	: theValue_(theValue)
{
}

void AutLib::FvLib::FvMaterial_Density::SteValue(const Scalar theValue)
{
	theValue_ = theValue;
}