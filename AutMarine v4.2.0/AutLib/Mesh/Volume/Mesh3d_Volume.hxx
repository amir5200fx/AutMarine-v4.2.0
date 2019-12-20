#pragma once
#ifndef _Mesh3d_Volume_Header
#define _Mesh3d_Volume_Header

#include <Mesh3d_TMesh.hxx>
#include <TColMesh3d_HAry1dOfTMesh.hxx>
#include <TColMesh3d_HAry1dOfSolidMesher.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_SizeMap;

		class Mesh3d_Volume
		{

		protected:

			TColMesh3d_HAry1dOfTMesh theMeshes_;

			TColMesh3d_HAry1dOfSolidMesher theDomains_;

			Standard_Integer theCurrent_;

		public:

			Mesh3d_Volume();

			virtual ~Mesh3d_Volume();

			Global_Handle(Mesh3d_Mesh) Mesh(const Standard_Integer Index) const;

			Global_Handle(Mesh3d_TMesh) CurrentMesh() const;

			Global_Handle(Mesh3d_TMesh)& CurrentMesh();

			Global_Handle(Mesh3d_SolidMesher) Domain(const Standard_Integer Index) const;

			Standard_Integer NbMeshes() const;

			Standard_Integer Current() const;

			Standard_Integer NbElements() const;

			Standard_Integer NbFacets() const;

			Standard_Integer NbEdges() const;

			Standard_Integer NbNodes() const;

			void SetCurrent(const Standard_Integer Value);

			void ExportCavitiesToPlt(fstream& File) const;

			void ExportToPlt(fstream & File) const;

			void ExportDomainToPlt(fstream& File) const;

			void ExportIndependentPatchesToPlt(fstream& File) const;

			void ExportQualityToPlt(fstream& File, const QualityMap3d_TypesInfo theQualityType = QualityMap3d_TypesInfo::QualityMap3d_VLRMS3RATIO) const;

			void ExportBoundaryQualityMeshToPlt(fstream& File) const;

			void ReportQuality(const QualityMap3d_TypesInfo theQualityType = QualityMap3d_TypesInfo::QualityMap3d_VLRMS3RATIO, Standard_OStream& Ostream = cout) const;

			void ReleaseMemory();

		protected:

			void AllocateMemory(const Standard_Integer N);

		};
	}
}

#include <Mesh3d_VolumeI.hxx>

#endif // !_Mesh3d_Volume_Header
