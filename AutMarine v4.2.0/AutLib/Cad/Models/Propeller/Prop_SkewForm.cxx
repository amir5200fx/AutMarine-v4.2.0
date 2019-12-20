#include <Prop_SkewForm.hxx>

AutLib::CadLib::Prop_SkewForm::Prop_SkewForm()
{
}

void AutLib::CadLib::Prop_SkewForm::SetTipSkew(const Standard_Real Value)
{
	theTipSkew_ = Value;
}

void AutLib::CadLib::Prop_SkewForm::SetTipSteep(const Standard_Real Value)
{
	theTipSteep_ = Value;
}

void AutLib::CadLib::Prop_SkewForm::SetRootSteep(const Standard_Real Value)
{
	theRootSteep_ = Value;
}