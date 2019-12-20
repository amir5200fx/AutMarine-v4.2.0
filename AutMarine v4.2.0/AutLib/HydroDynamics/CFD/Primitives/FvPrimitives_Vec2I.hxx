#pragma once
inline
void AutLib::FvLib::FvPrimitives_Vec2::SetValue
(
	const Label theIndex,
	const Scalar theValue
)
{
	theValue_[theIndex] = theValue;
}

inline 
Scalar AutLib::FvLib::FvPrimitives_Vec2::Value(const Label theIndex) const
{
	return theValue_[theIndex];
}

inline 
AutLib::FvLib::FvPrimitives_Vec2 & AutLib::FvLib::FvPrimitives_Vec2::operator=(const Scalar theScalar)
{
	theValue_[0] = theValue_[1] = theScalar;
	return *this;
}

inline 
AutLib::FvLib::FvPrimitives_Vec2 & AutLib::FvLib::FvPrimitives_Vec2::operator+=(const Scalar theScalar)
{
	theValue_[0] += theScalar;
	theValue_[1] += theScalar;
	return *this;
}

inline
AutLib::FvLib::FvPrimitives_Vec2 & AutLib::FvLib::FvPrimitives_Vec2::operator-=(const Scalar theScalar)
{
	theValue_[0] -= theScalar;
	theValue_[1] -= theScalar;
	return *this;
}

inline
AutLib::FvLib::FvPrimitives_Vec2 & AutLib::FvLib::FvPrimitives_Vec2::operator*=(const Scalar theScalar)
{
	theValue_[0] *= theScalar;
	theValue_[1] *= theScalar;
	return *this;
}

inline
AutLib::FvLib::FvPrimitives_Vec2 & AutLib::FvLib::FvPrimitives_Vec2::operator/=(const Scalar theScalar)
{
	theValue_[0] /= theScalar;
	theValue_[1] /= theScalar;
	return *this;
}

inline 
AutLib::FvLib::FvPrimitives_Vec2 & AutLib::FvLib::FvPrimitives_Vec2::operator+=(const FvPrimitives_Vec2 & theOther)
{
	theValue_[0] += theOther.theValue_[0];
	theValue_[1] += theOther.theValue_[1];
	return *this;
}

inline
AutLib::FvLib::FvPrimitives_Vec2 & AutLib::FvLib::FvPrimitives_Vec2::operator-=(const FvPrimitives_Vec2 & theOther)
{
	theValue_[0] -= theOther.theValue_[0];
	theValue_[1] -= theOther.theValue_[1];
	return *this;
}

inline 
AutLib::FvLib::FvPrimitives_Vec2 & AutLib::FvLib::FvPrimitives_Vec2::operator+()
{
	return *this;
}

inline 
AutLib::FvLib::FvPrimitives_Vec2 AutLib::FvLib::FvPrimitives_Vec2::operator-()
{
	FvPrimitives_Vec2 Zero;
	return Zero - (*this);
}

inline 
Scalar AutLib::FvLib::FvPrimitives_Vec2::X0() const
{
	return theValue_[0];
}

inline
Scalar AutLib::FvLib::FvPrimitives_Vec2::X1() const
{
	return theValue_[1];
}

inline
Scalar& AutLib::FvLib::FvPrimitives_Vec2::X0()
{
	return theValue_[0];
}

inline
Scalar& AutLib::FvLib::FvPrimitives_Vec2::X1()
{
	return theValue_[1];
}

inline 
Scalar AutLib::FvLib::FvPrimitives_Vec2::TwoNorm() const
{
	return sqrt(TwoNormSQ());
}

inline 
Scalar AutLib::FvLib::FvPrimitives_Vec2::TwoNormSQ() const
{
	return X0()*X0() + X1()*X1();
}

namespace AutLib
{
	namespace FvLib
	{

		inline FvPrimitives_Vec2 AutLib::FvLib::operator+(const FvPrimitives_Vec2 & theV1, const FvPrimitives_Vec2 & theV2)
		{
			FvPrimitives_Vec2 Sum = theV1;
			Sum += theV2;
			return std::move(Sum);
		}

		inline FvPrimitives_Vec2 AutLib::FvLib::operator-(const FvPrimitives_Vec2 & theV1, const FvPrimitives_Vec2 & theV2)
		{
			FvPrimitives_Vec2 Sum = theV1;
			Sum -= theV2;
			return std::move(Sum);
		}

		inline FvPrimitives_Vec2 AutLib::FvLib::operator+(const FvPrimitives_Vec2 & theVec, const Scalar theScalar)
		{
			FvPrimitives_Vec2 Sum = theVec;
			Sum += theScalar;
			return std::move(Sum);
		}

		inline FvPrimitives_Vec2 AutLib::FvLib::operator+(const Scalar theScalar, const FvPrimitives_Vec2 & theVec)
		{
			FvPrimitives_Vec2 Sum = theVec;
			Sum += theScalar;
			return std::move(Sum);
		}

		inline FvPrimitives_Vec2 AutLib::FvLib::operator-(const FvPrimitives_Vec2 & theVec, const Scalar theScalar)
		{
			FvPrimitives_Vec2 Sum = theVec;
			Sum -= theScalar;
			return std::move(Sum);
		}

		inline FvPrimitives_Vec2 AutLib::FvLib::operator*(const FvPrimitives_Vec2 & theVec, const Scalar theScalar)
		{
			FvPrimitives_Vec2 Sum = theVec;
			Sum *= theScalar;
			return std::move(Sum);
		}

		inline FvPrimitives_Vec2 AutLib::FvLib::operator*(const Scalar theScalar, const FvPrimitives_Vec2 & theVec)
		{
			FvPrimitives_Vec2 Sum = theVec;
			Sum *= theScalar;
			return std::move(Sum);
		}

		inline FvPrimitives_Vec2 AutLib::FvLib::operator/(const FvPrimitives_Vec2 & theVec, const Scalar theScalar)
		{
			FvPrimitives_Vec2 Sum = theVec;
			Sum /= theScalar;
			return std::move(Sum);
		}

		inline Scalar AutLib::FvLib::Distance(const FvPrimitives_Vec2 & theV1, const FvPrimitives_Vec2 & theV2)
		{
			return sqrt(DistanceSQ(theV1, theV2));
		}

		inline Scalar AutLib::FvLib::DistanceSQ(const FvPrimitives_Vec2 & theV1, const FvPrimitives_Vec2 & theV2)
		{
			FvPrimitives_Vec2 dV = theV2 - theV1;
			return dV.TwoNormSQ();
		}

		inline Scalar AutLib::FvLib::Dot(const FvPrimitives_Vec2 & theV1, const FvPrimitives_Vec2 & theV2)
		{
			return theV1.X0()*theV2.X0() + theV1.X1()*theV2.X1();
		}

		inline Scalar AutLib::FvLib::Cross(const FvPrimitives_Vec2 & theV1, const FvPrimitives_Vec2 & theV2)
		{
			return theV1.X0()*theV2.X1() - theV2.X0()*theV1.X1();
		}
	}
}