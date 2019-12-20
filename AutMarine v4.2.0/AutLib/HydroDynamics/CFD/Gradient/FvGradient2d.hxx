#pragma once
#ifndef _FvGradient2d_Header
#define _FvGradient2d_Header

#include <FvPrimitives_Vec2.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvInterpolation2d;
		class FvEntity_Element2d;

		class FvGradient2d
		{

		private:

			const FvInterpolation2d& theInterpolation_;

		public:

			FvGradient2d(const FvInterpolation2d& theInterpolation);

			Vec2 CalcGradient(const FvEntity_Element2d& theElement, const Standard_Boolean Boundary = Standard_True) const;
		};
	}
}

#include <FvGradient2dI.hxx>

#endif // !_FvGradient2d_Header
