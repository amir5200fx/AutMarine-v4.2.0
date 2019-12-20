#pragma once
inline
Standard_Integer AutLib::CadLib::Cad3d_WireOnPlane::Index() const
{
	return theIndex_;
}

inline
AutLib::CadLib::Cad3d_WireOnPlaneOrientationInfo AutLib::CadLib::Cad3d_WireOnPlane::Orientation() const
{
	return theOrientation_;
}

inline 
const M_AUT TColCad3d_HAry1dOfEdgeOnPlane & AutLib::CadLib::Cad3d_WireOnPlane::Edges() const
{
	return theEdges_;
}

inline 
const M_GEO Entity_Box2d & AutLib::CadLib::Cad3d_WireOnPlane::BoundingBox() const
{
	return theBox_;
}