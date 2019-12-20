#pragma once
inline
Standard_Real AutLib::MeshLib::Mesh_SurfaceCurvatureValues::SpanAngle() const
{
	return theSpanAngle_;
}

inline 
AutLib::MeshLib::Mesh_SurfaceCurvatureInfo AutLib::MeshLib::Mesh_SurfaceCurvatureValues::CurvatureInfo() const
{
	return theCurvatureInfo_;
}