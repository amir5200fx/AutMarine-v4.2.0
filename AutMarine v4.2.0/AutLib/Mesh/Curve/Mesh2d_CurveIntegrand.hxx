#pragma once
#ifndef _Mesh2d_CurveIntegrand_Header
#define _Mesh2d_CurveIntegrand_Header

#include <Standard_Real.hxx>
#include <Global_Debug.hxx>
#include <Global_Memory.hxx>

class Geom2d_Curve;

namespace AutLib
{
	namespace MeshLib
	{
		class Mesh2d_SizeMap;

		class Mesh2d_CurveIntegrand
		{

		private:

			const Global_Handle(Mesh2d_SizeMap) theMap_;

			const Global_Handle(Geom2d_Curve) theCurve_;

			Standard_Real theFirst_;
			Standard_Real theLast_;

		public:

			Mesh2d_CurveIntegrand();

			Mesh2d_CurveIntegrand(const Global_Handle(Mesh2d_SizeMap) Map, const Global_Handle(Geom2d_Curve) Curve, const Standard_Real First, const Standard_Real Last);

			const Global_Handle(Mesh2d_SizeMap) Map() const;

			const Global_Handle(Geom2d_Curve) Curve() const;

			Standard_Real FirstParameter() const;

			Standard_Real LastParameter() const;

			void SetFirstParameter(const Standard_Real Value);

			void SetLastParameter(const Standard_Real Value);

			void SetMap(const Global_Handle(Mesh2d_SizeMap) Map);

			void SetCurve(const Global_Handle(Geom2d_Curve) Curve);

		};
	}
}

#include <Mesh2d_CurveIntegrandI.hxx>

#endif // !_Mesh2d_CurveIntegrand_header
