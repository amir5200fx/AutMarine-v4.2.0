#pragma once
inline
Standard_Integer AutLib::MeshLib::Mesh3d_CavityEntity::Index() const
{
	return theIndex_;
}

inline
const Global_Handle(AutLib::MeshLib::Mesh3d_CavityShell) AutLib::MeshLib::Mesh3d_CavityEntity::Cavity() const
{
	return theCavity_;
}