#include <FvReferences_Pressure.hxx>

#include <FvReferences_Info.hxx>

AutLib::FvLib::FvReferences_Pressure::FvReferences_Pressure()
	: theValue_(FvReferences_Info::Pressure())
{
}

void AutLib::FvLib::FvReferences_Pressure::SetValue(const Standard_Real theValue)
{
	theValue_ = theValue;
}