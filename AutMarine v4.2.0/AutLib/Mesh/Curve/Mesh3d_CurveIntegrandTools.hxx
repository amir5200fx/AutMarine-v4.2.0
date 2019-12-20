#pragma once
#ifndef _Mesh3d_CurveIntegrandTools_Header
#define _Mesh3d_CurveIntegrandTools_Header

#include <Mesh3d_CurveIntegrand.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CurveIntegrandTools
		{

		public:

			static Standard_Real Integrand(const Standard_Real X, const Mesh3d_CurveIntegrand& CurveIntegrand);
		};
	}
}

#endif // !_Mesh3d_CurveIntegrandTools_Header