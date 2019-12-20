#include <FvReferences_Gravity.hxx>

#include <FvReferences_Info.hxx>

AutLib::FvLib::FvReferences_Gravity::FvReferences_Gravity()
	: theValue_(FvReferences_Info::Gravity())
{
}

void AutLib::FvLib::FvReferences_Gravity::SetValue(const Geom_Pnt2d & theValue)
{
	theValue_ = theValue;
}