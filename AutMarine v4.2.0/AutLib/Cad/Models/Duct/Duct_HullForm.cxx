#include <Duct_HullForm.hxx>

#include <Duct_ConstParameters.hxx>

AutLib::CadLib::Duct_HullForm::Duct_HullForm()
{
}

void AutLib::CadLib::Duct_HullForm::SetInletForm(const Duct_SectionForm& theInletForm)
{
	theInletForm_ = theInletForm;
}

void AutLib::CadLib::Duct_HullForm::SetOutletForm(const Duct_SectionForm & theOutletForm)
{
	theOutletForm_ = theOutletForm;
}

void AutLib::CadLib::Duct_HullForm::SetMidForm(const Duct_SectionForm & theMidForm)
{
	theMidForm_ = theMidForm;
}

void AutLib::CadLib::Duct_HullForm::SetMidLocation(const Standard_Real theMidLocation)
{
	Set_DuctParameterValue(theMidLocation, 0, 1, theMidLocation_);
}