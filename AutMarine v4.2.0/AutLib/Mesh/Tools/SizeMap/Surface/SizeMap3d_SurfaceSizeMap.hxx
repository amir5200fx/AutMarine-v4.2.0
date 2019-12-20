#pragma once
#ifndef _SizeMap3d_SurfaceSizeMap_Header
#define _SizeMap3d_SurfaceSizeMap_Header

#include <Mesh2d_SizeMap.hxx>
#include <Mesh3d_SizeMap.hxx>

#include <Geom_Surface.hxx>
#include <Standard_Handle.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap3d_SurfaceSizeMap : public Mesh2d_SizeMap
		{

		private:

			const Mesh3d_SizeMap& theSizeMap_;

			Handle(Geom_Surface) theSurface_;

		public:

			SizeMap3d_SurfaceSizeMap(const Mesh3d_SizeMap& SizeMap, const Handle(Geom_Surface)& Surface);

			Standard_Real BaseSize() const;

			Standard_Real ElementSize(const Geom_Pnt2d& Coord) const;

			Standard_Real ElementSize(const Mesh2d_Edge& Edge) const;

			Standard_Real Oriented(const Geom_Pnt2d& P0, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			Standard_Real CalcUnitDistance(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			Standard_Real CalcDistance(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			Standard_Real CalcDistanceSQ(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			Standard_Real CalcDistancePointFromLSeg(const Geom_Pnt2d& thePoint, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			Standard_Real CalcDistancePointFromLSegSQ(const Geom_Pnt2d& thePoint, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			Geom_Pnt2d CalcOptimumPoint(const Standard_Real Size, const Mesh2d_Edge& Edge) const;

			Geom_Pnt2d CalcCentreOf(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			M_GEO Entity_Box2d CalcSearchRegion(const Standard_Real Radius, const Geom_Pnt2d& Centre) const;

			M_GEO Entity_Box2d CalcSearchRegion(const Standard_Real Radius, const Geom_Pnt2d& Centre, const Mesh2d_Edge& Edge) const;

			Standard_Real Integrand(const Geom_Pnt2d& Point, const Geom_Pnt2d& Vector) const;

			Standard_Real MetricIntegrand(const Geom_Pnt2d& Point, const Geom_Pnt2d& Vector) const;

			Standard_Real ElementQuality(const Geom_Pnt2d& theP0, const Geom_Pnt2d& theP1, const Geom_Pnt2d& theP2, const Mesh2d_QualityMap& theQualityMap) const;

			void ExportSearchingAreaToPlt(const Standard_Real Size, const Geom_Pnt2d& Point, fstream& File) const;
		};
	}
}

#include <SizeMap3d_SurfaceSizeMapI.hxx>

#endif // !_SizeMap_SurfaceSizeMap_Header
