#pragma once
inline
Standard_Real AutLib::MeshLib::Mesh_ReferenceValues::BaseSize() const
{
	return theBaseSize_;
}

inline 
AutLib::MeshLib::Mesh_VariationRateInfo AutLib::MeshLib::Mesh_ReferenceValues::DefaultGrowthRate() const
{
	return theDefaultGrowthRate_;
}

inline 
const AutLib::MeshLib::Mesh_SurfaceSizeValues & AutLib::MeshLib::Mesh_ReferenceValues::SurfaceSize() const
{
	return theSurfaceSize_;
}

inline 
const AutLib::MeshLib::Mesh_SurfaceCurvatureValues & AutLib::MeshLib::Mesh_ReferenceValues::SurfaceCurvature() const
{
	return theSurfaceCurvature_;
}

inline 
AutLib::MeshLib::Mesh_SurfaceSizeValues & AutLib::MeshLib::Mesh_ReferenceValues::SurfaceSize()
{
	return theSurfaceSize_;
}

inline 
AutLib::MeshLib::Mesh_SurfaceCurvatureValues & AutLib::MeshLib::Mesh_ReferenceValues::SurfaceCurvature()
{
	return theSurfaceCurvature_;
}