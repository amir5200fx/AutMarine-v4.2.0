#pragma once
#ifndef _SizeMap3d_UniformSurfacesSizeMapTool_Header
#define _SizeMap3d_UniformSurfacesSizeMapTool_Header

#include <SizeMap3d_BoundarySizeMapTool.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap3d_UniformSurfacesSizeMapTool : public SizeMap3d_BoundarySizeMapTool
		{

		private:

			Standard_Integer theBucketSize_;

		public:

			SizeMap3d_UniformSurfacesSizeMapTool(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad3d_Solid) theSolid);

			virtual ~SizeMap3d_UniformSurfacesSizeMapTool();

			void SetBucketSize(const Standard_Integer BucketSize);

			void CreateSizeMap();

			virtual void RetrieveEntitiesTo(TColCad3d_HAry1dOfEntityOnSolid& theEntities) const;
		};
	}
}

#endif // !_SizeMap3d_UniformSurfacesSizeMapTool_Header
