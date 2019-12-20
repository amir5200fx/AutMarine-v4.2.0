#pragma once
#ifndef _FvInterpolation_Geometric2d_Header
#define _FvInterpolation_Geometric2d_Header

#include <FvInterpolation2d.hxx>
#include <FvEntity_Face2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvInterpolation_Geometric2d : public FvInterpolation2d
		{

		private:


		public:

			FvInterpolation_Geometric2d(const FvVector& thePhif, const FvVector& thePhi);

			Scalar Apply(const FvEntity_Face2d& theFace, const Standard_Boolean theBoundary = Standard_True) const;
		};
	}
}

#include <FvInterpolation_Geometric2dI.hxx>

#endif // !_FvInterpolation_Geometric2d_Header
