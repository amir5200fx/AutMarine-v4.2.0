#pragma once
#ifndef _Mesh3d_SolidMesher_Header
#define _Mesh3d_SolidMesher_Header

#include <Entity_Triangulation3d.hxx>
#include <SizeMap2d_AnIsoBackSizeType.hxx>
#include <TColMesh3d_HAry1dOfSurfaceMesher.hxx>
#include <TColCad3d_HAry1dOfSurfaceOnSolid.hxx>

namespace AutLib
{

	namespace CadLib
	{
		class Cad3d_Solid;
	}

	namespace MeshLib
	{

		class Mesh2d_QualityMap;
		class Mesh3d_SizeMap;

		class Mesh3d_SolidMesher
		{

		private:

			TColMesh3d_HAry1dOfSurfaceMesher theMesher_;

			Standard_Boolean ApplySmoothing_;
			Standard_Boolean ApplyOptimization_;
			Standard_Boolean UseExactMetric_;
			Standard_Boolean IsDone_;

			Standard_Integer theVerbose_;

			Standard_Real theMaxGradation_;
			Standard_Real theSmoothingFactor_;
			Standard_Real theDegeneracy_;

			Standard_String theSolidName_;

			const M_CAD Cad3d_Solid& theSolid_;

			const Mesh3d_SizeMap& theSizeMap_;

			M_GEO Entity_Triangulation3d theMergedMesh_;

			SizeMap2d_AnIsoBackSizeType theAnIsoSizeMapType_;

		public:

			Mesh3d_SolidMesher(const Mesh3d_SizeMap& theSizeMap, const M_CAD Cad3d_Solid& theShape);

			~Mesh3d_SolidMesher();

			const M_GEO Entity_Triangulation3d& Merged() const;

			const TColMesh3d_HAry1dOfSurfaceMesher& Algorithm() const;

			TColMesh3d_HAry1dOfSurfaceMesher& Algorithm();

			Standard_Boolean IsDone() const;

			void ApplyOptimization(const Standard_Boolean ApplyOptimization);

			void ApplySmoothing(const Standard_Boolean ApplySmoothing);

			void SetAnIsoSizeMapType(const SizeMap2d_AnIsoBackSizeType theType);

			void UseExactMetric();

			void SetVerbosity(Standard_Integer theVerbose);

			void Perform();

			void ExportMeshToPlt(fstream& File) const;

			void ExportQualityMeshToPlt(fstream& File, const Mesh2d_QualityMap& theQualityMap) const;

			void ExportMergedMeshToPlt(fstream& File) const;

			void ExportNormalsToPlt(fstream& File) const;

			void ExportMeshTo(fstream& File) const;

		private:

			void ConformBoundaries(const TColCad3d_HAry1dOfSurfaceOnSolid& theSurfaces);

			void Merging();

			void ReleaseMemory();
		};
	}
}

#include <Mesh3d_SolidMesherI.hxx>

#endif // !_Mesh3d_SolidMesher_Header
