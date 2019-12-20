#pragma once
#ifndef _FvMaterial_Density_Header
#define _FvMaterial_Density_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvMaterial_Density
		{

		private:

			Standard_Real theValue_;

		public:

			FvMaterial_Density();

			FvMaterial_Density(const Standard_Real theValue);

			void SteValue(const Standard_Real theValue);

			Standard_Real Value() const;
		};
	}
}

#include <FvMaterial_DensityI.hxx>

#endif // !_FvMaterial_Density_Header
