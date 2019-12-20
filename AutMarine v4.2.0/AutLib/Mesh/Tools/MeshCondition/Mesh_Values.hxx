#pragma once
#ifndef _Mesh_Values_Header
#define _Mesh_Values_Header

#include <Mesh_SurfaceCurvatureValues.hxx>
#include <Mesh_SurfaceSizeValues.hxx>
#include <Mesh_VariationRateInfo.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh_Values
		{

		private:

			Mesh_VariationRateInfo theBoundaryGrowthRate_;

			Mesh_SurfaceSizeValues theSurfaceSize_;

			Mesh_SurfaceCurvatureValues theCurvature_;

		public:

			Mesh_Values();

			Mesh_VariationRateInfo BoundaryGrowthRate() const;

			const Mesh_SurfaceSizeValues& SurfaceSize() const;

			const Mesh_SurfaceCurvatureValues& SurfaceCurvature() const;

			Mesh_SurfaceSizeValues& SurfaceSize();

			Mesh_SurfaceCurvatureValues& SurfaceCurvature();

			void SetBoundaryGrowthRate(const Mesh_VariationRateInfo BoundaryGrowthRate);
		};
	}
}

#include <Mesh_ValuesI.hxx>

#endif // !_Mesh_Values_Header
