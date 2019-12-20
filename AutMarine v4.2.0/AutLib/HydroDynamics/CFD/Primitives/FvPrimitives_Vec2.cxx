#include <FvPrimitives_Vec2.hxx>

AutLib::FvLib::FvPrimitives_Vec2::FvPrimitives_Vec2()
{
	theValue_[0] = (Scalar)0;
	theValue_[1] = (Scalar)0;
}

AutLib::FvLib::FvPrimitives_Vec2::FvPrimitives_Vec2
(
	const Scalar theX0, 
	const Scalar theX1
)
{
	theValue_[0] = theX0;
	theValue_[1] = theX1;
}

void AutLib::FvLib::FvPrimitives_Vec2::Init
(
	const Scalar theX0,
	const Scalar theX1
)
{
	theValue_[0] = theX0;
	theValue_[1] = theX1;
}

void AutLib::FvLib::FvPrimitives_Vec2::Print(Standard_OStream & out) const
{
	out << X0() << "  " << X1();
}

Standard_OStream & AutLib::FvLib::operator<<(Standard_OStream & Ostream, const FvPrimitives_Vec2 & theV)
{
	Ostream << theV.X0() << "  " << theV.X1();
	return Ostream;
}

Standard_IStream & AutLib::FvLib::operator>>(Standard_IStream & Ostream, FvPrimitives_Vec2 & theV)
{
	Scalar X0, X1;
	Ostream >> X0 >> X1;
	theV.Init(X0, X1);
	return Ostream;
}