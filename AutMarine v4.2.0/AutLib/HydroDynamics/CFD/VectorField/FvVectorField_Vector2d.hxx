#pragma once
#ifndef _FvVectorField_Vector2d_Header
#define _FvVectorField_Vector2d_Header

#include <FvVectorField_Scalar.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvVectorField_Vector2d : public FvVectorField_Scalar
		{

		private:

			FvVector& theYSource_;

		public:

			FvVectorField_Vector2d(FvVector& theXSource, FvVector& theYSource, FvVector& theX, FvVector& theY);

			virtual ~FvVectorField_Vector2d();

			const FvVector& ySource() const;

			FvVector& ySource();
		};
	}
}

#include <FvVectorField_Vector2dI.hxx>

#endif // !_FvVectorField_Vector2d_Header
