#pragma once
#ifndef _FvField2d_Scalar_Header
#define _FvField2d_Scalar_Header

#include <Standard_TypeDef.hxx>
#include <FvField2d_Variable.hxx>

namespace AutLib
{
	namespace FvLib
	{
		class FvField2d_Scalar : public FvField2d_Variable
		{

		private:

			Standard_Real theValue_;

		public:

			FvField2d_Scalar();

			FvField2d_Scalar(const Standard_Real theValue);

			virtual ~FvField2d_Scalar();

			void SetValue(const Standard_Real theValue);

			Standard_Real Value() const;
		};
	}
}

#include <FvField2d_ScalarI.hxx>

#endif // !_FvField2d_Scalar_Header
