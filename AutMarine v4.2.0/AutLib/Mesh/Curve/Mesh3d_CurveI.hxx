#pragma once
inline
const M_GEO Entity_StaticChain3d & AutLib::MeshLib::Mesh3d_Curve::Chain() const
{
	return theChain_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Curve::IsDone() const
{
	return IsDone_;
}