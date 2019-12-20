#include <Duct_Profiles.hxx>

AutLib::CadLib::Duct_Profiles::Duct_Profiles()
{
}

void AutLib::CadLib::Duct_Profiles::SetSection
(
	const Standard_Integer theIndex, 
	const Duct_DuctParameterProfile & theProfile
)
{
	Debug_Bad_Index_Array1(theIndex, theSections_);
	theSections_.SetValue(theIndex, theProfile);
}

void AutLib::CadLib::Duct_Profiles::SetBreadth(const Duct_DuctParameterProfile & theProfile)
{
	theBreadth_ = theProfile;
}

void AutLib::CadLib::Duct_Profiles::SetDepth(const Duct_DuctParameterProfile & theProfile)
{
	theDepth_ = theProfile;
}

void AutLib::CadLib::Duct_Profiles::SetMemory(const Standard_Integer nbSections)
{
	theSections_.Resize(nbSections);
}