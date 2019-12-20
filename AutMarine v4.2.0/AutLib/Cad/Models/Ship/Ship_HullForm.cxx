#include <Ship_HullForm.hxx>

#include <Ship_ConstParameters.hxx>

AutLib::CadLib::Ship_HullForm::Ship_HullForm()
{
	//SetDefault();
}

void AutLib::CadLib::Ship_HullForm::SetAftForm(const Ship_SectionForm & AftForm)
{
	AftForm_ = AftForm;
}

void AutLib::CadLib::Ship_HullForm::SetMidForm(const Ship_SectionForm & MidForm)
{
	MidForm_ = MidForm;
}

void AutLib::CadLib::Ship_HullForm::SetFwdForm(const Ship_SectionForm & FwdForm)
{
	FwdForm_ = FwdForm;
}

void AutLib::CadLib::Ship_HullForm::SetMaxAreaLocation(const Standard_Real MaxAreaLocation)
{
	Set_ShipParameterValue
	(
		MaxAreaLocation,
		Ship_ConstParameters::MinAreaLocation(),
		Ship_ConstParameters::MaxAreaLocation(),
		MaxAreaLocation_
	);
}

void AutLib::CadLib::Ship_HullForm::SetSheerHeight(const Standard_Real SheerHeight)
{
	Set_ShipParameterValue
	(
		SheerHeight,
		Ship_ConstParameters::MinSheerHeight(),
		Ship_ConstParameters::MaxSheerHeight(),
		SheerHeight_
	);
}

void AutLib::CadLib::Ship_HullForm::SetSheerPosition(const Standard_Real SheerPosition)
{
	Set_ShipParameterValue
	(
		SheerPosition,
		Ship_ConstParameters::MinSheerPosition(),
		Ship_ConstParameters::MaxSheerPosition(),
		SheerPosition_
	);
}

void AutLib::CadLib::Ship_HullForm::SetFullnessFwd(const Standard_Real FullnessFwd)
{
	Set_ShipParameterValue
	(
		FullnessFwd,
		Ship_ConstParameters::MinFullness(),
		Ship_ConstParameters::MaxFullness(),
		FullnessFwd_
	);
}

void AutLib::CadLib::Ship_HullForm::SetFullnessAft(const Standard_Real FullnessAft)
{
	Set_ShipParameterValue
	(
		FullnessAft,
		Ship_ConstParameters::MinFullness(),
		Ship_ConstParameters::MaxFullness(),
		FullnessAft_
	);
}

AutLib::CadLib::Ship_SectionForm & AutLib::CadLib::Ship_HullForm::AftForm()
{
	return AftForm_;
}

AutLib::CadLib::Ship_SectionForm & AutLib::CadLib::Ship_HullForm::MidForm()
{
	return MidForm_;
}

AutLib::CadLib::Ship_SectionForm & AutLib::CadLib::Ship_HullForm::FwdForm()
{
	return FwdForm_;
}

const AutLib::CadLib::Ship_SectionForm & AutLib::CadLib::Ship_HullForm::AftForm() const
{
	return AftForm_;
}

const AutLib::CadLib::Ship_SectionForm & AutLib::CadLib::Ship_HullForm::MidForm() const
{
	return MidForm_;
}

const AutLib::CadLib::Ship_SectionForm & AutLib::CadLib::Ship_HullForm::FwdForm() const
{
	return FwdForm_;
}

Standard_Real AutLib::CadLib::Ship_HullForm::MaxAreaLocation() const
{
	return MaxAreaLocation_;
}

Standard_Real AutLib::CadLib::Ship_HullForm::SheerHeight() const
{
	return SheerHeight_;
}

Standard_Real AutLib::CadLib::Ship_HullForm::SheerPosition() const
{
	return SheerPosition_;
}

Standard_Real AutLib::CadLib::Ship_HullForm::FullnessFwd() const
{
	return FullnessFwd_;
}

Standard_Real AutLib::CadLib::Ship_HullForm::FullnessAft() const
{
	return FullnessAft_;
}