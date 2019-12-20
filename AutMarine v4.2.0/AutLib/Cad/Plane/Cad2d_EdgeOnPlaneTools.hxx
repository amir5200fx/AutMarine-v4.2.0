#pragma once
#ifndef _Cad2d_EdgeOnPlaneTools_Header
#define _Cad2d_EdgeOnPlaneTools_Header

#include <Cad2d_EdgeOnPlane.hxx>
#include <TColCad2d_HAry1dOfCurveOnPlane.hxx>
#include <TColCad2d_HAry1dOfEdgeOnPlane.hxx>
#include <TColCad2d_HAry1dOfPointOnPlane.hxx>
#include <TColStd_Ary1dOfReal.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_EdgeOnPlaneTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Cad2d_EdgeOnPlane) const& theEdge1, Global_Handle(Cad2d_EdgeOnPlane) const& theEdge2);

			static TColCad2d_HAry1dOfCurveOnPlane RetrieveCurvesFrom(const TColCad2d_HAry1dOfEdgeOnPlane& theEdges);

			static TColCad2d_HAry1dOfPointOnPlane RetrievePointsFrom(const TColCad2d_HAry1dOfEdgeOnPlane& theEdges);

			static TColCad2d_HAry1dOfEdgeOnPlane MakeEdges(const TColCad2d_HAry1dOfCurveOnPlane& theCurves, const Standard_Real theTolerance);

			static TColCad2d_HAry1dOfEdgeOnPlane SubdivideEdge(const Cad2d_EdgeOnPlane& theEdge, const TColStd_Ary1dOfReal& theParameters, const Standard_Real theTolerance);
		};
	}
}

#include <Cad2d_EdgeOnPlaneToolsI.hxx>

#endif // !_Cad2d_EdgeOnPlaneTools_Header
