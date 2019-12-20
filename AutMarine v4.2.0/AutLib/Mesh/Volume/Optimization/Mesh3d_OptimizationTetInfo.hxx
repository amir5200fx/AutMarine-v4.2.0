#pragma once
#ifndef _Mesh3d_OptimizationTetInfo_Header
#define _Mesh3d_OptimizationTetInfo_Header

#include <Geom_Pnt3d.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_Element;

		class Mesh3d_OptimizationTetInfo
		{

		private:

			const Mesh3d_Element& theElement_;

			Standard_Real theVolume_;
			Standard_Real theQuality_;
			Standard_Real theFaceArea_[4];

			Geom_Pnt3d theVolumeGrad_;
			Geom_Pnt3d theQualityGrad_;
			Geom_Pnt3d theFaceAreaGrad_[4];

		public:

			Mesh3d_OptimizationTetInfo(const Mesh3d_Element& theElement);

			Standard_Real Volume() const;

			Standard_Real Quality() const;

			Standard_Real FaceArea(const Standard_Integer theIndex) const;

			const Geom_Pnt3d& VolumeGradient() const;

			const Geom_Pnt3d& QualityGradient() const;

			const Geom_Pnt3d& FaceAreaGradient(const Standard_Integer theIndex) const;

			const Mesh3d_Element& Element() const;

			void SetVolume(const Standard_Real theVolume);

			void SetQuality(const Standard_Real theQuality);

			void SetFaceArea(const Standard_Integer theIndex, const Standard_Real theArea);

			void SetVolumeGradient(const Geom_Pnt3d& theVolumeGrad);

			void SetQualityGradient(const Geom_Pnt3d& theQualityGrad);

			void SetFaceAreaGradient(const Standard_Integer theIndex, const Geom_Pnt3d& theAreaGrad);

		};
	}
}

#include <Mesh3d_OptimizationTetInfoI.hxx>

#endif // !_Mesh3d_OptimizationTetInfo_Header
