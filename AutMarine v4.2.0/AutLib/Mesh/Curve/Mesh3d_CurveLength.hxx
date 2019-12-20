#pragma once
#ifndef _Mesh3d_CurveLength_Header
#define _Mesh3d_CurveLength_Header

#include <Standard_Real.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CurveIntegrand;

		class Mesh3d_CurveLength
		{

		public:

			static Standard_Real Length(const Mesh3d_CurveIntegrand& Integrand, const Standard_Real Tolerance);

			static Standard_Real Length(const Mesh3d_CurveIntegrand& Integrand, const Standard_Real Lower, const Standard_Real Upper, const Standard_Real Tolerance);
		};
	}
}

#endif // !_Mesh3d_CurveLength_Header
