#pragma once
#ifndef _Mesh3d_SurfaceMesher_Header
#define _Mesh3d_SurfaceMesher_Header

#include <Global_Memory.hxx>
#include <Entity_Triangulation2d.hxx>
#include <Entity_Triangulation3d.hxx>
#include <Entity_StaticChain2d.hxx>
#include <Entity_StaticChain3d.hxx>
#include <TColMesh2d_HAry1dOfEdge.hxx>

class TopoDS_Face;

namespace AutLib
{

	namespace CadLib
	{
		class Cad3d_SurfaceOnSolid;
	}

	namespace MeshLib
	{

		class Mesh3d_SizeMap;
		class Mesh2d_SizeMap;
		class Mesh2d_MetricMap;
		class Mesh2d_QualityMap;
		class SizeMap2d_FullIntAnIso;
		class MetricMap_SurfaceMetricMap;
		class MetricMap_ApproxSurfaceMetric;
		class MetricMap_ExactSurfaceMetric;

		class Mesh3d_SurfaceMesher
		{

		private:

			const Mesh3d_SizeMap& theSizeMap_;

			const Global_Handle(M_CAD Cad3d_SurfaceOnSolid) theSurface_;

			M_GEO Entity_Triangulation2d theParaMesh_;

			M_GEO Entity_Triangulation3d theSurfaceMesh_;
			M_GEO Entity_Triangulation3d theModifiedSurfaceMesh_;

			M_GEO Entity_StaticChain2d theBoundary_;
			M_GEO Entity_StaticChain3d theBoundary3d_;
			M_GEO Entity_StaticChain2d theModifiedBoundary_;

			Standard_Boolean ApplySmoothing_;
			Standard_Boolean ApplyOptimization_;
			Standard_Boolean UseExactMetric_;
			Standard_Boolean IsDone_;

			Standard_Real theMaxGradation_;
			Standard_Real theSmoothingFactor_;
			Standard_Real theDegeneracy_;

			Standard_String theSurfaceName_;

			Standard_Integer theVerbose_;
			Standard_Integer theIndex_;

			Global_Handle(SizeMap2d_FullIntAnIso)(*CreateAnIsoSizeMap)(const Global_Handle(Mesh2d_SizeMap), const Global_Handle(Mesh2d_MetricMap));

			Global_Handle(MetricMap_ApproxSurfaceMetric) theAppxSurfaceMetric_;

			Standard_Boolean FaceMODE_;

		public:

			Mesh3d_SurfaceMesher(const Mesh3d_SizeMap& SizeMap, const M_CAD Cad3d_SurfaceOnSolid& theSurface);

			Mesh3d_SurfaceMesher(const Mesh3d_SizeMap& SizeMap, const TopoDS_Face& theSurface);

			~Mesh3d_SurfaceMesher();

			Standard_Boolean IsDone() const;

			Standard_Integer Index() const;

			M_GEO Entity_Triangulation3d& ModifiedSurfaceMesh();

			const M_GEO Entity_Triangulation3d& ModifiedSurfaceMesh() const;

			const M_GEO Entity_Triangulation2d& ParaMesh() const;

			const M_GEO Entity_Triangulation3d& SurfaceMesh() const;

			const M_GEO Entity_StaticChain3d& Boundary3d() const;

			void ApplyMetricSmoothing(const Standard_Boolean ApplySmoothing);

			void ApplyOptimization(const Standard_Boolean ApplyOptimization);

			//! Usaually set value > 1.0
			void SetMaxMetricGradation(const Standard_Real Gradation);

			void SetIndex(const Standard_Integer theIndex);

			void SetSurfaceName(const Standard_String Name);

			void SetVerbosity(const Standard_Integer theVerbose);

			void SetSmoothingFactor(const Standard_Real theSmoothingFactor);

			void SetAnIsoSizeMap(Global_Handle(SizeMap2d_FullIntAnIso)(*theCreateAnIsoSizeMap)(const Global_Handle(Mesh2d_SizeMap), const Global_Handle(Mesh2d_MetricMap)));

			void UseExactMetric();

			void Perform();

			void ExportDomainToPlt(fstream& File) const;

			void ExportQualityMeshToPlt(fstream& File, const Mesh2d_QualityMap& theQUalityMap) const;

			void ExportModifiedDomainToPlt(fstream& File) const;

			void ExportSurfaceMetricDeterminant(fstream& File) const;

			void ExportSingularityHorizonToPlt(fstream& File) const;

			void ExportModifiedMetricDomain(fstream& File) const;

			void ExportSurfaceMeshToPlt(fstream& File) const;

			void ExportParametricMeshToPlt(fstream& File) const;

			void ExportParametricBoundaryToPlt(fstream& File) const;

		private:

			void RemoveDegeneracy(const MetricMap_ApproxSurfaceMetric& Metric, GeoLib::Entity_StaticChain2d& Repaired, const Standard_Real Degeneracy);

			TColMesh2d_HAry1dOfEdge RemoveDegeneracy2(const MetricMap_ApproxSurfaceMetric& theApproxMetric, const MetricMap_ExactSurfaceMetric theExactMetric, const Mesh2d_SizeMap& theSizeMap, const Mesh2d_SizeMap& theBoundarySizeMap, const Standard_Real theDegeneracy);
		};
	}
}

#include <Mesh3d_SurfaceMesherI.hxx>

#endif // !_Mesh3d_SurfaceMesher_Header
