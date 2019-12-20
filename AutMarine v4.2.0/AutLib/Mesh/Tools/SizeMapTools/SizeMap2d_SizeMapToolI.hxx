#pragma once
inline
const M_MESH Mesh_Values & AutLib::MeshLib::SizeMap2d_SizeMapTool::MeshValues() const
{
	return theValues_;
}

inline 
const M_MESH Mesh_Conditions & AutLib::MeshLib::SizeMap2d_SizeMapTool::MeshConditions() const
{
	return theConditions_;
}

inline 
const Global_Handle(M_CAD Cad2d_Plane) AutLib::MeshLib::SizeMap2d_SizeMapTool::Plane() const
{
	return thePlane_;
}

inline 
M_MESH Mesh_Values & AutLib::MeshLib::SizeMap2d_SizeMapTool::MeshValues()
{
	return theValues_;
}

inline 
M_MESH Mesh_Conditions & AutLib::MeshLib::SizeMap2d_SizeMapTool::MeshConditions()
{
	return theConditions_;
}

inline 
Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) AutLib::MeshLib::SizeMap2d_SizeMapTool::BackGroundMesh() const
{
	return theBackMesh_;
}

//inline
//Standard_String AutLib::MeshLib::SizeMap2d_SizeMapTool::Name() const
//{
//	return theName_;
//}