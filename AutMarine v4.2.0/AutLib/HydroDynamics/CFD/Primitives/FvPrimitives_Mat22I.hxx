#pragma once
inline
void AutLib::FvLib::FvPrimitives_Mat22::SetValue
(
	const Label theI,
	const Label theJ,
	const Scalar theValue
)
{
	theValues_[theI][theJ] = theValue;
}

inline 
void AutLib::FvLib::FvPrimitives_Mat22::SetA00(const Scalar theValue)
{
	theValues_[0][0] = theValue;
}

inline
void AutLib::FvLib::FvPrimitives_Mat22::SetA10(const Scalar theValue)
{
	theValues_[1][0] = theValue;
}

inline
void AutLib::FvLib::FvPrimitives_Mat22::SetA01(const Scalar theValue)
{
	theValues_[0][1] = theValue;
}

inline
void AutLib::FvLib::FvPrimitives_Mat22::SetA11(const Scalar theValue)
{
	theValues_[1][1] = theValue;
}

inline 
Scalar AutLib::FvLib::FvPrimitives_Mat22::Value
(
	const Label theI,
	const Label theJ
) const
{
	return theValues_[theI][theJ];
}

inline 
Scalar AutLib::FvLib::FvPrimitives_Mat22::A00() const
{
	return theValues_[0][0];
}

inline
Scalar AutLib::FvLib::FvPrimitives_Mat22::A01() const
{
	return theValues_[0][1];
}

inline
Scalar AutLib::FvLib::FvPrimitives_Mat22::A10() const
{
	return theValues_[1][0];
}

inline
Scalar AutLib::FvLib::FvPrimitives_Mat22::A11() const
{
	return theValues_[1][1];
}

inline 
Vec2 AutLib::FvLib::FvPrimitives_Mat22::Multiply(const Vec2 & theVec) const
{
	Vec2 Vector(A00()*theVec.X0() + A01()*theVec.X1(), A10()*theVec.X0() + A11()*theVec.X1());
	return std::move(Vector);
}