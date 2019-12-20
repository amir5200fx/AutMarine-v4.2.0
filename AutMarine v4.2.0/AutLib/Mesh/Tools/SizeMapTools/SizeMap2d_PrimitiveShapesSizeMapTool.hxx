#pragma once
#ifndef _SizeMap2d_PrimitiveShapesSizeMapTool_Header
#define _SizeMap2d_PrimitiveShapesSizeMapTool_Header

#include <Entity_Box2d.hxx>
#include <SizeMap2d_SizeMapTool.hxx>
#include <TColEntity_HBasizQueueOfTriangulation2d.hxx>
#include <TColCad2d_HBasicQueueOfPlane.hxx>
#include <TColEntity_HAry1dOfNode2d.hxx>

namespace AutLib
{

	namespace GeoLib
	{
		class GeoMesh_BackGroundMesh2d;
		class Entity_Metric2;
	}

	namespace MeshLib
	{

		class Mesh_ReferenceValues;

		class SizeMap2d_PrimitiveShapesSizeMapTool : public SizeMap2d_SizeMapTool
		{

		private:

			TColCad2d_HBasicQueueOfPlane theShapes_;

			Standard_Integer theBucketSize_;

			Global_Handle(M_GEO Entity_Metric2) theMetric_;

			TColEntity_HAry1dOfNode2d theInnerNodes_;
			TColEntity_HAry1dOfNode2d theOutterNodes_;

		public:

			SizeMap2d_PrimitiveShapesSizeMapTool(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad2d_Plane) thePlane);

			virtual ~SizeMap2d_PrimitiveShapesSizeMapTool();

			const TColEntity_HAry1dOfNode2d& InnerNodes() const;

			const TColEntity_HAry1dOfNode2d& OutterNodes() const;

			const Global_Handle(M_GEO Entity_Metric2) Metric() const;

			void ImportShape(const Global_Handle(M_CAD Cad2d_Plane) theShape);

			void SetMetric(const M_GEO Entity_Metric2& theMetric);

			void CreateSizeMap();
		};
	}
}

#endif // !_SizeMap2d_PrimitiveShapesSizeMapTool_Header
