#pragma once
#ifndef _FvVectorField_Scalar_Header
#define _FvVectorField_Scalar_Header

#include <FvVectorField.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvVector;

		class FvVectorField_Scalar : public FvVectorField
		{

		protected:
			
			FvVector& theXSource_;

		public:

			FvVectorField_Scalar(FvVector& theSource, FvVector& theX);

			virtual ~FvVectorField_Scalar();

			const FvVector& xSource() const;

			FvVector& xSource();
		};
	}
}

#include <FvVectorField_ScalarI.hxx>

#endif // !_FvVectorField_Scalar_Header
