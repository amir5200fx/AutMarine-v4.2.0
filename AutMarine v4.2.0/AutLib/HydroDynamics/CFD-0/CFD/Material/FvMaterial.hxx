#pragma once
#ifndef _FvMaterial_Header
#define _FvMaterial_Header

#include <FvMaterial_Density.hxx>
#include <FvMaterial_Viscosity.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvMaterial
		{

		private:

			FvMaterial_Density theDensity_;
			FvMaterial_Viscosity theViscosity_;

		public:

			virtual ~FvMaterial();

			FvMaterial_Density& Density();

			FvMaterial_Viscosity& Viscosity();

			const FvMaterial_Density& Density() const;

			const FvMaterial_Viscosity& Viscosity() const;

		protected:

			FvMaterial();

			FvMaterial(const FvMaterial_Density& theDensity, const FvMaterial_Viscosity& theViscosity);

		};
	}
}

#include <FvMaterialI.hxx>

#endif // !_FvMaterial_Header
