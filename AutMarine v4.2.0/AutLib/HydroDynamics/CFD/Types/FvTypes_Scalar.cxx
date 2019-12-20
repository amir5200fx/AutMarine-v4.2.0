#include <FvTypes_Scalar.hxx>

AutLib::FvLib::FvTypes_Scalar::FvTypes_Scalar()
	: theValue_((Scalar)0)
{
}

AutLib::FvLib::FvTypes_Scalar::FvTypes_Scalar(const Scalar theValue)
	: theValue_(theValue)
{
}

AutLib::FvLib::FvTypes_Scalar::~FvTypes_Scalar()
{
}