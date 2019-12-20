#pragma once
#ifndef _FvInterpolation2d_Header
#define _FvInterpolation2d_Header

#include <FvPrimitives_Scalar.hxx>

namespace AutLib
{
	namespace FvLib
	{
		class FvVector;
		class FvEntity_Face2d;

		class FvInterpolation2d
		{

		private:

			const FvVector& thePhif_;

			const FvVector& thePhi_;

		public:

			virtual Scalar Apply(const FvEntity_Face2d& theFace, const Standard_Boolean theBoundary = Standard_True) const = 0;

			const FvVector& FaceVector() const;

			const FvVector& CellVector() const;

		protected:

			FvInterpolation2d(const FvVector& thePhif, const FvVector& thePhi);
		};
	}
}

#include <FvInterpolation2dI.hxx>

#endif // !FvInterpolation2d_Header
