#pragma once
inline
Standard_Boolean AutLib::MeshLib::Mesh3d_SurfaceMesher::IsDone() const
{
	return IsDone_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_SurfaceMesher::Index() const
{
	return theIndex_;
}

inline 
M_GEO Entity_Triangulation3d & AutLib::MeshLib::Mesh3d_SurfaceMesher::ModifiedSurfaceMesh()
{
	return theModifiedSurfaceMesh_;
}

inline 
const M_GEO Entity_Triangulation3d & AutLib::MeshLib::Mesh3d_SurfaceMesher::ModifiedSurfaceMesh() const
{
	return theModifiedSurfaceMesh_;
}

inline
const M_GEO Entity_Triangulation2d & AutLib::MeshLib::Mesh3d_SurfaceMesher::ParaMesh() const
{
	return theParaMesh_;
}

inline 
const M_GEO Entity_Triangulation3d & AutLib::MeshLib::Mesh3d_SurfaceMesher::SurfaceMesh() const
{
	return theSurfaceMesh_;
}

inline 
const M_GEO Entity_StaticChain3d & AutLib::MeshLib::Mesh3d_SurfaceMesher::Boundary3d() const
{
	return theBoundary3d_;
}