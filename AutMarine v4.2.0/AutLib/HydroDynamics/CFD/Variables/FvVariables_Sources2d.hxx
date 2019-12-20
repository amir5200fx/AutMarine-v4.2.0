#pragma once
#ifndef _FvVariables_Sources2d_Header
#define _FvVariables_Sources2d_Header

#include <Global_Macros.hxx>
#include <FvVector.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvVariables_Sources2d
		{

		private:

			FvVector& theBu_;
			FvVector& theBv_;

		public:

			FvVariables_Sources2d(FvVector& theU_Component, FvVector& theV_Component);

			const FvVector& U_Component() const;

			const FvVector& V_Component() const;

			FvVector& U_Component();

			FvVector& V_Component();
		};
	}
}

#include <FvVariables_Sources2dI.hxx>

#endif // !_FvVariables_Sources2d_Header
