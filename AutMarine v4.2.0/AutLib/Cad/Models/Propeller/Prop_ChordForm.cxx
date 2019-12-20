#include <Prop_ChordForm.hxx>

AutLib::CadLib::Prop_ChordForm::Prop_ChordForm()
{
}

void AutLib::CadLib::Prop_ChordForm::SetRootChord(const Standard_Real Value)
{
	theRootChord_ = Value;
}

void AutLib::CadLib::Prop_ChordForm::SetTipChord(const Standard_Real Value)
{
	theTipChord_ = Value;
}

void AutLib::CadLib::Prop_ChordForm::SetMaxChord(const Standard_Real Value)
{
	theMaxChord_ = Value;
}

void AutLib::CadLib::Prop_ChordForm::SetMaxChordLocation(const Standard_Real Value)
{
	theMaxChordLocation_ = Value;
}

void AutLib::CadLib::Prop_ChordForm::SetRootWeight(const Standard_Real Value)
{
	theRootWeight_ = Value;
}

void AutLib::CadLib::Prop_ChordForm::SetTipWeight(const Standard_Real Value)
{
	theTipWeight_ = Value;
}