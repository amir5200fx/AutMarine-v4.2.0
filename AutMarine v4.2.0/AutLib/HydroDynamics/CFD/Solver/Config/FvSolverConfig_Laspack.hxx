#pragma once
#ifndef _FvSolverConfig_Laspack_Header
#define _FvSolverConfig_Laspack_Header

#include <FvSolverConfig.hxx>
#include <FvSolverConfig_LaspackPrecondition.hxx>
#include <FvSolverConfig_LaspackSolverInfo.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvSolverConfig_Laspack : public FvSolverConfig
		{

		private:

			FvSolverConfig_LaspackPrecondition thePrecondition_;

			FvSolverConfig_LaspackSolverInfo theSolver_;

			Scalar theOmega_;

		public:

			virtual ~FvSolverConfig_Laspack();

			void SetPrecondition(const FvSolverConfig_LaspackPrecondition thePrecondition);

			void SetSolver(const FvSolverConfig_LaspackSolverInfo theSolver);

			void SetOmega(const Scalar theOmega);

			FvSolverConfig_LaspackPrecondition Precondition() const;

			FvSolverConfig_LaspackSolverInfo Solver() const;

			Scalar Omega() const;

		protected:

			FvSolverConfig_Laspack(const Label theMaxIters, const Scalar theMaxRes, const FvSolverConfig_LaspackPrecondition thePrecondition, const FvSolverConfig_LaspackSolverInfo theSolver);
		};
	}
}

#include <FvSolverConfig_LaspackI.hxx>

#endif // !_FvSolverConfig_Laspack_Header
