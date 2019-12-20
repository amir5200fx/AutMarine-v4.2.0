#pragma once
#ifndef _SizeMap2d_FullIntAnIso_Header
#define _SizeMap2d_FullIntAnIso_Header

#include <Mesh2d_SizeMap.hxx>
#include <Mesh2d_MetricMap.hxx>
#include <Entity_Metric1.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap2d_FullIntAnIso : public Mesh2d_SizeMap
		{

		protected:

			const Global_Handle(Mesh2d_SizeMap) theSizeMap_;

			const Global_Handle(Mesh2d_MetricMap) theMetricMap_;

			M_GEO Entity_Box2d theBoundingBox_;

			Standard_Real theTolerance_;

			Standard_Integer theMaxIters_;

			mutable M_GEO Entity_Metric1 theCurrentMetric_;

		public:

			SizeMap2d_FullIntAnIso(const Global_Handle(Mesh2d_SizeMap) theSizeMap, const Global_Handle(Mesh2d_MetricMap) theMetricMap);

			const Global_Handle(Mesh2d_SizeMap) SizeMap() const;

			const Global_Handle(Mesh2d_MetricMap) MetricMap() const;

			void SetMetric(const Global_Handle(Mesh2d_MetricMap) theMetricMap);

			virtual Standard_Real BaseSize() const;

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

			virtual void ExportSearchingAreaToPlt(const Standard_Real Size, const Geom_Pnt2d& Point, fstream& File) const;

		protected:

			Geom_Pnt2d CorrectPoint(const Geom_Pnt2d& theCentre, const Geom_Pnt2d& P) const;
		};
	}
}

#include <SizeMap2d_FullIntAnIsoI.hxx>

#endif // !_SizeMap2d_FullIntAnIso_Header
