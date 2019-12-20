#include <Prop_ThicknessForm.hxx>

AutLib::CadLib::Prop_ThicknessForm::Prop_ThicknessForm()
{
}

void AutLib::CadLib::Prop_ThicknessForm::SetRootThickness(const Standard_Real Value)
{
	theRootThickness_ = Value;
}

void AutLib::CadLib::Prop_ThicknessForm::SetTipThickness(const Standard_Real Value)
{
	theTipThickness_ = Value;
}

void AutLib::CadLib::Prop_ThicknessForm::SetRootSteep(const Standard_Real Value)
{
	theRootSteep_ = Value;
}

void AutLib::CadLib::Prop_ThicknessForm::SetTipSteep(const Standard_Real Value)
{
	theTipSteep_ = Value;
}