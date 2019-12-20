#pragma once
#ifndef _Mesh2d_CurveLength_Header
#define _Mesh2d_CurveLength_Header

#include <Standard_Real.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		
		class Mesh2d_CurveIntegrand;

		class Mesh2d_CurveLength
		{

		public:

			static Standard_Real Length(const Mesh2d_CurveIntegrand& Integrand, const Standard_Real Tolerance);

			static Standard_Real Length(const Mesh2d_CurveIntegrand& Integrand, const Standard_Real Lower, const Standard_Real Upper, const Standard_Real Tolerance);
		};
	}
}

#endif // !_Mesh2d_CurveLength_Header
