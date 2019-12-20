#pragma once
#ifndef _FvInterpolation_Mean2d_Header
#define _FvInterpolation_Mean2d_Header

#include <FvInterpolation2d.hxx>
#include <FvEntity_Face2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvInterpolation_Mean2d : public FvInterpolation2d
		{

		private:

		public:

			FvInterpolation_Mean2d(const FvVector& thePhif, const FvVector& thePhi);

			Scalar Apply(const FvEntity_Face2d& theFace, const Standard_Boolean theBoundary = Standard_True) const;
		};
	}
}

#include <FvInterpolation_Mean2dI.hxx>

#endif // !_FvInterpolation_Mean2d_Header
