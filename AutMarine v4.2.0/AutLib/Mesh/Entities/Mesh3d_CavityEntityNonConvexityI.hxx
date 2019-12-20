#pragma once
inline
const Global_Handle(AutLib::MeshLib::Mesh3d_Edge) AutLib::MeshLib::Mesh3d_CavityEntityNonConvexity::Edge() const
{
	return theEdge_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_CavityEntityNonConvexity::Angle() const
{
	return theAngle_;
}