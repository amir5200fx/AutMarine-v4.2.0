#include <Prop_PitchForm.hxx>

AutLib::CadLib::Prop_PitchForm::Prop_PitchForm()
{
}

void AutLib::CadLib::Prop_PitchForm::SetRootPitch(const Standard_Real RootPitch)
{
	theRootPitch_ = RootPitch;
}

void AutLib::CadLib::Prop_PitchForm::SetRootSteep(const Standard_Real RootSteep)
{
	theRootSteep_ = RootSteep;
}

void AutLib::CadLib::Prop_PitchForm::SetTipPitch(const Standard_Real TipPitch)
{
	theTipPitch_ = TipPitch;
}

void AutLib::CadLib::Prop_PitchForm::SetTipSteep(const Standard_Real TipSteep)
{
	theTipSteep_ = TipSteep;
}