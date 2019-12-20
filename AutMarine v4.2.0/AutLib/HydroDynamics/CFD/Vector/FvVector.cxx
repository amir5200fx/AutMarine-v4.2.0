#include <FvVector.hxx>

AutLib::FvLib::FvVector::FvVector()
	: theName_("Unkown Vector")
{
}

void AutLib::FvLib::FvVector::SetName(const Standard_String theName)
{
	theName_ = theName;
}