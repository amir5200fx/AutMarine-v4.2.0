#pragma once
#ifndef _SizeMap2d_UnionMetricMaps_Header
#define _SizeMap2d_UnionMetricMaps_Header

#include <Standard_Stream.hxx>
#include <TColGeoMesh_HBasicQueueOfBackGroundMetric2d.hxx>

namespace AutLib
{

	namespace GeoLib
	{
		class GeoMesh_BackGroundMetric2d;
		class Entity_Metric1;
	}

	namespace MeshLib
	{

		class SizeMap2d_UnionMetricMaps
		{

		private:

			TColGeoMesh_HBasicQueueOfBackGroundMetric2d theMetricMaps_;

			Standard_Real theTolerance_;

			Standard_Integer theMinSubdivision_;
			Standard_Integer theMaxSubdivision_;

			Standard_Boolean IsDone_;

			GeoLib::Entity_Metric1(*InterSection)(const M_GEO Entity_Metric1&, const M_GEO Entity_Metric1&);

			Global_Handle(M_GEO GeoMesh_BackGroundMetric2d) theBackMetric_;

		public:

			SizeMap2d_UnionMetricMaps();

			~SizeMap2d_UnionMetricMaps();

			void ImportSizeMap(const Global_Handle(M_GEO GeoMesh_BackGroundMetric2d) theBack);

			void SetTolerance(const Standard_Real theTolerance);

			void SetMinSubdivide(const Standard_Integer theValue);

			void SetMaxSubdivide(const Standard_Integer theValue);

			void SetIntersection(GeoLib::Entity_Metric1(*theInterSection)(const M_GEO Entity_Metric1&, const M_GEO Entity_Metric1&));

			void Perform();

			Standard_Boolean IsDone() const;

			//! Warning: not removed from memory automatically
			Global_Handle(M_GEO GeoMesh_BackGroundMetric2d) BackGroundMetric() const;

			void ExportBackMeshToPlt(fstream& File) const;
		};
	}
}

#include <SizeMap2d_UnionMetricMapsI.hxx>

#endif // !_SizeMap2d_UnionAnIsoSizeMaps_Header
