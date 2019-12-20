#include <Ship_KeelForm.hxx>

#include <Ship_ConstParameters.hxx>

AutLib::CadLib::Ship_KeelForm::Ship_KeelForm()
{
	//SetDefault();
}

void AutLib::CadLib::Ship_KeelForm::SetKeelPosition(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinKeelPosition(),
		Ship_ConstParameters::MaxKeelPosition(),
		KeelPosition_
	);
}

void AutLib::CadLib::Ship_KeelForm::SetKeelRisePoint(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinKeelRisePoint(),
		Ship_ConstParameters::MaxKeelRisePoint(),
		KeelRisePoint_
	);
}

void AutLib::CadLib::Ship_KeelForm::SetKeelRiseTangent(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinKeelRiseTangent(),
		Ship_ConstParameters::MaxKeelRiseTangent(),
		KeelRiseTangent_
	);
}

void AutLib::CadLib::Ship_KeelForm::SetKeelTransomTangent(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinKeelTransomTangent(),
		Ship_ConstParameters::MaxKeelTransomTangent(),
		KeelTransomTangent_
	);
}

Standard_Real AutLib::CadLib::Ship_KeelForm::KeelPosition() const
{
	return KeelPosition_;
}

Standard_Real AutLib::CadLib::Ship_KeelForm::KeelRisePoint() const
{
	return KeelRisePoint_;
}

Standard_Real AutLib::CadLib::Ship_KeelForm::KeelRiseTangent() const
{
	return KeelRiseTangent_;
}

Standard_Real AutLib::CadLib::Ship_KeelForm::KeelTransomTangent() const
{
	return KeelTransomTangent_;
}