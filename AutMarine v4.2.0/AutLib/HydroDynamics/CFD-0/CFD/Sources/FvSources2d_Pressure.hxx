#pragma once
#ifndef _FvSources2d_Pressure_Header
#define _FvSources2d_Pressure_Header

#include <FvSources2d.hxx>
#include <FvGradient2d_Pressure.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvSources2d_Pressure : public FvSources2d
		{

		private:

			const FvGradient2d& theGradient_;

			Standard_Boolean theBoundary_;

		public:

			FvSources2d_Pressure(const FvGradient2d_Pressure& theGradient);

			virtual Geom_Pnt2d Value(const FvEntity_Element2d& theElement) const;
		};
	}
}

#include <FvSources2d_PressureI.hxx>

#endif // !_FvSources2d_Pressure_Header
