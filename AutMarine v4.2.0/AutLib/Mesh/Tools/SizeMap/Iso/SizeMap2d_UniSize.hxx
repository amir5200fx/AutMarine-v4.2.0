#pragma once
#ifndef _Mesh2d_UniSize_Header
#define _Mesh2d_UniSize_Header

#include <Mesh2d_SizeMap.hxx>
#include <Geometry_Distance.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		
		class SizeMap2d_UniSize : public Mesh2d_SizeMap
		{

		protected:

			Standard_Real theSize_;

			Standard_Real theInvSize_;

		public:

			SizeMap2d_UniSize(const Standard_Real Size);

			virtual Standard_Real BaseSize() const override;

			virtual Standard_Real ElementSize(const Geom_Pnt2d& Coord) const;

			virtual Standard_Real ElementSize(const Mesh2d_Edge& Edge) const;

			virtual Standard_Real Oriented(const Geom_Pnt2d& P0, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			virtual Standard_Real CalcUnitDistance(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			virtual Standard_Real CalcDistance(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			virtual Standard_Real CalcDistanceSQ(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			virtual Standard_Real CalcDistancePointFromLSeg(const Geom_Pnt2d& thePoint, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			virtual Standard_Real CalcDistancePointFromLSegSQ(const Geom_Pnt2d& thePoint, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			virtual Geom_Pnt2d CalcOptimumPoint(const Standard_Real Size, const Mesh2d_Edge& Edge) const;

			virtual Geom_Pnt2d CalcCentreOf(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2) const;

			virtual M_GEO Entity_Box2d CalcSearchRegion(const Standard_Real Radius, const Geom_Pnt2d& Centre) const;

			virtual M_GEO Entity_Box2d CalcSearchRegion(const Standard_Real Radius, const Geom_Pnt2d& Centre, const Mesh2d_Edge& Edge) const;

			virtual Standard_Real Integrand(const Geom_Pnt2d& Point, const Geom_Pnt2d& Vector) const;

			virtual Standard_Real MetricIntegrand(const Geom_Pnt2d& Point, const Geom_Pnt2d& Vector) const;

			virtual Standard_Real ElementQuality(const Geom_Pnt2d& theP0, const Geom_Pnt2d& theP1, const Geom_Pnt2d& theP2, const Mesh2d_QualityMap& theQualityMap) const;

			void ExportSearchingAreaToPlt(const Standard_Real Size, const Geom_Pnt2d& Point, fstream& File) const {}
		};
	}
}

#include <SizeMap2d_UniSizeI.hxx>

#endif // !_Mesh2d_UniSize_Header