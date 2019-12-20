#pragma once
inline
const M_GEO Entity_Triangulation3d & AutLib::MeshLib::Mesh3d_ShapeDiscrete::Mesh() const
{
	return theMergedMesh_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_ShapeDiscrete::IsDone() const
{
	return IsDone_;
}