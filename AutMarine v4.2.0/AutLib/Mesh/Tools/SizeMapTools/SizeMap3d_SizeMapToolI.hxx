#pragma once
inline
const M_MESH Mesh_Values & AutLib::MeshLib::SizeMap3d_SizeMapTool::MeshValues() const
{
	return theValues_;
}

inline 
const M_MESH Mesh_Conditions & AutLib::MeshLib::SizeMap3d_SizeMapTool::MeshConditions() const
{
	return theConditions_;
}

inline 
const Global_Handle(M_CAD Cad3d_Solid) AutLib::MeshLib::SizeMap3d_SizeMapTool::Solid() const
{
	return theSolid_;
}

inline 
M_MESH Mesh_Values & AutLib::MeshLib::SizeMap3d_SizeMapTool::MeshValues()
{
	return theValues_;
}

inline 
M_MESH Mesh_Conditions & AutLib::MeshLib::SizeMap3d_SizeMapTool::MeshConditions()
{
	return theConditions_;
}

inline 
Global_Handle(M_GEO GeoMesh_BackGroundMesh3d) AutLib::MeshLib::SizeMap3d_SizeMapTool::BackGroundMesh() const
{
	return theBackMesh_;
}