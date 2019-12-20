#pragma once
#ifndef _FvVariables_FluxVelocity_Header
#define _FvVariables_FluxVelocity_Header

#include <Global_Macros.hxx>
#include <FvVector.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvVariables_FluxVelocity
		{

		private:

			FvVector& theU_;

		public:

			FvVariables_FluxVelocity(FvVector& theFluxVelocity);

			FvVector& Velocity();

			const FvVector& Velocity() const;
		};
	}
}

#include <FvVariables_FluxVelocityI.hxx>

#endif // !_FvVariables_FluxVelocity_Header
