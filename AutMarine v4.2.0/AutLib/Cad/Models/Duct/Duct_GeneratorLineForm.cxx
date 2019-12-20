#include <Duct_GeneratorLineForm.hxx>

AutLib::CadLib::Duct_GeneratorLineForm::Duct_GeneratorLineForm()
{
}

void AutLib::CadLib::Duct_GeneratorLineForm::SetPosition(const Standard_Real Value)
{
	thePosition_ = Value;
}

void AutLib::CadLib::Duct_GeneratorLineForm::SetRisePoint(const Standard_Real Value)
{
	theRisePoint_ = Value;
}

void AutLib::CadLib::Duct_GeneratorLineForm::SetRiseTangent(const Standard_Real Value)
{
	theRiseTangent_ = Value;
}

void AutLib::CadLib::Duct_GeneratorLineForm::SetOutletTangent(const Standard_Real Value)
{
	theOutletTangent_ = Value;
}