#pragma once
#ifndef _Cad3d_CurveOnPlaneTools_Header
#define _Cad3d_CurveOnPlaneTools_Header

#include <Standard_Handle.hxx>
#include <TColCad3d_HAry1dOfCurveOnPlane.hxx>
#include <TColCad3d_HAry1dOfEdgeOnSolid.hxx>

class Geom_Surface;
class TopoDS_Edge;

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Box2d;
	}

	namespace CadLib
	{

		class Cad3d_CurveOnPlane;

		class Cad3d_CurveOnPlaneTools
		{

		public:

			static TColCad3d_HAry1dOfCurveOnPlane RetrieveCurvesOnPlane(const TColCad3d_HAry1dOfEdgeOnSolid& Edges);

			//! Throw an exception if the list is empty
			static GeoLib::Entity_Box2d BoundingBoxOf(const TColCad3d_HAry1dOfCurveOnPlane& theCurves, const Standard_Real Offset = 0.0);

			static Standard_Boolean IsSameDirection(const Global_Handle(Cad3d_CurveOnPlane) theCurve1, const Global_Handle(Cad3d_CurveOnPlane) theCurve2, const Handle(Geom_Surface) theSurface1, const Handle(Geom_Surface) theSurface2);

			static TopoDS_Edge Get_TopoDS_Edge(const Cad3d_CurveOnPlane& theCurve, const Handle(Geom_Surface) theSurface);
		};
	}
}

#endif // !_Cad3d_CurveOnPlaneTools_Header
