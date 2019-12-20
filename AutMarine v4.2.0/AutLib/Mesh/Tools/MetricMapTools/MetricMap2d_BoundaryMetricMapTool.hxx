#pragma once
#ifndef _MetricMap2d_BoundaryMetricMapTool_Header
#define _MetricMap2d_BoundaryMetricMapTool_Header

#include <Standard_TypeDef.hxx>
#include <MetricMap2d_MetricMapTool.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap2d_BoundarySizeMapTool;

		class MetricMap2d_BoundaryMetricMapTool : public MetricMap2d_MetricMapTool
		{

		private:

			Standard_Integer theBucketSize_;

			const Global_Handle(SizeMap2d_BoundarySizeMapTool) theBoundarySize_;

		public:

			MetricMap2d_BoundaryMetricMapTool(const Global_Handle(SizeMap2d_BoundarySizeMapTool) theBoundarySize);

			void SetBucketSize(const Standard_Integer theBucketSize);

			void Perform();
		};
	}
}

#endif // !_MetricMap2d_BoundaryMetricMapTool_Header
