#include <FvField2d_Scalar.hxx>

AutLib::FvLib::FvField2d_Scalar::FvField2d_Scalar()
	: theValue_(0)
{
}

AutLib::FvLib::FvField2d_Scalar::FvField2d_Scalar(const Standard_Real theValue)
	: theValue_(theValue)
{
}

AutLib::FvLib::FvField2d_Scalar::~FvField2d_Scalar()
{
}

void AutLib::FvLib::FvField2d_Scalar::SetValue(const Standard_Real theValue)
{
	theValue_ = theValue;
}