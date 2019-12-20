#include <FvField2d_Vector.hxx>

AutLib::FvLib::FvField2d_Vector::FvField2d_Vector()
	: theValue_(0, 0)
{
}

AutLib::FvLib::FvField2d_Vector::FvField2d_Vector(const Geom_Pnt2d & theValue)
	: theValue_(theValue)
{
}

AutLib::FvLib::FvField2d_Vector::~FvField2d_Vector()
{
}

void AutLib::FvLib::FvField2d_Vector::SetValue(const Geom_Pnt2d & theValue)
{
	theValue_ = theValue;
}