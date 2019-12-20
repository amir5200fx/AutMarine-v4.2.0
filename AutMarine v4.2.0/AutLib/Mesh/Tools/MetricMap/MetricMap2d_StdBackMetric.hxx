#pragma once
#ifndef _MetricMap2d_StdBackMetric_Header
#define _MetricMap2d_StdBackMetric_Header

#include <Mesh2d_MetricMap.hxx>
#include <GeoMesh_BackGroundMetric2d.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class MetricMap2d_StdBackMetric : public Mesh2d_MetricMap
		{

		private:

			const M_GEO GeoMesh_BackGroundMetric2d& theMetric_;

		public:

			MetricMap2d_StdBackMetric(const M_GEO GeoMesh_BackGroundMetric2d& theMetric);

			virtual GeoLib::Entity_Metric1 MetricAt(const GeoLib::Geom_Pnt2d& theCoord) const;

			virtual Standard_Real ElementQuality(const GeoLib::Geom_Pnt2d& theP0, const GeoLib::Geom_Pnt2d& theP1, const GeoLib::Geom_Pnt2d& theP2, const Mesh2d_QualityMap & theQualityMap) const;
		};
	}
}

#include <MetricMap2d_StdBackMetricI.hxx>

#endif // !_MetricMap2d_StdBackMetric_Header
