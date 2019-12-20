#pragma once
#ifndef _Mesh_VariationRate_Header
#define _Mesh_VariationRate_Header

#include <Standard_Real.hxx>
#include <Mesh_VariationRateInfo.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh_VariationRate
		{

		public:

			static Standard_Real VeryLowrate();

			static Standard_Real Lowrate();

			static Standard_Real Moderate();

			static Standard_Real Highrate();

			static Standard_Real Rate(const Mesh_VariationRateInfo Info);
		};
	}
}

#endif // !_Mesh_VariationRate_Header
