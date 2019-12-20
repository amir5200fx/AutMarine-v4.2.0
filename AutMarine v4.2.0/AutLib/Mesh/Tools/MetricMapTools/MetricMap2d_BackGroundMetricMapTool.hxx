#pragma once
#ifndef _MetricMap2d_BackGroundMetricMapTool_Header
#define _MetricMap2d_BackGroundMetricMapTool_Header

#include <MetricMap2d_MetricMapTool.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap2d_SizeMapTool;

		class MetricMap2d_BackGroundMetricMapTool : public MetricMap2d_MetricMapTool
		{

		private:

			Standard_Integer theBucketSize_;

			const Global_Handle(SizeMap2d_SizeMapTool) theSizeMap_;

		public:

			MetricMap2d_BackGroundMetricMapTool(const Global_Handle(SizeMap2d_SizeMapTool) theSizeMap);

			void SetBucketSize(const Standard_Integer theBucketSize);

			void Perform();
		};
	}
}

#endif // !_MetricMap2d_BackGroundMetricMapTool_Header
