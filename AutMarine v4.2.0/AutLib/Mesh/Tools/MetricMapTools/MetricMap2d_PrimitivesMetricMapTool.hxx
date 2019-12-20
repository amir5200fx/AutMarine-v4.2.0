#pragma once
#ifndef _MetricMap2d_PrimitivesMetricMapTool_Header
#define _MetricMap2d_PrimitivesMetricMapTool_Header

#include <MetricMap2d_MetricMapTool.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap2d_PrimitiveShapesSizeMapTool;

		class MetricMap2d_PrimitivesMetricMapTool : public MetricMap2d_MetricMapTool
		{

		private:

			Standard_Integer theBucketSize_;

			const Global_Handle(SizeMap2d_PrimitiveShapesSizeMapTool) theSizeMap_;

		public:

			MetricMap2d_PrimitivesMetricMapTool(const Global_Handle(SizeMap2d_PrimitiveShapesSizeMapTool) theSizeMap);

			void SetBucketSize(const Standard_Integer theBucketSize);

			void Perform();

		};
	}
}

#endif // !_MetricMap2d_PrimitivesMetricMapTool_Header
