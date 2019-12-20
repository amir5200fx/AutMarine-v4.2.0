#include <FvSolver.hxx>

AutLib::FvLib::FvSolver::FvSolver
(
	const FvMatrix & theMatrix, 
	const FvSolverConfig & theParameters
)
	: theMatrix_(theMatrix)
	, theParameters_(theParameters)
{
}