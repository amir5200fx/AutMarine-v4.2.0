#pragma once
inline
const M_AUT TColCad3d_HAry1dOfEdgeOnPlane & AutLib::CadLib::Cad3d_Plane::Edges() const
{
	return theEdges_;
}

inline 
const M_AUT TColCad3d_HAry1dOfPointOnPlane & AutLib::CadLib::Cad3d_Plane::Corners() const
{
	return theCorners_;
}

inline 
const M_AUT Cad3d_OutterBoundaryOnPlane & AutLib::CadLib::Cad3d_Plane::OutterWire() const
{
	return theOutterWire_;
}

inline 
const M_AUT Cad3d_InnerBoundariesOnPlane & AutLib::CadLib::Cad3d_Plane::InnerWires() const
{
	return theInnerWires_;
}

inline 
const Global_Handle(M_CAD Cad3d_WireOnPlane) AutLib::CadLib::Cad3d_Plane::InnerWire(const Standard_Integer theIndex) const
{
	if (NOT INSIDE(theIndex, 0, NbHoles() - 1)) { THROW_STANDARD_EXCEPTION("Wrong Index"); }
	return theInnerWires_[theIndex];
}

inline 
Standard_Integer AutLib::CadLib::Cad3d_Plane::NbEdges() const
{
	return theEdges_.Size();
}

inline 
Standard_Integer AutLib::CadLib::Cad3d_Plane::NbHoles() const
{
	return theInnerWires_.Size();
}