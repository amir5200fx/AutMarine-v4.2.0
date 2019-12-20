#pragma once
inline
void AutLib::MeshLib::SizeMap2d_UnionSizeMaps::ImportSizeMap(const Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) theBack)
{
	theSizeMaps_.EnQueue((Global_Handle(M_GEO GeoMesh_BackGroundMesh2d))theBack);
}

inline
Standard_Boolean AutLib::MeshLib::SizeMap2d_UnionSizeMaps::IsDone() const
{
	return IsDone_;
}

inline 
Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) AutLib::MeshLib::SizeMap2d_UnionSizeMaps::BackGroundMesh() const
{
	return theBackMesh_;
}