#include <FvParameters_SolverConfigInfo.hxx>

using namespace AutLib;
using namespace FvLib;

Standard_Integer AutLib::FvLib::FvParameters_SolverConfigInfo::VelocityMaxNbIterations()
{
	return (Standard_Integer)500;
}

Standard_Integer AutLib::FvLib::FvParameters_SolverConfigInfo::PressureMaxNbIterations()
{
	return (Standard_Integer)1500;
}

Standard_Real AutLib::FvLib::FvParameters_SolverConfigInfo::VelocityMaxResidual()
{
	return (Standard_Real)1.0E-8;
}

Standard_Real AutLib::FvLib::FvParameters_SolverConfigInfo::PressureMaxResidual()
{
	return (Standard_Real)1.0E-8;
}

FvParameters_Precondition AutLib::FvLib::FvParameters_SolverConfigInfo::VelocityPrecondition()
{
	return FvParameters_Precondition::FvParameters_Precondition_SOR;
}

FvParameters_Precondition AutLib::FvLib::FvParameters_SolverConfigInfo::PressurePrecondition()
{
	return FvParameters_Precondition::FvParameters_Precondition_JACOBI;
}

FvParameters_Solver AutLib::FvLib::FvParameters_SolverConfigInfo::VelocitySolver()
{
	return FvParameters_Solver::FvParameters_Solver_BICGS;
}

FvParameters_Solver AutLib::FvLib::FvParameters_SolverConfigInfo::PressureSolver()
{
	return FvParameters_Solver::FvParameters_Solver_CG;
}