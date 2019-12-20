#pragma once
#ifndef _FvSolver_Laspack_Header
#define _FvSolver_Laspack_Header

#include <FvSolver.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvSolver_Laspack : public FvSolver
		{

		private:


		public:

			FvSolver_Laspack(const FvMatrix& theMatrix, const FvSolverConfig& theParameters);

			virtual void Solve(const FvVector& theRHS, FvVector& theX) const;
		};
	}
}

#endif // !_FvSolver_Laspack_Header
