#include <Compound_ShipRudderSystemParametersBounds.hxx>

AutLib::CadLib::Compound_ShipRudderSystemParametersBounds::Compound_ShipRudderSystemParametersBounds()
{
}

void AutLib::CadLib::Compound_ShipRudderSystemParametersBounds::SetX(const Compound_BoundedParameter & theX)
{
	theX_ = theX;
}

void AutLib::CadLib::Compound_ShipRudderSystemParametersBounds::SetY(const Compound_BoundedParameter & theY)
{
	theY_ = theY;
}

void AutLib::CadLib::Compound_ShipRudderSystemParametersBounds::SetZ(const Compound_BoundedParameter & theZ)
{
	theZ_ = theZ;
}

void AutLib::CadLib::Compound_ShipRudderSystemParametersBounds::SetShaftInclination(const Compound_BoundedParameter & theInclination)
{
	theShaftInclination_ = theInclination;
}