#pragma once
#ifndef _Mesh3d_CurveIntegrand_Header
#define _Mesh3d_CurveIntegrand_Header

#include <Standard_Real.hxx>
#include <Global_Debug.hxx>
#include <Global_Memory.hxx>

class Geom_Curve;

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_SizeMap;

		class Mesh3d_CurveIntegrand
		{

		private:

			const Global_Handle(Mesh3d_SizeMap) theMap_;

			const Global_Handle(Geom_Curve) theCurve_;

			Standard_Real theFirst_;
			Standard_Real theLast_;

		public:

			Mesh3d_CurveIntegrand(const Global_Handle(Mesh3d_SizeMap) Map, const Global_Handle(Geom_Curve) Curve, const Standard_Real First, const Standard_Real Last);

			const Global_Handle(Mesh3d_SizeMap) Map() const;

			const Global_Handle(Geom_Curve) Curve() const;

			Standard_Real FirstParameter() const;

			Standard_Real LastParameter() const;

		};
	}
}

#include <Mesh3d_CurveIntegrandI.hxx>

#endif // !_Mesh3d_CurveIntegrand_Header
