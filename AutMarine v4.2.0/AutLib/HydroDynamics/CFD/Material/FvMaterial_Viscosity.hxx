#pragma once
#ifndef _FvMaterial_Viscosity_Header
#define _FvMaterial_Viscosity_Header

#include <FvPrimitives_Scalar.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvMaterial_Viscosity
		{

		private:

			Scalar theValue_;

		public:

			FvMaterial_Viscosity();

			FvMaterial_Viscosity(const Scalar theValue);

			Scalar Value() const;

			void SetValue(const Scalar theValue);
		};
	}
}

#include <FvMaterial_ViscosityI.hxx>

#endif // !_FvMaterial_Viscosity_Header
