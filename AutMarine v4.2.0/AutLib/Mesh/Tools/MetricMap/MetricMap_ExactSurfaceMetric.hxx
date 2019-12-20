#pragma once
#ifndef _MetricMap_ExactSurfaceMetric_Header
#define _MetricMap_ExactSurfaceMetric_Header

#include <Entity_Box2d.hxx>
#include <Entity_Metric1.hxx>
#include <MetricMap_SurfaceMetricMap.hxx>

class Geom_Surface;

namespace AutLib
{
	namespace MeshLib
	{

		class MetricMap_ExactSurfaceMetric : public MetricMap_SurfaceMetricMap
		{

		private:

			Handle(Geom_Surface) thePatch_;

		public:

			MetricMap_ExactSurfaceMetric(const M_CAD Cad3d_SurfaceOnSolid& theSurface);

			virtual M_GEO Entity_Metric1 MetricAt(const M_GEO Geom_Pnt2d& Coord) const;

		};
	}
}

#endif // !_MetricMap_ExactSurfaceMetric_Header
