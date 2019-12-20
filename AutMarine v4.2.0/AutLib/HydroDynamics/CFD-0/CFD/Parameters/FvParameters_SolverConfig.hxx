#pragma once
#ifndef _FvParameters_SolverConfig_Header
#define _FvParameters_SolverConfig_Header

#include <Standard_TypeDef.hxx>
#include <FvParameters_Precondition.hxx>
#include <FvParameters_Solver.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvParameters_SolverConfig
		{

		private:

			FvParameters_Solver theSolver_;

			FvParameters_Precondition thePrecondition_;

			Standard_Real theTime_;

			Standard_Integer theMaxIters_;
			Standard_Integer theIters_;

			Standard_Real theMaxRes_;
			Standard_Real theRes_;

		public:

			FvParameters_SolverConfig();

			void SetSolver(const FvParameters_Solver theSolver);

			void SetPrecondition(const FvParameters_Precondition thePrecondition);

			void SetTime(const Standard_Real theTime);

			void SetMaxIterations(const Standard_Integer theMaxIters);

			void SetNbIterations(const Standard_Integer theNbIterations);

			void SetMaxResidual(const Standard_Real theValue);

			void SetResidual(const Standard_Real theValue);

			FvParameters_Solver Solver() const;

			FvParameters_Precondition Precondition() const;

			Standard_Real Time() const;

			Standard_Integer MaxIterations() const;

			Standard_Integer NbIterations() const;

			Standard_Real MaxResidual() const;

			Standard_Real Residual() const;
		};
	}
}

#include <FvParameters_SolverConfigI.hxx>

#endif // !_FvParameters_SolverConfig_Header
