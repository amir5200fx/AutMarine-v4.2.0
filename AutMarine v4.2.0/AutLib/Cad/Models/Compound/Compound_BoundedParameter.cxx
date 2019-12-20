#include <Compound_BoundedParameter.hxx>

AutLib::CadLib::Compound_BoundedParameter::Compound_BoundedParameter()
	: theMin_(RealFirst())
	, theMax_(RealLast())
{
}

AutLib::CadLib::Compound_BoundedParameter::Compound_BoundedParameter
(
	const Standard_Real theMin,
	const Standard_Real theMax
)
	: theMin_(theMin)
	, theMax_(theMax)
{
}

void AutLib::CadLib::Compound_BoundedParameter::Init
(
	const Standard_Real theMin, 
	const Standard_Real theMax
)
{
	theMin_ = theMin;
	theMax_ = theMax;
}

void AutLib::CadLib::Compound_BoundedParameter::SetMin(const Standard_Real theMin)
{
	theMin_ = theMin;
}

void AutLib::CadLib::Compound_BoundedParameter::SetMax(const Standard_Real theMax)
{
	theMax_ = theMax;
}

void AutLib::CadLib::Compound_BoundedParameter::Print(Standard_OStream & Ostream) const
{
	Ostream << "[" << theMin_ << ", " << theMax_ << "]";
}