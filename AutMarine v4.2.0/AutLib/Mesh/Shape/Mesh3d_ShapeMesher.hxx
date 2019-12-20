#pragma once
#ifndef _Mesh3d_ShapeMesher_Header
#define _Mesh3d_ShapeMesher_Header

#include <Entity_Triangulation3d.hxx>
#include <TColMesh3d_HAry1dOfSurfaceMesher.hxx>

#include <TopoDS_Shape.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_SizeMap;

		class Mesh3d_ShapeMesher
		{

		private:

			TopoDS_Shape theShape_;

			const Mesh3d_SizeMap& theSizeMap_;

			TColMesh3d_HAry1dOfSurfaceMesher theMesh_;

			M_GEO Entity_Triangulation3d theMergedMesh_;

			Standard_Boolean ApplySmoothing_;
			Standard_Boolean UseExactMetric_;
			Standard_Boolean IsDone_;

			Standard_Real theMaxGradation_;
			Standard_Real theSewingTolerance_;

			Standard_String theShapeName_;

		public:

			Mesh3d_ShapeMesher(const Mesh3d_SizeMap& theSizeMap, const TopoDS_Shape& theShape);

			~Mesh3d_ShapeMesher() { ReleaseMemory(); }

			//! Throw an exception if ShapeMesher is not performed
			const M_GEO Entity_Triangulation3d& Mesh() const;

			void ApplyMetricSmoothing(const Standard_Boolean ApplySmoothing);

			//! Usaually set value > 1.0
			void SetMaxMetricGradation(const Standard_Real Gradation);

			void SetSwingTolerance(const Standard_Real Tolerance);

			void SetShapeName(const Standard_String Name);

			void UseExactMetric();

			void Perform();

			//! Throw an exception if ShapeMesher is not performed
			void ExportMeshToPlt(fstream& File);

			void ExportMergedMeshToPlt(fstream& File);

		private:

			void Merging();

			void ConformityOfBoundaries();

			void ReleaseMemory();
		};
	}
}

#include <Mesh3d_ShapeMesherI.hxx>

#endif // !_Mesh3d_ShapeMesher_Header
