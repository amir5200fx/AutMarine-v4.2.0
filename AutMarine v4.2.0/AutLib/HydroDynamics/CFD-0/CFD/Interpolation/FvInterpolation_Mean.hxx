#pragma once
#ifndef _FvInterpolation_Mean_Header
#define _FvInterpolation_Mean_Header

#include <FvInterpolation.hxx>
#include <FvEntity_Face2d.hxx>
#include <FvEntity_Element2d.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvInterpolation_Mean : public FvInterpolation
		{

		private:


		public:

			FvInterpolation_Mean(const FvVariables_Faces2d& thePhif, const FvVariables_Elements2d& thePhi);

			virtual Standard_Real Interpolate(const FvEntity_Face2d& theFace, const Standard_Boolean theBoundary = Standard_True) const;

			static Standard_Real Interpolate(const FvEntity_Face2d& theFace, const FvVariables_Faces2d& thePhif, const FvVariables_Elements2d& thePhi, const Standard_Boolean theBoundary = Standard_True);

			static Geom_Pnt2d Interpolate(const FvEntity_Face2d& theFace, const TColGeom_Ary1dOfPnt2d& thePhi);
		};
	}
}

#include <FvInterpolation_MeanI.hxx>

#endif // !_FvInterpolation_Mean_Header
