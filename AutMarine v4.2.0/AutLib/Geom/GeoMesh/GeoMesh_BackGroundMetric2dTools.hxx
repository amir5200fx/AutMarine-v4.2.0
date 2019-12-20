#pragma once
#ifndef _GeoMesh_BackGroundMetric2dTools_Header
#define _GeoMesh_BackGroundMetric2dTools_Header

#include <TColMesh2d_HAry1dOfMetricSourcePoint.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Metric1;
		class GeoMesh_BackGroundMetric2d;

		class GeoMesh_BackGroundMetric2dTools
		{

		public:

			static void SetSourcesToMesh(const TColMesh2d_HAry1dOfMetricSourcePoint& theSources, GeoMesh_BackGroundMetric2d& theMesh, Entity_Metric1(*InterSection)(const Entity_Metric1&, const Entity_Metric1&));
		};
	}
}

#endif // !_GeoMesh_BackGroundMetric2dTools_Header
