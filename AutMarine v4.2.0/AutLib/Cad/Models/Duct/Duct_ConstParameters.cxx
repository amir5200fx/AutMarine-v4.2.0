#include <Duct_ConstParameters.hxx>

Standard_Integer AutLib::CadLib::Duct_ConstParameters::LevelOfSmoothing()
{
	return (Standard_Integer)3;
}

Standard_Real AutLib::CadLib::Duct_ConstParameters::SmoothWeight()
{
	return (Standard_Real)0.25;
}

Standard_Integer AutLib::CadLib::Duct_ConstParameters::MaxNbSections()
{
	return (Standard_Integer)100;
}

Standard_Integer AutLib::CadLib::Duct_ConstParameters::MinNbSections()
{
	return (Standard_Integer)5;
}