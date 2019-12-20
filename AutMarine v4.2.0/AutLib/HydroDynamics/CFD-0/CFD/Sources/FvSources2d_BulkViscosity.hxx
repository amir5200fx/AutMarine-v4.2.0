#pragma once
#ifndef _FvSources2d_BulkViscosity_Header
#define _FvSources2d_BulkViscosity_Header

#include <FvSources2d.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvMaterial_Viscosity;
		class FvVariables2d;
		class FvEntity_Face2d;
		class FvVariables_Faces2d;
		class FvVariables_Elements2d;

		class FvSources2d_BulkViscosity : public FvSources2d
		{

		private:

			const FvMaterial_Viscosity& theViscosity_;

			const FvVariables2d& theVariables_;

			Geom_Pnt2d(*Interpolation_)(const FvEntity_Face2d& theFace, const TColGeom_Ary1dOfPnt2d& thePhi);

		public:

			FvSources2d_BulkViscosity(const FvVariables2d& theVariables, const FvMaterial_Viscosity& theViscosity);

			void SetInterpolation(Geom_Pnt2d(*Interpolation)(const FvEntity_Face2d& theFace, const TColGeom_Ary1dOfPnt2d& thePhi));

			virtual Geom_Pnt2d Value(const FvEntity_Element2d& theElement) const;
		};
	}
}

#endif // !_FvSources2d_BulkViscosity_Header
