#pragma once
#ifndef _FvTypes_Tensor2_Header
#define _FvTypes_Tensor2_Header

#include <FvTypes.hxx>
#include <FvPrimitives_Tensor2.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvTypes_Tensor2 : public FvTypes
		{

		private:

			Tensor2 theValue_;

		public:

			FvTypes_Tensor2();

			FvTypes_Tensor2(const Tensor2& theValue);

			virtual ~FvTypes_Tensor2();

			void SetValue(const Tensor2& theValue);

			const Tensor2& Value() const;
		};
	}
}

#include <FvTypes_Tensor2I.hxx>

#endif // !_FvTypes_Tensor2_Header
