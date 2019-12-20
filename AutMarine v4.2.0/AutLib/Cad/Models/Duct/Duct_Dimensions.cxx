#include <Duct_Dimensions.hxx>

AutLib::CadLib::Duct_Dimensions::Duct_Dimensions()
{
}

void AutLib::CadLib::Duct_Dimensions::SetNbSections(const Standard_Integer theNbSections)
{
	theNbSections_ = theNbSections;
}

void AutLib::CadLib::Duct_Dimensions::SetOveralLength(const Standard_Real theOveralLength)
{
	theOveralLength_ = theOveralLength;
}

void AutLib::CadLib::Duct_Dimensions::SetBreadthAtInlet(const Standard_Real theBeamAtInlet)
{
	theBreadthAtInlet_ = theBeamAtInlet;
}

void AutLib::CadLib::Duct_Dimensions::SetBreadthAtOutlet(const Standard_Real theBeamAtOutlet)
{
	theBreadthAtOutlet_ = theBeamAtOutlet;
}

void AutLib::CadLib::Duct_Dimensions::SetDepthAtInlet(const Standard_Real theDepthAtInlet)
{
	theDepthAtInlet_ = theDepthAtInlet;
}

void AutLib::CadLib::Duct_Dimensions::SetDepthAtOutlet(const Standard_Real theDepthAtOutlet)
{
	theDepthAtOutlet_ = theDepthAtOutlet;
}

void AutLib::CadLib::Duct_Dimensions::SetHeightAtOutlet(const Standard_Real theHeightAtOutlet)
{
	theHeightAtOutlet_ = theHeightAtOutlet;
}