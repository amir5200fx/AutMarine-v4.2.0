#pragma once
#ifndef _SizeMap3d_UniSize_Header
#define _SizeMap3d_UniSize_Header

#include <Mesh3d_SizeMap.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap3d_UniSize : public Mesh3d_SizeMap
		{

		private:

			Standard_Real theSize_;

			Standard_Real theInvSize_;

		public:

			SizeMap3d_UniSize(const Standard_Real Size);

			Standard_Real BaseSize() const;

			Standard_Real ElementSize(const Mesh3d_Facet& Facet) const;

			Standard_Real ElementSize(const Geom_Pnt3d& Coord) const;

			Standard_Real CalcUnitDistance(const Geom_Pnt3d& Coord1, const Geom_Pnt3d& Coord2) const;

			Standard_Real CalcDistance(const Geom_Pnt3d& Coord1, const Geom_Pnt3d& Coord2) const;

			Standard_Real CalcDistanceSQ(const Geom_Pnt3d& Coord1, const Geom_Pnt3d& Coord2) const;

			Standard_Real CalcDistanceFromTriangle(const Geom_Pnt3d& thePoint, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3) const;

			Standard_Real CalcDistanceFromTriangleSQ(const Geom_Pnt3d& thePoint, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3) const;

			Standard_Real CalcDistanceFromProjectedEdgesOfTriangle(const Geom_Pnt3d& thePoint, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3) const;

			Standard_Real CalcDistanceFromProjectedEdgesOfTriangleSQ(const Geom_Pnt3d& thePoint, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3) const;

			Standard_Real CalcDistanceEdgeFromEdge(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& Q1, const Geom_Pnt3d& Q2) const;

			Standard_Real CalcDistanceEdgeFromEdgeSQ(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& Q1, const Geom_Pnt3d& Q2) const;

			Standard_Real CalcArea(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3) const;

			Geom_Pnt3d CalcOptimumCoord(const Standard_Real Size, const Mesh3d_Facet& Facet) const;

			M_GEO Entity_Box3d CalcSearchingRegion(const Standard_Real Radius, const Geom_Pnt3d& theCentre) const;

			Standard_Real Integrand(const Geom_Pnt3d& Point, const Geom_Pnt3d& Vector) const;

			Standard_Real MetricIntegrand(const Geom_Pnt3d& Point, const Geom_Pnt3d& Vector) const;

			void ExportSizeMapToPlt(fstream& File) const {}
		};
	}
}

#include <SizeMap3d_UniSizeI.hxx>

#endif // !_SizeMap3d_UniSize_Header
