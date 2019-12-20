#pragma once
#ifndef _FvMaterial_Density_Header
#define _FvMaterial_Density_Header

#include <FvPrimitives_Scalar.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvMaterial_Density
		{

		private:

			Scalar theValue_;

		public:

			FvMaterial_Density();

			FvMaterial_Density(const Scalar theValue);

			void SteValue(const Scalar theValue);

			Scalar Value() const;
		};
	}
}

#include <FvMaterial_DensityI.hxx>

#endif // !_FvMaterial_Density_Header
