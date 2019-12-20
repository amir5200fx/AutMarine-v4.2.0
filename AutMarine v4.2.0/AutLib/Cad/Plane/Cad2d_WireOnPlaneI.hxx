#pragma once
inline
Standard_Integer AutLib::CadLib::Cad2d_WireOnPlane::Index() const
{
	return theIndex_;
}

inline 
M_CAD Cad2d_WireOnPlaneOrientationInfo AutLib::CadLib::Cad2d_WireOnPlane::Orientation() const
{
	return theOrientation_;
}

inline 
const M_AUT TColCad2d_HAry1dOfEdgeOnPlane & AutLib::CadLib::Cad2d_WireOnPlane::Edges() const
{
	return theEdges_;
}