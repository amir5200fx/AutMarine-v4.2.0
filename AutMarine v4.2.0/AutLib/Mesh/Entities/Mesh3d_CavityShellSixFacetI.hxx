#pragma once
inline
Global_Handle(M_MESH Mesh3d_Node) AutLib::MeshLib::Mesh3d_CavityShellSixFacet::Vertex0() const
{
	return theVertex0_;
}

inline 
Global_Handle(M_MESH Mesh3d_Node) AutLib::MeshLib::Mesh3d_CavityShellSixFacet::Vertex1() const
{
	return theVertex1_;
}

inline 
const M_AUT TColMesh3d_HAry1dOfNode & AutLib::MeshLib::Mesh3d_CavityShellSixFacet::Equatorial() const
{
	return theEquatorial_;
}