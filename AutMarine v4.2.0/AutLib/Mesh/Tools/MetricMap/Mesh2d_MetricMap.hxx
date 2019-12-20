#pragma once
#ifndef _Mesh2d_MetricMap_Header
#define _Mesh2d_MetricMap_Header

#include <Entity_Box2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Metric1;
		class Geom_Pnt2d;
	}

	namespace MeshLib
	{

		class Mesh2d_QualityMap;

		class Mesh2d_MetricMap
		{

		private:

			M_GEO Entity_Box2d theBoundingBox_;

		public:

			virtual GeoLib::Entity_Metric1 MetricAt(const GeoLib::Geom_Pnt2d& theCoord) const = 0;

			virtual Standard_Real ElementQuality(const GeoLib::Geom_Pnt2d& theP0, const GeoLib::Geom_Pnt2d& theP1, const GeoLib::Geom_Pnt2d& theP2, const Mesh2d_QualityMap & theQualityMap) const = 0;

			const M_GEO Entity_Box2d& BoundingBox() const;

			void SetBoundingBox(const M_GEO Entity_Box2d& theBox);

		protected:

			Mesh2d_MetricMap();
		};
	}
}

#include <Mesh2d_MetricMapI.hxx>

#endif // !_Mesh2d_MetricMap_Header
