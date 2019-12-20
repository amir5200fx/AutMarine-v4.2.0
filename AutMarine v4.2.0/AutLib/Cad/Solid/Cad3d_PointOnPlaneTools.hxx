#pragma once
#ifndef _Cad3d_PointOnPlaneTools_Header
#define _Cad3d_PointOnPlaneTools_Header

#include <Cad3d_PointOnPlane.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColCad3d_HAry1dOfPointOnPlane.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_PointOnPlaneTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Cad3d_PointOnPlane) const &thePoint1, Global_Handle(Cad3d_PointOnPlane) const &thePoint2);

			static const Geom_Pnt2d& CoordOf(Global_Handle(Cad3d_PointOnPlane) thePoint);

			static TColGeom_Ary1dOfPnt2d GetCoordsOf(const TColCad3d_HAry1dOfPointOnPlane& thePoints);
		};
	}
}

#include <Cad3d_PointOnPlaneToolsI.hxx>

#endif // !_Cad3d_PointOnPlaneTools_Header
