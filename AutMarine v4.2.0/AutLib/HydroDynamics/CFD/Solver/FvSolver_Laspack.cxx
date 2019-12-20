#include <FvSolver_Laspack.hxx>

#include <Global_Memory.hxx>
#include <Global_Debug.hxx>
#include <Time.hxx>
#include <FvSolverConfig_Laspack.hxx>
#include <laspack.h>

using namespace AutLib;

AutLib::FvLib::FvSolver_Laspack::FvSolver_Laspack
(
	const FvMatrix & theMatrix,
	const FvSolverConfig & theParameters
)
	: FvSolver(theMatrix, theParameters)
{
}

void AutLib::FvLib::FvSolver_Laspack::Solve
(
	const FvVector & theRHS,
	FvVector & theX
) const
{
	Global_Handle(FvSolverConfig_Laspack) Config = Global_DownCast(FvSolverConfig_Laspack, (Global_Handle(FvSolver))&FvSolver::Parameters());
	if (NOT Config)
	{
		THROW_STANDARD_EXCEPTION("No LASPACK Config solver has been found!");
	}

	PrecondProcType PreconditionType;
	switch (Config->Precondition())
	{
	case FvSolverConfig_LaspackPrecondition_NONE: {PreconditionType = NULL; break; }
	case FvSolverConfig_LaspackPrecondition_JACOBI: {PreconditionType = JacobiPrecond; break; }
	case FvSolverConfig_LaspackPrecondition_SOR: {PreconditionType = SSORPrecond; break; }
	case FvSolverConfig_LaspackPrecondition_ILU: {PreconditionType = ILUPrecond; break; }
	default: {THROW_STANDARD_EXCEPTION("Bad Precondition Type"); }
	}

	Scalar FirstTime = getCPUTime();

	switch (Config->Solver())
	{
	case FvSolverConfig_LaspackSolverInfo_JACOBI:

		JacobiIter
		(
			(QMatrix*)&FvSolver::Matrix(), 
			(Vector*)&theX,
			(Vector*)&theRHS,
			Config->MaxIterations(),
			PreconditionType,
			Config->Omega()
		);

		Config->SetNbIterations(GetLastNoIter());
		Config->SetResidual(GetLastAccuracy());

		break;

	case FvSolverConfig_LaspackSolverInfo_SOR:

		SSORIter
		(
			(QMatrix*)&FvSolver::Matrix(),
			(Vector*)&theX,
			(Vector*)&theRHS,
			Config->MaxIterations(),
			PreconditionType,
			Config->Omega()
		);

		Config->SetNbIterations(GetLastNoIter());
		Config->SetResidual(GetLastAccuracy());

		break;

	case FvSolverConfig_LaspackSolverInfo_QMR:

		QMRIter
		(
			(QMatrix*)&FvSolver::Matrix(), 
			(Vector*)&theX, 
			(Vector*)&theRHS, 
			Config->MaxIterations(), 
			PreconditionType,
			Config->Omega()
		);

		Config->SetNbIterations(GetLastNoIter());
		Config->SetResidual(GetLastAccuracy());

		break;

	case FvSolverConfig_LaspackSolverInfo_GMRES:

		GMRESIter
		(
			(QMatrix*)&FvSolver::Matrix(), 
			(Vector*)&theX, 
			(Vector*)&theRHS, 
			Config->MaxIterations(), 
			PreconditionType, 
			Config->Omega()
		);

		Config->SetNbIterations(GetLastNoIter());
		Config->SetResidual(GetLastAccuracy());

		break;

	case FvSolverConfig_LaspackSolverInfo_CGS:

		CGSIter
		(
			(QMatrix*)&FvSolver::Matrix(), 
			(Vector*)&theX, 
			(Vector*)&theRHS, 
			Config->MaxIterations(), 
			PreconditionType, 
			Config->Omega()
		);

		Config->SetNbIterations(GetLastNoIter());
		Config->SetResidual(GetLastAccuracy());

		break;

	case FvSolverConfig_LaspackSolverInfo_CGN:

		CGNIter
		(
			(QMatrix*)&FvSolver::Matrix(),
			(Vector*)&theX,
			(Vector*)&theRHS,
			Config->MaxIterations(),
			PreconditionType,
			Config->Omega()
		);

		Config->SetNbIterations(GetLastNoIter());
		Config->SetResidual(GetLastAccuracy());

		break;

	case FvSolverConfig_LaspackSolverInfo_CG:

		CGIter
		(
			(QMatrix*)&FvSolver::Matrix(),
			(Vector*)&theX,
			(Vector*)&theRHS,
			Config->MaxIterations(),
			PreconditionType,
			Config->Omega()
		);

		Config->SetNbIterations(GetLastNoIter());
		Config->SetResidual(GetLastAccuracy());

		break;

	case FvSolverConfig_LaspackSolverInfo_BICGS:

		BiCGSTABIter
		(
			(QMatrix*)&FvSolver::Matrix(),
			(Vector*)&theX,
			(Vector*)&theRHS,
			Config->MaxIterations(),
			PreconditionType,
			Config->Omega()
		);

		Config->SetNbIterations(GetLastNoIter());
		Config->SetResidual(GetLastAccuracy());

		break;


	case FvSolverConfig_LaspackSolverInfo_BICG:

		BiCGIter
		(
			(QMatrix*)&FvSolver::Matrix(),
			(Vector*)&theX,
			(Vector*)&theRHS,
			Config->MaxIterations(),
			PreconditionType,
			Config->Omega()
		);

		Config->SetNbIterations(GetLastNoIter());
		Config->SetResidual(GetLastAccuracy());

		break;
	}

	Scalar LastTime = getCPUTime();

	Config->SetTime(LastTime - FirstTime);
}