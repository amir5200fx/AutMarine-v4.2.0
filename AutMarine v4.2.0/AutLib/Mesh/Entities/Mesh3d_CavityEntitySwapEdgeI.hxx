#pragma once
#include <Global_Macros.hxx>
inline
const Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_CavityEntitySwapEdge::Edge() const
{
	return theEdge_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_CavityEntitySwapEdge::Angle() const
{
	return theAngle_;
}