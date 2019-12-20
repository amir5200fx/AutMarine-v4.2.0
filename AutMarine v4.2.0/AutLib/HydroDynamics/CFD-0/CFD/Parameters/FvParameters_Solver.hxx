#pragma once
#ifndef _FvParameters_Solver_Header
#define _FvParameters_Solver_Header

namespace AutLib
{
	namespace FvLib
	{

		enum FvParameters_Solver
		{

			FvParameters_Solver_JACOBI = 0,
			FvParameters_Solver_SOR,
			FvParameters_Solver_QMR,
			FvParameters_Solver_GRMES,
			FvParameters_Solver_CG,
			FvParameters_Solver_CGN,
			FvParameters_Solver_CGS,
			FvParameters_Solver_BICG,
			FvParameters_Solver_BICGS
		};
	}
}

#endif // !_FvParameters_Solver_Header
