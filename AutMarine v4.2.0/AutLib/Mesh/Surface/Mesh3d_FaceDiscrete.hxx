#pragma once
#ifndef _Mesh3d_FaceDiscrete_Header
#define _Mesh3d_FaceDiscrete_Header

#include <Global_Macros.hxx>
#include <Global_Memory.hxx>
#include <Entity_StaticChain2d.hxx>
#include <Entity_Triangulation2d.hxx>
#include <Entity_Triangulation3d.hxx>
#include <TColMesh2d_HAry1dOfEdge.hxx>

class TopoDS_Face;

namespace AutLib
{
	
	namespace CadLib
	{
		class Cad2d_Plane;
	}

	namespace MeshLib
	{

		class Mesh2d_SizeMap;
		class Mesh2d_MetricMap;
		class MetricMap_ApproxSurfaceMetric;
		class MetricMap_ExactSurfaceMetric;
		class SizeMap2d_FullIntAnIso;

		class Mesh3d_FaceDiscrete
		{

		private:

			const TopoDS_Face& theFace_;

			Standard_Real theSize_;
			Standard_Real theDegeneracy_;

			M_GEO Entity_Triangulation2d theParaMesh_;

			M_GEO Entity_Triangulation3d theSurfaceMesh_;

			M_GEO Entity_StaticChain2d theBoundary_;

			Standard_Boolean ApplySmoothing_;
			Standard_Boolean ApplyOptimization_;
			Standard_Boolean UseExactMetric_;
			Standard_Boolean IsDone_;

			Standard_String theSurfaceName_;

			Standard_Integer theVerbose_;

			Global_Handle(SizeMap2d_FullIntAnIso)(*CreateAnIsoSizeMap)(const Global_Handle(Mesh2d_SizeMap), const Global_Handle(Mesh2d_MetricMap));

		public:

			Mesh3d_FaceDiscrete(const Standard_Real theSize, const TopoDS_Face& theFace);

			Standard_Boolean IsDone() const;

			const M_GEO Entity_Triangulation2d& ParaMesh() const;

			const M_GEO Entity_Triangulation3d& SurfaceMesh() const;

			void ApplySmoothing(const Standard_Boolean ApplySmoothing);

			void ApplyOptimization(const Standard_Boolean ApplyOptimization);

			void SetToUseExactMetric();

			void SetSurfaceName(const Standard_String Name);

			void Perform();

			void ExportTriangulationToPlt(fstream& File) const;

			void ExportParametricMeshToPlt(fstream& File) const;

			void ExportParametricBoundaryToPlt(fstream& File) const;

		private:

			Global_Handle(M_CAD Cad2d_Plane) GetPlane() const;

			TColMesh2d_HAry1dOfEdge RemoveDegeneracy2(const MetricMap_ApproxSurfaceMetric& theApproxMetric, const MetricMap_ExactSurfaceMetric theExactMetric, const Mesh2d_SizeMap& theSizeMap, const Mesh2d_SizeMap& theBoundarySizeMap, const Standard_Real theDegeneracy);
		};
	}
}

#include <Mesh3d_FaceDiscreteI.hxx>

#endif // !_Mesh3d_FaceDiscrete_Header
