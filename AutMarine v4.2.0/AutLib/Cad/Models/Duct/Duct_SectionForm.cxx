#include <Duct_SectionForm.hxx>

AutLib::CadLib::Duct_SectionForm::Duct_SectionForm()
{
}

void AutLib::CadLib::Duct_SectionForm::SetSideSlope(const Standard_Real theSideSlope)
{
	theSideSlope_ = theSideSlope;
}

void AutLib::CadLib::Duct_SectionForm::SetUpperTightness(const Standard_Real theUpperTightness)
{
	theUpperTightness_ = theUpperTightness;
}

void AutLib::CadLib::Duct_SectionForm::SetLowerTightness(const Standard_Real theLowerTightness)
{
	theLowerTightness_ = theLowerTightness;
}

void AutLib::CadLib::Duct_SectionForm::SetWidth(const Standard_Real theHeight)
{
	theWidth_ = theHeight;
}