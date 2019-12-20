#pragma once
#ifndef _FvSources2d_Unsteady_Header
#define _FvSources2d_Unsteady_Header

#include <FvSources2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvParameters_TimeConfig;
		class FvMaterial_Density;
		class FvVariables2d;

		class FvSources2d_Unsteady : public FvSources2d
		{

		private:

			const FvParameters_TimeConfig& theTime_;

			const FvMaterial_Density& theDensity_;

			const FvVariables2d& theVariables_;

		public:

			FvSources2d_Unsteady(const FvParameters_TimeConfig& theTime, const FvMaterial_Density& theDensity, const FvVariables2d& theVariables);

			virtual Geom_Pnt2d Value(const FvEntity_Element2d& theElement) const;
		};
	}
}

#endif // !_FvSources2d_Unsteady_Header
