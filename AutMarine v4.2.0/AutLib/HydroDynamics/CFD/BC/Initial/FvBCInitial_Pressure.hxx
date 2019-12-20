#pragma once
#ifndef _FvBCInitial_Pressure_Header
#define _FvBCInitial_Pressure_Header

#include <FvBC_Boundary.hxx>
#include <FvBCSpecification_Pressure.hxx>

namespace AutLib
{
	namespace FvLib
	{
		
		class FvBCInitial_Pressure : public FvBC_Boundary
		{

		private:

			const FvBCSpecification_Pressure& thePressure_;

		public:

			FvBCInitial_Pressure(const FvBCSpecification_Pressure& thePressure);

			virtual ~FvBCInitial_Pressure();

			const FvBCSpecification_Pressure& Pressure() const;
		};
	}
}

#include <FvBCInitial_PressureI.hxx>

#endif // !_FvBCInitial_Pressure_Header
