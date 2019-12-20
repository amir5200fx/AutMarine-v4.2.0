#include <Ship_StemForm.hxx>

#include <Ship_ConstParameters.hxx>

AutLib::CadLib::Ship_StemForm::Ship_StemForm()
{
	//SetDefault();
}

void AutLib::CadLib::Ship_StemForm::SetBowRounding(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinBowRounding(),
		Ship_ConstParameters::MaxBowRounding(),
		BowRounding_
	);
}

void AutLib::CadLib::Ship_StemForm::SetStemRake(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinRake(),
		Ship_ConstParameters::MaxRake(),
		StemRake_
	);
}

void AutLib::CadLib::Ship_StemForm::SetStemCurvature(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinStemCurvature(),
		Ship_ConstParameters::MaxStemCurvature(),
		StemCurvature_
	);
}

void AutLib::CadLib::Ship_StemForm::SetStemCurvaturePosition(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinStemCurvaturePosition(),
		Ship_ConstParameters::MaxStemCurvaturePosition(),
		StemCurvaturePos_
	);
}

void AutLib::CadLib::Ship_StemForm::SetForeFootShape(const Standard_Real Value)
{
	Set_ShipParameterValue
	(
		Value,
		Ship_ConstParameters::MinForeFootShape(),
		Ship_ConstParameters::MaxForeFootShape(),
		ForeFootShape_
	);
}

Standard_Real AutLib::CadLib::Ship_StemForm::BowRounding() const
{
	return BowRounding_;
}

Standard_Real AutLib::CadLib::Ship_StemForm::Rake() const
{
	return StemRake_;
}

Standard_Real AutLib::CadLib::Ship_StemForm::StemCurvature() const
{
	return StemCurvature_;
}

Standard_Real AutLib::CadLib::Ship_StemForm::StemCurvaturePosition() const
{
	return StemCurvaturePos_;
}

Standard_Real AutLib::CadLib::Ship_StemForm::ForeFootShape() const
{
	return ForeFootShape_;
}