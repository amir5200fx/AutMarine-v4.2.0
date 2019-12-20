#pragma once
#ifndef _FvParameters_SolverConfigInfo_Header
#define _FvParameters_SolverConfigInfo_Header

#include <Standard_TypeDef.hxx>
#include <FvParameters_Precondition.hxx>
#include <FvParameters_Solver.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvParameters_SolverConfigInfo
		{

		public:

			static Standard_Integer VelocityMaxNbIterations();

			static Standard_Integer PressureMaxNbIterations();

			static Standard_Real VelocityMaxResidual();

			static Standard_Real PressureMaxResidual();

			static FvParameters_Precondition VelocityPrecondition();

			static FvParameters_Precondition PressurePrecondition();

			static FvParameters_Solver VelocitySolver();

			static FvParameters_Solver PressureSolver();
		};
	}
}

#endif // !_FvParameters_SolverConfigInfo_Header
