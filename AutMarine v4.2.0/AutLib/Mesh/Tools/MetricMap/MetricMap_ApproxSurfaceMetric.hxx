#pragma once
#ifndef _MetricMap_ApproxSurfaceMetric_Header
#define _MetricMap_ApproxSurfaceMetric_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <Entity_Box2d.hxx>
#include <MetricMap_SurfaceMetricMap.hxx>
#include <GeoMesh_BackGroundMetric2d.hxx>
#include <TColEntity_HAry1dOfPolygon2d.hxx>

namespace AutLib
{

	namespace GeoLib
	{
		class GeoMesh_BackGroundMetric2d;
		class Entity_Polygon2d;
	}

	namespace MeshLib
	{

		class Mesh3d_SizeMap;

		class MetricMap_ApproxSurfaceMetric : public MetricMap_SurfaceMetricMap
		{

		private:

			M_GEO GeoMesh_BackGroundMetric2d theMetric_;

			TColEntity_HAry1dOfPolygon2d theSingularityHorizons_;

			Standard_Integer theNb_MIN_LEVELS_;
			Standard_Integer theNb_MAX_LEVELS_;

			Standard_Real theTolerance_;
			Standard_Real theDegeneracy_;
			Standard_Real theMaxMetricDet_;

			Standard_Boolean IsDone_;

		public:

			MetricMap_ApproxSurfaceMetric(const M_CAD Cad3d_SurfaceOnSolid& theSurface);

			~MetricMap_ApproxSurfaceMetric();

			Standard_Real MaxMetricDeterminant() const;

			Standard_Integer NbSingularityHorizons() const;

			Standard_Boolean IsDone() const;

			Global_Handle(M_GEO Entity_Polygon2d) SingularityHorizon(const Standard_Integer Index) const;

			const M_GEO GeoMesh_BackGroundMetric2d& Metric() const;

			virtual M_GEO Entity_Metric1 MetricAt(const M_GEO Geom_Pnt2d& theCoord) const;

			void SetTolerance(Standard_Real Tolerance);

			void SetDegeneracy(Standard_Real Degeneracy);

			void SetMinLevels(Standard_Integer MinLevels);

			void SetMaxLevels(Standard_Integer MaxLevels);

			void SetIntersection(M_GEO Entity_Metric1(*InterSection)(const M_GEO Entity_Metric1&, const M_GEO Entity_Metric1&));

			void Perform();

			void HvCorrection(const Standard_Real theFactor = 1.3, const Standard_Integer theMaxLevel = 5);

			void LaplacianSmoothing();

			void ExportMetricToPlt(const Mesh3d_SizeMap& SizeMap, fstream& File) const;

		private:

			void IdentifySingularityHorizon();
		};
	}
}

#include <MetricMap_ApproxSurfaceMetricI.hxx>

#endif // !_MetricMap_ApproxSurfaceMetric_Header
