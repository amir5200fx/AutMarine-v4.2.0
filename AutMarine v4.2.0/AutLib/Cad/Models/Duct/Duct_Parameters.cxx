#include <Duct_Parameters.hxx>

AutLib::CadLib::Duct_Parameters::Duct_Parameters()
{
}

void AutLib::CadLib::Duct_Parameters::SetDimensions(const Duct_Dimensions & theDimensions)
{
	theDimensions_ = theDimensions;
}

void AutLib::CadLib::Duct_Parameters::SetHullForm(const Duct_HullForm & theHullForm)
{
	theHull_ = theHullForm;
}

void AutLib::CadLib::Duct_Parameters::SetGenerator(const Duct_GeneratorLineForm & theGenerator)
{
	theGenerator_ = theGenerator;
}