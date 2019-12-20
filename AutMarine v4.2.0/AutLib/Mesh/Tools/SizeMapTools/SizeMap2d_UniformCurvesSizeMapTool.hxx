#pragma once
#ifndef _SizeMap2d_UniformCurvesSizeMapTool_Header
#define _SizeMap2d_UniformCurvesSizeMapTool_Header

#include <SizeMap2d_BoundarySizeMapTool.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap2d_UniformCurvesSizeMapTool : public SizeMap2d_BoundarySizeMapTool
		{

		protected:

			Standard_Integer theBucketSize_;

		public:

			SizeMap2d_UniformCurvesSizeMapTool(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad2d_Plane) thePlane);

			virtual ~SizeMap2d_UniformCurvesSizeMapTool();

			void SetBucketSize(const Standard_Integer BucketSize);

			void CreateSizeMap();

		private:

			void CreateSizeMap(const TColCad2d_HAry1dOfEdgeOnPlane& theEdges);
		};
	}
}

#endif // !_SizeMap2d_UniformCurvesSizeMapTool_Header
