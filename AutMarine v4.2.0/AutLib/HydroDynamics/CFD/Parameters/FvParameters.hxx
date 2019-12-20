#pragma once
#ifndef _FvParameters_Header
#define _FvParameters_Header

#include <FvSolverConfig.hxx>
#include <FvParameters_TimeConfig.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvParameters
		{

		private:

			const FvSolverConfig& theVelocity_;

			const FvSolverConfig& thePressure_;

			const FvParameters_TimeConfig& theTime_;

		public:

			FvParameters(const FvParameters_TimeConfig& theTime, const FvSolverConfig& theVelocitySolver, const FvSolverConfig& thePressureSolver);

			const FvSolverConfig& Velocity() const;

			const FvSolverConfig& Pressure() const;

			const FvParameters_TimeConfig& Time() const;
		};
	}
}

#include <FvParametersI.hxx>

#endif // !_FvParameters_Header
