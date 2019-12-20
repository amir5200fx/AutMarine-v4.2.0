#pragma once
#ifndef _FvSolverConfig_LaspackSolverSetupInfo_Header
#define _FvSolverConfig_LaspackSolverSetupInfo_Header

#include <FvPrimitives_Label.hxx>
#include <FvPrimitives_Scalar.hxx>
#include <FvSolverConfig_LaspackPrecondition.hxx>
#include <FvSolverConfig_LaspackSolverInfo.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvSolverConfig_LaspackSolverSetupInfo
		{

		public:

			static Label VelocityMaxNbIterations();

			static Label PressureMaxNbIterations();

			static Scalar VelocityMaxResidual();

			static Scalar PressureMaxResidual();

			static Scalar Omeag();

			static FvSolverConfig_LaspackPrecondition VelocityPrecondition();

			static FvSolverConfig_LaspackPrecondition PressurePrecondition();

			static FvSolverConfig_LaspackSolverInfo VelocitySolver();

			static FvSolverConfig_LaspackSolverInfo PressureSolver();

		};
	}
}

#endif // !_FvSolverConfig_LaspackSolverSetupInfo_Header
