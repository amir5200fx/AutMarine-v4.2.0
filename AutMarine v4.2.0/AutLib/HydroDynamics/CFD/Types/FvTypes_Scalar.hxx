#pragma once
#ifndef _FvTypes_Scalar_Header
#define _FvTypes_Scalar_Header

#include <FvTypes.hxx>
#include <FvPrimitives_Scalar.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvTypes_Scalar : public FvTypes
		{

		private:

			Scalar theValue_;

		public:

			FvTypes_Scalar();

			FvTypes_Scalar(const Scalar theValue);

			virtual ~FvTypes_Scalar();

			void SetValue(const Scalar theValue);

			Scalar Value() const;
		};
	}
}

#include <FvTypes_ScalarI.hxx>

#endif // !_FvTypes_Scalar_Header
