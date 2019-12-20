#include <Compound_ShipPropellerSystemParameters.hxx>

#include <Global_Macros.hxx>
#include <Global_Debug.hxx>

static const Standard_Real DEFAULT_X = 0.5;
static const Standard_Real DEFAULT_Y = 0.5;
static const Standard_Real DEFAULT_Z = 0.5;
static const Standard_Real DEFAULT_SHAFT_INCLINATION = 0.0;

AutLib::CadLib::Compound_ShipPropellerSystemParameters::Compound_ShipPropellerSystemParameters()
	: theX_(DEFAULT_X)
	, theY_(DEFAULT_Y)
	, theZ_(DEFAULT_Z)
	, theShaftInclination_(DEFAULT_SHAFT_INCLINATION)
{
}

void AutLib::CadLib::Compound_ShipPropellerSystemParameters::SetX(const Standard_Real theX)
{
	//if (NOT INSIDE(theX, 0, 1)) { THROW_STANDARD_EXCEPTION("Invalid Data: not 0<value<1"); }
	theX_ = theX;
}

void AutLib::CadLib::Compound_ShipPropellerSystemParameters::SetY(const Standard_Real theX)
{
	//if (NOT INSIDE(theX, 0, 1)) { THROW_STANDARD_EXCEPTION("Invalid Data: not 0<value<1"); }
	theY_ = theX;
}

void AutLib::CadLib::Compound_ShipPropellerSystemParameters::SetZ(const Standard_Real theX)
{
	//if (NOT INSIDE(theX, 0, 1)) { THROW_STANDARD_EXCEPTION("Invalid Data: not 0<value<1"); }
	theZ_ = theX;
}

void AutLib::CadLib::Compound_ShipPropellerSystemParameters::SetShaftInclination(const Standard_Real theX)
{
	//if (NOT INSIDE(theX, 0, 1)) { THROW_STANDARD_EXCEPTION("Invalid Data: not 0<value<1"); }
	theShaftInclination_ = theX;
}