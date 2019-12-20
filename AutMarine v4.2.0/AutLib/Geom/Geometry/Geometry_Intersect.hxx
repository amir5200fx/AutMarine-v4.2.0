#pragma once
#ifndef _Geometry_Intersect_Header
#define _Geometry_Intersect_Header

#include <Geom_Pnt2d.hxx>
#include <Entity_Box2d.hxx>
#include <Entity_Box3d.hxx>
#include <Global_DefineException.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Geometry_Intersect
		{

		public:

			static Geom_Pnt2d IntersectionTwoLines(const Geom_Pnt2d& P0, const Geom_Pnt2d& Vec0, const Geom_Pnt2d& P1, const Geom_Pnt2d& Vec1);

			static Geom_Pnt2d IntersectionTwoLines(const Geom_Pnt2d& P0, const Geom_Pnt2d& P1, const Geom_Pnt2d& Q0, const Geom_Pnt2d& Q1, Standard_Real & t1, Standard_Real & t2);

			static Standard_Boolean IsIntersectLineSegmentTriangle(const Geom_Pnt3d& theP0, const Geom_Pnt3d& theP1, const Geom_Pnt3d& theQ0, const Geom_Pnt3d& theQ1, const Geom_Pnt3d& theQ2);

			static Standard_Boolean IsIntersect(const Standard_Real U0, const Standard_Real U1, const Standard_Real V0, const Standard_Real V1);

			static Standard_Boolean IsIntersect(const Entity_Box2d & b1, const Entity_Box2d & b2);

			static Standard_Boolean IsIntersect(const Entity_Box3d & Box1, const Entity_Box3d & Box2);

			static Standard_Boolean IsIntersect(const Geom_Pnt2d& P0, const Geom_Pnt2d& t0, const Geom_Pnt2d& P1, const Geom_Pnt2d& t1, Standard_Real& s0, Standard_Real& s1, Geom_Pnt2d& Point);

			static Standard_Boolean IsIntersect(const Geom_Pnt2d& P0, const Geom_Pnt2d& P1, const Geom_Pnt2d& Q0, const Geom_Pnt2d& Q1, Geom_Pnt2d& Point);

			static Standard_Boolean IsIntersect(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Geom_Pnt2d& Q1, const Geom_Pnt2d& Q2);
		};
	}
}

#include <Geometry_IntersectI.hxx>

#endif // !_Geometry_Intersect_Header
