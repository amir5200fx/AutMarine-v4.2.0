#pragma once
#ifndef _FvPressure2d_Header
#define _FvPressure2d_Header

#include <FvNavierStokes.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvPressure2d : public FvNavierStokes
		{

		private:


		public:

			FvPressure2d(const FvMesh2d& theMesh, const FvParameters& theParameters, const FvBC& theBoundaryCondition, const FvVariables2d& theVariables);

			void CalcPressure();
		};
	}
}

#endif // !_FvPressure_Header
