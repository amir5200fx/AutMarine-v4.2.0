#pragma once
#ifndef _Mesh3d_Region_Header
#define _Mesh3d_Region_Header

#include <QualityMap3d_TypesInfo.hxx>
#include <SizeMap3d_IsoBackSizeType.hxx>
#include <Mesh3d_BoundarySizeMapControl.hxx>
#include <Mesh3d_VolumetricSizeMapControl.hxx>

namespace AutLib
{

	namespace CadLib
	{
		class Cad3d_Solid;
	}

	namespace MeshLib
	{

		class Mesh_ReferenceValues;
		class Mesh3d_SizeMap;
		class Mesh3d_Volume;

		class Mesh3d_Region
		{

		private:

			const Global_Handle(Mesh_ReferenceValues) theReference_;

			const Global_Handle(M_CAD Cad3d_Solid) theSolid_;

			Mesh3d_BoundarySizeMapControl theBoundaries_;
			Mesh3d_VolumetricSizeMapControl theVolumetric_;

			Global_Handle(Mesh3d_SizeMap) theSizeMap_;
			Global_Handle(Mesh3d_Volume) theMesh_;

			SizeMap3d_IsoBackSizeType theSizeMapType_;
			QualityMap3d_TypesInfo theQualityType_;

			Standard_Boolean IsDone_;
			Standard_Boolean SurfaceMeshOnly_;
			Standard_Boolean UseExactMetricForSurfaceMeshing_;

			Standard_Integer theVerbose_;

		public:

			Mesh3d_Region(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad3d_Solid) theSolid);

			const Mesh3d_BoundarySizeMapControl& Boundaries() const;

			const Mesh3d_VolumetricSizeMapControl& Volumetric() const;

			Mesh3d_BoundarySizeMapControl& Boundaries();

			Mesh3d_VolumetricSizeMapControl& Volumetric();

			SizeMap3d_IsoBackSizeType& BackSizeType();

			QualityMap3d_TypesInfo& QualityType();

			Standard_Boolean IsDone() const;

			const Global_Handle(Mesh3d_Volume) Mesh() const;

			void Perform();

			void SetVerbosity(const Standard_Integer theVerbose);

			void SetToSurfaceMeshOnly();

			void SetToUseExactMetricForSurfaceMeshing();

			void ExportQualityToPlt(fstream& File) const;

			void ExportBoundaryQualityMeshToPlt(fstream& File) const;

			//void ExportNormalsOfSurfaces(fstream& File) const;

			void ExportSizeMap(fstream& File) const;

		private:

			void CreateSizeMap();
		};
	}
}

#include <Mesh3d_RegionI.hxx>

#endif // !_Mesh3d_Region_Header
