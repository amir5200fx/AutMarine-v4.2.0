#pragma once
#ifndef _Cad3d_EdgeOnPlaneTools_Header
#define _Cad3d_EdgeOnPlaneTools_Header

#include <Cad3d_EdgeOnPlane.hxx>
#include <TColCad3d_HAry1dOfEdgeOnPlane.hxx>
#include <TColCad3d_HAry1dOfEdgeOnSolid.hxx>
#include <TColCad3d_HAry1dOfCurveOnPlane.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Box2d;
	}

	namespace CadLib
	{

		class Cad3d_EdgeOnPlaneTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Cad3d_EdgeOnPlane) const& theEdge1, Global_Handle(Cad3d_EdgeOnPlane) const& theEdge2);

			static TColCad3d_HAry1dOfCurveOnPlane RetrieveCurvesFrom(const TColCad3d_HAry1dOfEdgeOnPlane& theEdges);

			static TColCad3d_HAry1dOfPointOnPlane RetrievePointsFrom(const TColCad3d_HAry1dOfEdgeOnPlane& theEdges);

			static TColCad3d_HAry1dOfEdgeOnPlane MakeEdges(const TColCad3d_HAry1dOfCurveOnPlane& theCurves, const Standard_Real theTolerance);
		};
	}
}

#include <Cad3d_EdgeOnPlaneToolsI.hxx>

#endif // !_Cad3d_EdgeOnPlaneTools_Header
