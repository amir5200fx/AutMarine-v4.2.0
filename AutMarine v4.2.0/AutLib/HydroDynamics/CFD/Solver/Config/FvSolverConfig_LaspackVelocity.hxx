#pragma once
#ifndef _FvSolverConfig_LaspackVelocity_Header
#define _FvSolverConfig_LaspackVelocity_Header

#include <FvSolverConfig_Laspack.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvSolverConfig_LaspackVelocity : public FvSolverConfig_Laspack
		{

		private:


		public:

			FvSolverConfig_LaspackVelocity();

			virtual ~FvSolverConfig_LaspackVelocity();
		};
	}
}

#endif // !_FvSolverConfig_LaspackVelocity_Header
