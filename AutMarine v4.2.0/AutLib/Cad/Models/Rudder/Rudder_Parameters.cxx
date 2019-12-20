#include <Rudder_Parameters.hxx>

AutLib::CadLib::Rudder_Parameters::Rudder_Parameters()
{
}

void AutLib::CadLib::Rudder_Parameters::SetChord(const Standard_Real theValue)
{
	theChord_ = theValue;
}

void AutLib::CadLib::Rudder_Parameters::SetSpan(const Standard_Real theValue)
{
	theSpan_ = theValue;
}

void AutLib::CadLib::Rudder_Parameters::SetThickness(const Standard_Real theValue)
{
	theThickness_ = theValue;
}

void AutLib::CadLib::Rudder_Parameters::SetShaftLength(const Standard_Real theValue)
{
	theShaftLength_ = theValue;
}

void AutLib::CadLib::Rudder_Parameters::SetShaftDiameter(const Standard_Real theValue)
{
	theShaftDiameter_ = theValue;
}

void AutLib::CadLib::Rudder_Parameters::SetShaftPosition(const Standard_Real theValue)
{
	theShaftPosition_ = theValue;
}