#pragma once
#ifndef _Cad3d_PointOnSolidTools_Header
#define _Cad3d_PointOnSolidTools_Header

#include <Cad3d_PointOnSolid.hxx>
#include <TColCad3d_HAry1dOfPointOnSolid.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_PointOnSolidTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Cad3d_PointOnSolid) const thePoint1, Global_Handle(Cad3d_PointOnSolid) const thePoint2);

			static const Geom_Pnt3d& CoordOf(Global_Handle(Cad3d_PointOnSolid) Point);

			static TColGeom_Ary1dOfPnt3d GetStaticCoordsOf(const TColCad3d_HAry1dOfPointOnSolid& PointsOnSolid);

			static void GetStaticCoordsOf(const TColCad3d_HAry1dOfPointOnSolid& PointsOnSolid, TColGeom_Ary1dOfPnt3d& Coords);
		};
	}
}

#include <Cad3d_PointOnSolidToolsI.hxx>

#endif // !_Cad3d_PointOnSolidTools_Header
