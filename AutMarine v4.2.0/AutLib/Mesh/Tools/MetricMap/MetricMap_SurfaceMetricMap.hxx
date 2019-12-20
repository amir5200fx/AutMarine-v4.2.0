#pragma once
#ifndef _MetricMap_SurfaceMetricMap_Header
#define _MetricMap_SurfaceMetricMap_Header

#include <Entity_Box2d.hxx>
#include <Entity_Metric1.hxx>
#include <Mesh2d_MetricMap.hxx>

class Geom_Surface;

namespace AutLib
{
	namespace CadLib
	{
		class Cad3d_SurfaceOnSolid;
	}

	namespace MeshLib
	{

		class MetricMap_SurfaceMetricMap : public  Mesh2d_MetricMap
		{

		protected:

			const M_CAD Cad3d_SurfaceOnSolid& theSurface_;

			Standard_String theSurfaceName_;

		public:

			virtual M_GEO Entity_Metric1 MetricAt(const M_GEO Geom_Pnt2d& Coord) const;

			virtual Standard_Real ElementQuality(const GeoLib::Geom_Pnt2d& theP0, const GeoLib::Geom_Pnt2d& theP1, const GeoLib::Geom_Pnt2d& theP2, const Mesh2d_QualityMap & theQualityMap) const;

			const Standard_String& Name() const;

			void SetSurfaceName(const Standard_String& Name);

			M_GEO Entity_Box2d CalcBoundingBox() const;

		protected:

			MetricMap_SurfaceMetricMap(const M_CAD Cad3d_SurfaceOnSolid& theSurface);

		};
	}
}

#include <MetricMap_SurfaceMetricMapI.hxx>

#endif // !_MetricMap_SurfaceMetricMap_Header
