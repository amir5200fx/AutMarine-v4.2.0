#pragma once
#ifndef _FvSolverConfig_LaspackPressure_Header
#define _FvSolverConfig_LaspackPressure_Header

#include <FvSolverConfig_Laspack.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvSolverConfig_LaspackPressure : public FvSolverConfig_Laspack
		{

		private:


		public:

			FvSolverConfig_LaspackPressure();

			virtual ~FvSolverConfig_LaspackPressure();
		};
	}
}

#endif // !_FvSolverConfig_LaspackPressure_Header
