#pragma once
#ifndef _FvSolverConfig_LaspackPrecondition_Header
#define _FvSolverConfig_LaspackPrecondition_Header

namespace AutLib
{
	namespace FvLib
	{

		enum FvSolverConfig_LaspackPrecondition
		{
			FvSolverConfig_LaspackPrecondition_NONE = 0,
			FvSolverConfig_LaspackPrecondition_JACOBI,
			FvSolverConfig_LaspackPrecondition_SOR,
			FvSolverConfig_LaspackPrecondition_ILU
		};
	}
}

#endif // !_FvSolverConfig_LaspackPrecondition_Header
