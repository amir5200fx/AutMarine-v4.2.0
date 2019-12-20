#pragma once
#ifndef _SizeMap3d_PrimitiveShapesSizeMapTool_Header
#define _SizeMap3d_PrimitiveShapesSizeMapTool_Header

#include <Entity_Box3d.hxx>
#include <SizeMap3d_SizeMapTool.hxx>
#include <TColSizeMap3d_HBasicQueueOfPrimitiveShapeSource.hxx>
#include <TColEntity_HBasicQueueOfTetrahedralization.hxx>
#include <TColEntity_HAry1dOfNode3d.hxx>

namespace AutLib
{

	namespace GeoLib
	{
		class GeoMesh_BackGroundMesh3d;
	}

	namespace MeshLib
	{

		class Mesh_ReferenceValues;

		class SizeMap3d_PrimitiveShapesSizeMapTool : public SizeMap3d_SizeMapTool
		{

		private:

			TColSizeMap3d_HBasicQueueOfPrimitiveShapeSource theShapes_;

			Standard_Integer theBucketSize_;

			TColEntity_HAry1dOfNode3d theInnerNodes_;
			TColEntity_HAry1dOfNode3d theOutterNodes_;

		public:

			SizeMap3d_PrimitiveShapesSizeMapTool(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad3d_Solid) theSolid);

			virtual ~SizeMap3d_PrimitiveShapesSizeMapTool();

			void SetBucketSize(const Standard_Integer BucketSize);

			void ImportSource(const Global_Handle(SizeMap3d_PrimitiveShapeSource) theShape);

			void CreateSizeMap();

			

			//virtual void RetrieveEntitiesTo(TColCad3d_HAry1dOfEntityOnSolid& theEntities) const;
		};
	}
}

#endif // !_SizeMap3d_PrimitiveShapesSizeMapTool_Header
