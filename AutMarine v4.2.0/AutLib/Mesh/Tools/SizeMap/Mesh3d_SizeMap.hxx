#pragma once
#ifndef _Mesh3d_SizeMap_Header
#define _Mesh3d_SizeMap_Header

#include <Geom_Pnt3d.hxx>
#include <Mesh3d_Facet.hxx>
#include <Entity_Box3d.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_SizeMap
		{

		public:

			virtual Standard_Real BaseSize() const = 0;

			virtual Standard_Real ElementSize(const Mesh3d_Facet& Facet) const = 0;

			virtual Standard_Real ElementSize(const Geom_Pnt3d& Coord) const = 0;

			virtual Standard_Real CalcUnitDistance(const Geom_Pnt3d& Coord1, const Geom_Pnt3d& Coord2) const = 0;

			virtual Standard_Real CalcDistance(const Geom_Pnt3d& Coord1, const Geom_Pnt3d& Coord2) const = 0;

			virtual Standard_Real CalcDistanceSQ(const Geom_Pnt3d& Coord1, const Geom_Pnt3d& Coord2) const = 0;

			virtual Standard_Real CalcDistanceFromTriangle(const Geom_Pnt3d& thePoint, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3) const = 0;

			virtual Standard_Real CalcDistanceFromTriangleSQ(const Geom_Pnt3d& thePoint, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3) const = 0;

			virtual Standard_Real CalcDistanceFromProjectedEdgesOfTriangle(const Geom_Pnt3d& thePoint, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3) const = 0;

			virtual Standard_Real CalcDistanceFromProjectedEdgesOfTriangleSQ(const Geom_Pnt3d& thePoint, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3) const = 0;

			virtual Standard_Real CalcDistanceEdgeFromEdge(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& Q1, const Geom_Pnt3d& Q2) const = 0;

			virtual Standard_Real CalcDistanceEdgeFromEdgeSQ(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& Q1, const Geom_Pnt3d& Q2) const = 0;

			virtual Standard_Real CalcArea(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3) const = 0;

			virtual Geom_Pnt3d CalcOptimumCoord(const Standard_Real Size, const Mesh3d_Facet& Facet) const = 0;

			virtual M_GEO Entity_Box3d CalcSearchingRegion(const Standard_Real Radius, const Geom_Pnt3d& theCentre) const = 0;

			virtual Standard_Real Integrand(const Geom_Pnt3d& Point, const Geom_Pnt3d& Vector) const = 0;

			virtual Standard_Real MetricIntegrand(const Geom_Pnt3d& Point, const Geom_Pnt3d& Vector) const = 0;

			virtual void ExportSizeMapToPlt(fstream& File) const = 0;
		};
	}
}

#endif // !_Mesh3d_SizeMap_Header
