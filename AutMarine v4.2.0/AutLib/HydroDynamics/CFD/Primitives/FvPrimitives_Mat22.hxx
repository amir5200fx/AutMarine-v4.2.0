#pragma once
#ifndef _FvPrimitives_Mat22_Header
#define _FvPrimitives_Mat22_Header

#include <FvPrimitives_Scalar.hxx>
#include <FvPrimitives_Label.hxx>
#include <FvPrimitives_Vec2.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvPrimitives_Mat22
		{

		private:

			Scalar theValues_[2][2];

		public:

			FvPrimitives_Mat22();

			FvPrimitives_Mat22(const Scalar theA00, const Scalar theA01, const Scalar theA10, const Scalar theA11);

			void Init(const Scalar theA00, const Scalar theA01, const Scalar theA10, const Scalar theA11);

			void SetValue(const Label theI, const Label theJ, const Scalar theValue);

			void SetA00(const Scalar theValue);

			void SetA01(const Scalar theValue);

			void SetA10(const Scalar theValue);

			void SetA11(const Scalar theValue);

			Scalar Value(const Label theI, const Label theJ) const;

			Scalar A00() const;

			Scalar A01() const;

			Scalar A10() const;

			Scalar A11() const;

			Vec2 Multiply(const Vec2& theVec) const;
		};

		typedef FvPrimitives_Mat22 Mat22;
	}
}

#include <FvPrimitives_Mat22I.hxx>

using AutLib::FvLib::Mat22;

#endif // !_FvPrimitives_Mat22_Header