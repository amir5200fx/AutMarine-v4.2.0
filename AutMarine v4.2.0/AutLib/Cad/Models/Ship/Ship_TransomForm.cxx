#include <Ship_TransomForm.hxx>

#include <Ship_ConstParameters.hxx>

AutLib::CadLib::Ship_TransomForm::Ship_TransomForm()
{
}

void AutLib::CadLib::Ship_TransomForm::SetRake(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinRake(),
		Ship_ConstParameters::MaxRake(),
		theRake_
	);
}

void AutLib::CadLib::Ship_TransomForm::SetWidth(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinWidth(),
		Ship_ConstParameters::MaxWidth(),
		theWidth_
	);
}

Standard_Real AutLib::CadLib::Ship_TransomForm::Rake() const
{
	return theRake_;
}

Standard_Real AutLib::CadLib::Ship_TransomForm::Width() const
{
	return theWidth_;
}