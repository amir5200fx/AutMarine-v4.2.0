#pragma once
inline
AutLib::MeshLib::Mesh_VariationRateInfo AutLib::MeshLib::Mesh_Values::BoundaryGrowthRate() const
{
	return theBoundaryGrowthRate_;
}

inline
const AutLib::MeshLib::Mesh_SurfaceSizeValues & AutLib::MeshLib::Mesh_Values::SurfaceSize() const
{
	return theSurfaceSize_;
}

inline
const AutLib::MeshLib::Mesh_SurfaceCurvatureValues & AutLib::MeshLib::Mesh_Values::SurfaceCurvature() const
{
	return theCurvature_;
}

inline
AutLib::MeshLib::Mesh_SurfaceSizeValues & AutLib::MeshLib::Mesh_Values::SurfaceSize()
{
	return theSurfaceSize_;
}

inline
AutLib::MeshLib::Mesh_SurfaceCurvatureValues & AutLib::MeshLib::Mesh_Values::SurfaceCurvature()
{
	return theCurvature_;
}

inline
void AutLib::MeshLib::Mesh_Values::SetBoundaryGrowthRate(const Mesh_VariationRateInfo BoundaryGrowthRate)
{
	theBoundaryGrowthRate_ = BoundaryGrowthRate;
}