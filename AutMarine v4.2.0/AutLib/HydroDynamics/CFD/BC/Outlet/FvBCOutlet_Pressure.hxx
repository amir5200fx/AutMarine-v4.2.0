#pragma once
#ifndef _FvBCOutlet_Pressure_Header
#define _FvBCOutlet_Pressure_Header

#include <FvBC_Boundary.hxx>
#include <FvBCSpecification_Pressure.hxx>

namespace AutLib
{
	namespace FvLib
	{
		
		class FvBCOutlet_Pressure : public FvBC_Boundary
		{

		private:

			const FvBCSpecification_Pressure& thePressure_;

		public:

			FvBCOutlet_Pressure(const FvBCSpecification_Pressure& thePressure);

			virtual ~FvBCOutlet_Pressure();

			const FvBCSpecification_Pressure& Pressure() const;
		};
	}
}

#include <FvBCOutlet_PressureI.hxx>

#endif // !_FvBCOutlet_Pressure_Header
