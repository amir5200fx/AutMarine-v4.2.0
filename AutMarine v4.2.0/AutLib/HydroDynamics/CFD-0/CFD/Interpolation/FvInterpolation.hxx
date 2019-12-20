#pragma once
#ifndef _FvInterpolation_Header
#define _FvInterpolation_Header

#include <Standard_TypeDef.hxx>
#include <FvVariables_Faces2d.hxx>
#include <FvVariables_Elements2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvEntity_Face2d;

		class FvInterpolation
		{

		protected:

			const FvVariables_Faces2d& thePhif_;

			const FvVariables_Elements2d& thePhi_;

		public:

			virtual Standard_Real Interpolate(const FvEntity_Face2d& theFace, const Standard_Boolean theBoundary = Standard_True) const = 0;

		protected:

			FvInterpolation(const FvVariables_Faces2d& thePhif, const FvVariables_Elements2d& thePhi);

		};
	}
}

#endif // !_FvInterpolation_Header
