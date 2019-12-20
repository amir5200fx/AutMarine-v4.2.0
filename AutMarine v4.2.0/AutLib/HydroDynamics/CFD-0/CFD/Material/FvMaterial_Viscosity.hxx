#pragma once
#ifndef _FvMaterial_Viscosity_Header
#define _FvMaterial_Viscosity_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvMaterial_Viscosity
		{

		private:

			Standard_Real theValue_;

		public:

			FvMaterial_Viscosity();

			FvMaterial_Viscosity(const Standard_Real theValue);

			Standard_Real Value() const;

			void SetValue(const Standard_Real theValue);
		};
	}
}

#include <FvMaterial_ViscosityI.hxx>

#endif // !_FvMaterial_Viscosity_Header
