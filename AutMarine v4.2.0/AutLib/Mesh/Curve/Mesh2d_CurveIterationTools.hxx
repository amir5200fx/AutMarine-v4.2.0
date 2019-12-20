#pragma once
#ifndef _Mesh2d_CurveIterationTools_Header
#define _Mesh2d_CurveIterationTools_Header

#include <Mesh2d_CurveIteration.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		class Mesh2d_CurveIterationTools
		{

		public:

			// Throw an exception
			static Standard_Real Iteration(const Standard_Real Start, const Standard_Real Guess, const Standard_Real Step, const Mesh2d_CurveIntegrand& CurveIntegrand);
		};
	}
}

#endif // !_Mesh2d_CurveIterationTools_Header
