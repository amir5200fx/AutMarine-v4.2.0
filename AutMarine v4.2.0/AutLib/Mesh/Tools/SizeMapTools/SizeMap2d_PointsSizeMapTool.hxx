#pragma once
#ifndef _SizeMap2d_PointsSizeMapTool_Header
#define _SizeMap2d_PointsSizeMapTool_Header

#include <SizeMap2d_BoundarySizeMapTool.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap2d_PointsSizeMapTool : public SizeMap2d_BoundarySizeMapTool
		{

		private:

			Standard_Integer theBucketSize_;

		public:

			SizeMap2d_PointsSizeMapTool(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad2d_Plane) thePlane);

			virtual ~SizeMap2d_PointsSizeMapTool();

			void SetBucketSize(const Standard_Integer BucketSize);

			void CreateSizeMap();
		};
	}
}

#endif // !_SizeMap2d_PointsSizeMapTool_Header
