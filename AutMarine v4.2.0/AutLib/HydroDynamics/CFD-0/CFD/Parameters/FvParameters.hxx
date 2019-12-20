#pragma once
#ifndef _FvParameters_Header
#define _FvParameters_Header

#include <FvParameters_SolverConfig.hxx>
#include <FvParameters_TimeConfig.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvParameters
		{

		private:

			FvParameters_SolverConfig theVelocity_;

			FvParameters_SolverConfig thePressure_;

			const FvParameters_TimeConfig& theTime_;

		public:

			FvParameters(const FvParameters_TimeConfig& theTime);

			FvParameters_SolverConfig& Velocity();

			FvParameters_SolverConfig& Pressure();

			const FvParameters_SolverConfig& Velocity() const;

			const FvParameters_SolverConfig& Pressure() const;

			const FvParameters_TimeConfig& Time() const;
		};
	}
}

#include <FvParametersI.hxx>

#endif // !_FvParameters_Header
