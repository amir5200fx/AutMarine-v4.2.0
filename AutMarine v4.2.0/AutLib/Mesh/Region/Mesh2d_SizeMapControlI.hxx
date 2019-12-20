#pragma once
inline
Standard_Integer AutLib::MeshLib::Mesh2d_SizeMapControl::Size() const
{
	return (Standard_Integer)theBoundaries_.size();
}

inline 
const M_AUT TColSizeMap2d_StringMapOfHSizeMapTool & AutLib::MeshLib::Mesh2d_SizeMapControl::Maps() const
{
	return theBoundaries_;
}