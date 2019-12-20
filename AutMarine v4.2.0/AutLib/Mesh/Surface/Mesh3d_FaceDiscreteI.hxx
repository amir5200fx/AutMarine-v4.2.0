#pragma once
inline
Standard_Boolean AutLib::MeshLib::Mesh3d_FaceDiscrete::IsDone() const
{
	return IsDone_;
}

inline
const M_GEO Entity_Triangulation2d & AutLib::MeshLib::Mesh3d_FaceDiscrete::ParaMesh() const
{
	return theParaMesh_;
}

inline 
const M_GEO Entity_Triangulation3d & AutLib::MeshLib::Mesh3d_FaceDiscrete::SurfaceMesh() const
{
	return theSurfaceMesh_;
}