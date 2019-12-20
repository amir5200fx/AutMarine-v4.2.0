#pragma once
#ifndef _FvMaterial_Custom_Header
#define _FvMaterial_Custom_Header

#include <FvMaterial.hxx>
#include <Standard_Stream.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvMaterial_Viscosity;
		class FvMaterial_Density;

		class FvMaterial_Custom : public FvMaterial
		{

		private:


		public:

			FvMaterial_Custom(const FvMaterial_Density& theDensity, const FvMaterial_Viscosity& theViscosity);

			void ImportFrom(fstream& File);
		};
	}
}

#endif // !_FvMaterial_Custom_Header
