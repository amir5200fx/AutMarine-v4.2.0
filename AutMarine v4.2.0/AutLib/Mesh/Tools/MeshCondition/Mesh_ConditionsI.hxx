#pragma once
inline
Standard_Boolean AutLib::MeshLib::Mesh_Conditions::CustomBoundaryGrowthRate() const
{
	return CustomBoundaryGrowthRate_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh_Conditions::CustomSurfaceSize() const
{
	return CustomSurfaceSize_;
}

inline
AutLib::MeshLib::Mesh_SurfaceCurvatureInfo AutLib::MeshLib::Mesh_Conditions::CustomSurfaceCurvature() const
{
	return theCustomSurfaceCurvature_;
}