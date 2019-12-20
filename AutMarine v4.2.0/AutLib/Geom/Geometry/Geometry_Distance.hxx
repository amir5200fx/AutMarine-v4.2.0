#pragma once
#ifndef _Geometry_Distance_Header
#define _Geometry_Distance_Header

#include <Geom_Pnt2d.hxx>
#include <Geom_Pnt3d.hxx>
#include <Entity_Metric1.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Geometry_Distance
		{

		public:

			static Standard_Real InfNorm(const Standard_Real X0, const Standard_Real Y0, const Standard_Real X1, const Standard_Real Y1);

			static Standard_Real TwoNorm(const Standard_Real X0, const Standard_Real Y0, const Standard_Real X1, const Standard_Real Y1);

			static Standard_Real InfNorm(const Standard_Real X0, const Standard_Real Y0, const Standard_Real Z0, const Standard_Real X1, const Standard_Real Y1, const Standard_Real Z1);

			static Standard_Real TwoNorm(const Standard_Real X0, const Standard_Real Y0, const Standard_Real Z0, const Standard_Real X1, const Standard_Real Y1, const Standard_Real Z1);

			static Standard_Real Distance(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Entity_Metric1& Metric);

			static Standard_Real DistanceSQ(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Entity_Metric1& Metric);

			static Standard_Real DistanceFromLineSegment(const Geom_Pnt2d& thePoint, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2);

			static Standard_Real DistanceFromLineSegment(const Geom_Pnt3d& thePoint, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2);

			static Standard_Real DistanceFromLineSegmentSQ(const Geom_Pnt2d& thePoint, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2);

			static Standard_Real DistanceFromLineSegmentSQ(const Geom_Pnt3d& thePoint, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2);

			static Standard_Real DistancePointFromTriangle(const Geom_Pnt3d& thePoint, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3);

			static Standard_Real DistancePointFromTriangleSQ(const Geom_Pnt3d& thePoint, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3);

			static Standard_Real DistancePointFromProjectedEdgesOfTriangle(const Geom_Pnt3d& thePoint, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3);

			static Standard_Real DistancePointFromProjectedEdgesOfTriangleSQ(const Geom_Pnt3d& thePoint, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3);

			static Standard_Real DistanceLineSegmentFromLineSegment(const Geom_Pnt3d& P0, const Geom_Pnt3d& P1, const Geom_Pnt3d& Q0, const Geom_Pnt3d& Q1);

			static Standard_Real DistanceLineSegmentFromLineSegmentSQ(const Geom_Pnt3d& P0, const Geom_Pnt3d& P1, const Geom_Pnt3d& Q0, const Geom_Pnt3d& Q1);
		};
	}
}

#include <Geometry_DistanceI.hxx>

#endif // !_Geometry_Distance_Header
