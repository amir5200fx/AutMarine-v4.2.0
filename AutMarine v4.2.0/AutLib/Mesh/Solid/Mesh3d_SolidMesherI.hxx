#pragma once
inline
const M_GEO Entity_Triangulation3d & AutLib::MeshLib::Mesh3d_SolidMesher::Merged() const
{
	return theMergedMesh_;
}

inline 
const M_AUT TColMesh3d_HAry1dOfSurfaceMesher & AutLib::MeshLib::Mesh3d_SolidMesher::Algorithm() const
{
	return theMesher_;
}

inline 
M_AUT TColMesh3d_HAry1dOfSurfaceMesher & AutLib::MeshLib::Mesh3d_SolidMesher::Algorithm()
{
	return theMesher_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_SolidMesher::IsDone() const
{
	return IsDone_;
}