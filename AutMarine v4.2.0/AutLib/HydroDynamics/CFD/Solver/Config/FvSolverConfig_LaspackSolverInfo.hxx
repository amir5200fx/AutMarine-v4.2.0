#pragma once
#ifndef _FvSolverConfig_LaspackSolverInfo_Header
#define _FvSolverConfig_LaspackSolverInfo_Header

namespace AutLib
{
	namespace FvLib
	{

		enum FvSolverConfig_LaspackSolverInfo
		{

			FvSolverConfig_LaspackSolverInfo_JACOBI = 0,
			FvSolverConfig_LaspackSolverInfo_SOR,
			FvSolverConfig_LaspackSolverInfo_QMR,
			FvSolverConfig_LaspackSolverInfo_GMRES,
			FvSolverConfig_LaspackSolverInfo_CG,
			FvSolverConfig_LaspackSolverInfo_CGN,
			FvSolverConfig_LaspackSolverInfo_CGS,
			FvSolverConfig_LaspackSolverInfo_BICG,
			FvSolverConfig_LaspackSolverInfo_BICGS
		};
	}
}

#endif // !_FvSolverConfig_SolverInfo_Header
