#pragma once
#ifndef _Mesh2d_Region_Header
#define _Mesh2d_Region_Header

#include <SizeMap2d_IsoBackSizeType.hxx>
#include <SizeMap2d_AnIsoBackSizeType.hxx>
#include <Mesh2d_BoundarySizeMapControl.hxx>
#include <Mesh2d_FeatureSizeMapControl.hxx>
#include <Mesh2d_VolumetricSizeMapControl.hxx>

namespace AutLib
{

	namespace CadLib
	{
		class Cad2d_Plane;
	}

	namespace MeshLib
	{

		class Mesh_ReferenceValues;
		class Mesh2d_SizeMap;
		class Mesh2d_MetricMap;
		class Mesh2d_Plane;

		class Mesh2d_Region
		{

		private:

			const Global_Handle(Mesh_ReferenceValues) theReference_;

			const Global_Handle(M_CAD Cad2d_Plane) thePlane_;

			Mesh2d_BoundarySizeMapControl theBoundaries_;

			Mesh2d_FeatureSizeMapControl theFeatures_;

			Mesh2d_VolumetricSizeMapControl theVolumetrics_;

			Global_Handle(Mesh2d_SizeMap) theSizeMap_;
			Global_Handle(Mesh2d_MetricMap) theMetricMap_;
			Global_Handle(Mesh2d_Plane) theMesh_;

			SizeMap2d_IsoBackSizeType theSizeMapType_;
			SizeMap2d_AnIsoBackSizeType theAnIsoSizeMapType_;

			Standard_Boolean IsDone_;
			Standard_Boolean IsAnIsotropic_;

			Standard_Integer theVerbose_;

		public:

			Mesh2d_Region(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad2d_Plane) thePlane);

			const Mesh2d_BoundarySizeMapControl& Boundaries() const;

			const Mesh2d_FeatureSizeMapControl& Features() const;

			const Mesh2d_VolumetricSizeMapControl& Volumetrics() const;

			Mesh2d_BoundarySizeMapControl& Boundaries();

			Mesh2d_FeatureSizeMapControl& Features();

			Mesh2d_VolumetricSizeMapControl& Volumetrics();

			SizeMap2d_IsoBackSizeType& Type();

			Standard_Boolean IsDone() const;

			const Global_Handle(Mesh2d_Plane) Mesh() const;

			void SetIsoSizeMapType(const SizeMap2d_IsoBackSizeType theIsoSizeMapType);

			void SetAnIsoSizeMapType(const SizeMap2d_AnIsoBackSizeType theAnIsoSizeMapType);

			void Perform();

			void SetVerbosity(const Standard_Integer theVerbose);

			void ExportQualityToPlt(fstream& File) const;

		private:

			void CreateSizeMap();

			void CreateMetricMap();
		};
	}
}

#include <Mesh2d_RegionI.hxx>

#endif // !_Mesh2d_Region_Header
