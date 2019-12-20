#include <Prop_HubForm.hxx>

AutLib::CadLib::Prop_HubForm::Prop_HubForm()
{
}

void AutLib::CadLib::Prop_HubForm::SetHubLength(const Standard_Real theValue)
{
	theHubLength_ = theValue;
}

void AutLib::CadLib::Prop_HubForm::SetHubWeight(const Standard_Real theValue)
{
	theHubWeight_ = theValue;
}

void AutLib::CadLib::Prop_HubForm::SetShaftRadius(const Standard_Real theValue)
{
	theShaftRadius_ = theValue;
}

void AutLib::CadLib::Prop_HubForm::SetShaftOffset(const Standard_Real theValue)
{
	theShaftOffset_ = theValue;
}

void AutLib::CadLib::Prop_HubForm::SetShaftLength(const Standard_Real theValue)
{
	theShaftLenght_ = theValue;
}