#pragma once
inline
void AutLib::MeshLib::SizeMap3d_UnionSizeMaps::ImportSizeMap(const Global_Handle(M_GEO GeoMesh_BackGroundMesh3d) theBack)
{
	theSizeMaps_.EnQueue((Global_Handle(M_GEO GeoMesh_BackGroundMesh3d))theBack);
}

inline
Standard_Boolean AutLib::MeshLib::SizeMap3d_UnionSizeMaps::IsDone() const
{
	return IsDone_;
}

inline 
Standard_Integer AutLib::MeshLib::SizeMap3d_UnionSizeMaps::Size() const
{
	return theSizeMaps_.Size();
}

inline
Global_Handle(M_GEO GeoMesh_BackGroundMesh3d) AutLib::MeshLib::SizeMap3d_UnionSizeMaps::BackGroundMesh() const
{
	return theBackMesh_;
}