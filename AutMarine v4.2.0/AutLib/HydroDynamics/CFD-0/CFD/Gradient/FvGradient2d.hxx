#pragma once
#ifndef _FvGradient2d_Header
#define _FvGradient2d_Header

#include <FvVariables_Faces2d.hxx>
#include <FvVariables_Elements2d.hxx>
#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace FvLib
	{
		
		class FvMesh2d;
		class FvEntity_Element2d;
		class FvInterpolation;

		class FvGradient2d
		{

		private:

			const FvInterpolation& theInterpolation_;

		public:

			FvGradient2d(const FvInterpolation& theInterpolation);

			Geom_Pnt2d CalcGradient(const FvEntity_Element2d& theElement, const Standard_Boolean Boundary = Standard_True) const;
		};
	}
}

#endif // !_FvGradient2d_Header
