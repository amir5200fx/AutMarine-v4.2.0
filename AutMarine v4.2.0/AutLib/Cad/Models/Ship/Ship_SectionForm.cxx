#include <Ship_SectionForm.hxx>

#include <Ship_ConstParameters.hxx>

AutLib::CadLib::Ship_SectionForm::Ship_SectionForm()
{
	//SetDefault();
}

void AutLib::CadLib::Ship_SectionForm::SetTightness(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinTightness(),
		Ship_ConstParameters::MaxTightness(),
		theTightness_
	);
}

void AutLib::CadLib::Ship_SectionForm::SetDeadRise(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinDeadRise(),
		Ship_ConstParameters::MaxDeadRise(),
		theDeadRise_
	);
}

void AutLib::CadLib::Ship_SectionForm::SetSideSlope(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinSideSlope(),
		Ship_ConstParameters::MaxSideSlope(),
		theSideSlope_
	);
}

void AutLib::CadLib::Ship_SectionForm::SetFlare(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinFlare(),
		Ship_ConstParameters::MaxFlare(),
		theFlare_
	);
}

void AutLib::CadLib::Ship_SectionForm::SetSkeg(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinSkeg(),
		Ship_ConstParameters::MaxSkeg(),
		theskeg_
	);
}

Standard_Real AutLib::CadLib::Ship_SectionForm::Tightness() const
{
	return theTightness_;
}

Standard_Real AutLib::CadLib::Ship_SectionForm::DeadRise() const
{
	return theDeadRise_;
}

Standard_Real AutLib::CadLib::Ship_SectionForm::SideSlope() const
{
	return theSideSlope_;
}

Standard_Real AutLib::CadLib::Ship_SectionForm::Flare() const
{
	return theFlare_;
}

Standard_Real AutLib::CadLib::Ship_SectionForm::Skeg() const
{
	return theskeg_;
}