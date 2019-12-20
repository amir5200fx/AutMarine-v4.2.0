#pragma once
#ifndef _FvVariables_Primitives2d_Header
#define _FvVariables_Primitives2d_Header

#include <Global_Macros.hxx>
#include <Global_Memory.hxx>
#include <FvVector.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvVariables_Primitives2d
		{

		private:

			FvVector& theU_;
			FvVector& theV_;
			FvVector& theP_;

		public:

			FvVariables_Primitives2d(FvVector& theU_Component, FvVector& theV_Component, FvVector& thePressure);

			const FvVector& U_Component() const;

			const FvVector& V_Component() const;

			const FvVector& Pressure() const;

			FvVector& U_Component();

			FvVector& V_Component();

			FvVector& Pressure();
		};
	}
}

#include <FvVariables_Primitives2dI.hxx>

#endif // !_FvVariables_Primitives2d_Header

