#pragma once
#ifndef _FvSolver_Header
#define _FvSolver_Header

#include <FvVector.hxx>
#include <FvMatrix.hxx>
#include <FvSolverConfig.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvSolver
		{

		private:

			const FvMatrix& theMatrix_;

			const FvSolverConfig& theParameters_;

		public:

			virtual void Solve(const FvVector& theRHS, FvVector& theX) const = 0;

			const FvMatrix& Matrix() const;

			const FvSolverConfig& Parameters() const;

		protected:

			FvSolver(const FvMatrix& theMatrix, const FvSolverConfig& theParameters);

		};
	}
}

#include <FvSolverI.hxx>

#endif // !_FvSolver_Header
