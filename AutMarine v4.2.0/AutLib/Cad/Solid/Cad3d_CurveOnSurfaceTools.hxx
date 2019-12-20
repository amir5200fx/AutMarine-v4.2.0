#pragma once
#ifndef _Cad3d_CurveOnSurfaceTools_Header
#define _Cad3d_CurveOnSurfaceTools_Header

#include <Standard_TypeDef.hxx>
#include <Geom_Pnt3d.hxx>
#include <TColCad3d_HAry1dOfEdgeOnSolid.hxx>
#include <TColCad3d_HAry1dOfSurfaceOnSolid.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_PolyLine3d;
	}

	namespace CadLib
	{

		class Cad3d_CurveOnSurface;

		class Cad3d_CurveOnSurfaceTools
		{

		public:

			static GeoLib::Entity_PolyLine3d DiscretizedOf(const Cad3d_CurveOnSurface& EdgeOnSurface, const Standard_Real Deflection, const Standard_Real Tolerance, const Standard_Integer NbSamples = 5);

			static Standard_Boolean IsSameDirection(const Global_Handle(Cad3d_CurveOnSurface) theCurve1, const Global_Handle(Cad3d_CurveOnSurface) theCurve2);

			static Standard_Real Distance(const Geom_Pnt3d& thePoint, const Cad3d_CurveOnSurface& theEdge);

			static Standard_Real Distance(const Cad3d_CurveOnSurface& theEdge1, const Cad3d_CurveOnSurface& theEdge2);
		};
	}
}

#endif // !_Cad3d_EdgeOnSurfaceTools_Header
