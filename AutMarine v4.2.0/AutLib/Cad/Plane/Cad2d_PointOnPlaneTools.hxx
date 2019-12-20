#pragma once
#ifndef _Cad2d_PointOnPlaneTools_Header
#define _Cad2d_PointOnPlaneTools_Header

#include <Cad2d_PointOnPlane.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColCad2d_HAry1dOfPointOnPlane.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_PointOnPlaneTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Cad2d_PointOnPlane) const &thePoint1, Global_Handle(Cad2d_PointOnPlane) const &thePoint2);

			static const Geom_Pnt2d& CoordOf(Global_Handle(Cad2d_PointOnPlane) thePoint);

			static TColGeom_Ary1dOfPnt2d GetCoordsOf(const TColCad2d_HAry1dOfPointOnPlane& thePoints);


		};
	}
}

#include <Cad2d_PointOnPlaneToolsI.hxx>

#endif // !_Cad2d_PointOnPlaneTools_Header
