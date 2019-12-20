#pragma once
#ifndef _FvMaterial_Info_Header
#define _FvMaterial_Info_Header

namespace AutLib
{
	namespace FvLib
	{

		class FvMaterial_Viscosity;
		class FvMaterial_Density;

		class FvMaterial_Info
		{

		public:

			static FvMaterial_Density Density_Water();

			static FvMaterial_Density Density_Air();

			static FvMaterial_Viscosity Viscosity_Water();

			static FvMaterial_Viscosity Viscosity_Air();
		};
	}
}

#endif // !_FvMaterial_Info_Header
