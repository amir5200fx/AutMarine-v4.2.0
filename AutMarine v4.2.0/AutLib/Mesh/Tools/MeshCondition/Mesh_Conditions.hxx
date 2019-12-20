#pragma once
#ifndef _Mesh_Conditions_Header
#define _Mesh_Conditions_Header

#include <Standard_TypeDef.hxx>
#include <Mesh_SurfaceCurvatureInfo.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh_Conditions
		{

		private:

			Standard_Boolean CustomBoundaryGrowthRate_;
			Standard_Boolean CustomSurfaceSize_;

			Mesh_SurfaceCurvatureInfo theCustomSurfaceCurvature_;

		public:

			Mesh_Conditions();

			void SetCustomBoundaryGrowthRate(const Standard_Boolean CustomBoundaryGrowthRate);

			void SetCustomSurfaceSize(const Standard_Boolean CustomSurfaceSize);

			void SetCustomSurfaceCurvature(const Mesh_SurfaceCurvatureInfo SurfaceCurvatureInfo);

			Standard_Boolean CustomBoundaryGrowthRate() const;

			Standard_Boolean CustomSurfaceSize() const;

			Mesh_SurfaceCurvatureInfo CustomSurfaceCurvature() const;
		};
	}
}

#include <Mesh_ConditionsI.hxx>

#endif // !_Mesh_Conditions_Header
