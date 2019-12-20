#pragma once
#ifndef _Mesh2d_SizeMap_Header
#define _Mesh2d_SizeMap_Header

#include <Geom_Pnt2d.hxx>
#include <Entity_Box2d.hxx>
#include <Mesh2d_Edge.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		
		class Mesh2d_QualityMap;

		class Mesh2d_SizeMap
		{

		public:

			virtual Standard_Real BaseSize() const = 0;

			virtual Standard_Real ElementSize(const Geom_Pnt2d& Coord) const = 0;

			virtual Standard_Real ElementSize(const Mesh2d_Edge& Edge) const = 0;

			virtual Standard_Real Oriented(const Geom_Pnt2d& P0, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const = 0;

			virtual Standard_Real CalcUnitDistance(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const = 0;

			virtual Standard_Real CalcDistance(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const = 0;

			virtual Standard_Real CalcDistanceSQ(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const = 0;

			virtual Standard_Real CalcDistancePointFromLSeg(const Geom_Pnt2d& thePoint, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const = 0;

			virtual Standard_Real CalcDistancePointFromLSegSQ(const Geom_Pnt2d& thePoint, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const = 0;

			virtual Geom_Pnt2d CalcOptimumPoint(const Standard_Real Size, const Mesh2d_Edge& Edge) const = 0;

			virtual Geom_Pnt2d CalcCentreOf(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const = 0;

			virtual M_GEO Entity_Box2d CalcSearchRegion(const Standard_Real Radius, const Geom_Pnt2d& Centre) const = 0;

			virtual M_GEO Entity_Box2d CalcSearchRegion(const Standard_Real Radius, const Geom_Pnt2d& Centre, const Mesh2d_Edge& Edge) const = 0;

			virtual Standard_Real Integrand(const Geom_Pnt2d& Point, const Geom_Pnt2d& Vector) const = 0;

			virtual Standard_Real MetricIntegrand(const Geom_Pnt2d& Point, const Geom_Pnt2d& Vector) const = 0;

			virtual Standard_Real ElementQuality(const Geom_Pnt2d& theP0, const Geom_Pnt2d& theP1, const Geom_Pnt2d& theP2, const Mesh2d_QualityMap& theQualityMap) const = 0;

			virtual void ExportSearchingAreaToPlt(const Standard_Real Size, const Geom_Pnt2d& Point, fstream& File) const = 0;
		};
	}
}

#endif // !_Mesh2d_SizeMap_Header
