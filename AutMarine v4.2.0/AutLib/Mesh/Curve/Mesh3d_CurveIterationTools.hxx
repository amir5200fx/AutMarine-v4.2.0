#pragma once
#ifndef _Mesh3d_CurveIterationTools_Header
#define _Mesh3d_CurveIterationTools_Header

#include <Standard_Real.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CurveIntegrand;

		class Mesh3d_CurveIterationTools
		{

		public:

			// Throw an exception
			static Standard_Real Iteration(const Standard_Real Start, const Standard_Real Guess, const Standard_Real Step, const Mesh3d_CurveIntegrand& CurveIntegrand);
		};
	}
}

#endif // !_Mesh3d_CurveIterationTools_Header
