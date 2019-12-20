#pragma once
#ifndef _Mesh2d_CurveIntegrandTools_Header
#define _Mesh2d_CurveIntegrandTools_Header

#include <Mesh2d_CurveIntegrand.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		class Mesh2d_CurveIntegrandTools
		{

		public:

			static Standard_Real Integrand(const Standard_Real X, const Mesh2d_CurveIntegrand& CurveIntegrand);
		};
	}
}


#endif // !_Mesh2d_CurveIntegrandTools_Header
