#include <Prop_CamberForm.hxx>

AutLib::CadLib::Prop_CamberForm::Prop_CamberForm()
{
}

void AutLib::CadLib::Prop_CamberForm::SetRootCamber(const Standard_Real Value)
{
	theRootCamber_ = Value;
}

void AutLib::CadLib::Prop_CamberForm::SetTipCamber(const Standard_Real Value)
{
	theTipCamber_ = Value;
}

void AutLib::CadLib::Prop_CamberForm::SetMaxCamber(const Standard_Real Value)
{
	theMaxCamber_ = Value;
}

void AutLib::CadLib::Prop_CamberForm::SetMaxCamberLocation(const Standard_Real Value)
{
	theMaxCamberLocation_ = Value;
}

void AutLib::CadLib::Prop_CamberForm::SetRootWeight(const Standard_Real Value)
{
	theRootWeight_ = Value;
}

void AutLib::CadLib::Prop_CamberForm::SetTipWeight(const Standard_Real Value)
{
	theTipWeight_ = Value;
}