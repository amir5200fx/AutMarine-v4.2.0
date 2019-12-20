#pragma once
#ifndef _FvPrimitives_Vec2_Header
#define _FvPrimitives_Vec2_Header

#include <FvPrimitives_Label.hxx>
#include <FvPrimitives_Scalar.hxx>
#include <Standard_OStream.hxx>
#include <Standard_IStream.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvPrimitives_Vec2
		{

		private:

			Scalar theValue_[2];

		public:

			FvPrimitives_Vec2();

			FvPrimitives_Vec2(const Scalar theX0, const Scalar theX1);

			void Init(const Scalar theX0, const Scalar theX1);

			void SetValue(const Label theIndex, const Scalar theValue);

			Scalar Value(const Label theIndex) const;

			FvPrimitives_Vec2& operator=(const Scalar theScalar);

			FvPrimitives_Vec2& operator+=(const Scalar theScalar);

			FvPrimitives_Vec2& operator-=(const Scalar theScalar);

			FvPrimitives_Vec2& operator*=(const Scalar theScalar);

			FvPrimitives_Vec2& operator/=(const Scalar theScalar);

			FvPrimitives_Vec2& operator+=(const FvPrimitives_Vec2& theOther);

			FvPrimitives_Vec2& operator-=(const FvPrimitives_Vec2& theOther);

			FvPrimitives_Vec2& operator+();

			FvPrimitives_Vec2 operator-();

			Scalar X0() const;

			Scalar X1() const;

			Scalar& X0();

			Scalar& X1();

			Scalar TwoNorm() const;

			Scalar TwoNormSQ() const;

			void Print(Standard_OStream& out = cout) const;

			friend FvPrimitives_Vec2 operator+(const FvPrimitives_Vec2& theV1, const FvPrimitives_Vec2& theV2);

			friend FvPrimitives_Vec2 operator-(const FvPrimitives_Vec2& theV1, const FvPrimitives_Vec2& theV2);

			friend FvPrimitives_Vec2 operator+(const FvPrimitives_Vec2& theVec, const Scalar theScalar);

			friend FvPrimitives_Vec2 operator+(const Scalar theScalar, const FvPrimitives_Vec2& theVec);

			friend FvPrimitives_Vec2 operator-(const FvPrimitives_Vec2& theVec, const Scalar theScalar);

			friend FvPrimitives_Vec2 operator*(const FvPrimitives_Vec2& theVec, const Scalar theScalar);

			friend FvPrimitives_Vec2 operator*(const Scalar theScalar, const FvPrimitives_Vec2& theVec);

			friend FvPrimitives_Vec2 operator/(const FvPrimitives_Vec2& theVec, const Scalar theScalar);

			friend Scalar Distance(const FvPrimitives_Vec2& theV1, const FvPrimitives_Vec2& theV2);

			friend Scalar DistanceSQ(const FvPrimitives_Vec2& theV1, const FvPrimitives_Vec2& theV2);

			friend Scalar Dot(const FvPrimitives_Vec2& theV1, const FvPrimitives_Vec2& theV2);

			friend Scalar Cross(const FvPrimitives_Vec2& theV1, const FvPrimitives_Vec2& theV2);

			friend Standard_OStream& operator<<(Standard_OStream& Ostream, const FvPrimitives_Vec2& theV);

			friend Standard_IStream& operator>>(Standard_IStream& Ostream, FvPrimitives_Vec2& theV);
		};

		typedef FvPrimitives_Vec2 Vec2;
	}
}

#include <FvPrimitives_Vec2I.hxx>

using AutLib::FvLib::Vec2;

#endif // !_FvPrimitives_Vec2_Header
