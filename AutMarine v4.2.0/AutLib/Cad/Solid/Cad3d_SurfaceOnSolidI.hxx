#pragma once
inline 
Standard_Integer AutLib::CadLib::Cad3d_SurfaceOnSolid::NbEdges() const
{
	return theEdges_.Size();
}

inline 
Standard_Real AutLib::CadLib::Cad3d_SurfaceOnSolid::Umin() const
{
	return theUmin_;
}

inline 
Standard_Real AutLib::CadLib::Cad3d_SurfaceOnSolid::Umax() const
{
	return theUmax_;
}

inline 
Standard_Real AutLib::CadLib::Cad3d_SurfaceOnSolid::Vmin() const
{
	return theVmin_;
}

inline 
Standard_Real AutLib::CadLib::Cad3d_SurfaceOnSolid::Vmax() const
{
	return theVmax_;
}

inline 
Standard_Boolean AutLib::CadLib::Cad3d_SurfaceOnSolid::HasTriangulation() const
{
	return NOT theTriangulation_.IsNull();
}

inline 
M_CAD Cad3d_SurfaceOrientationInfo AutLib::CadLib::Cad3d_SurfaceOnSolid::Orientation() const
{
	return theOrientation_;
}

inline 
const Handle(Geom_Surface)& AutLib::CadLib::Cad3d_SurfaceOnSolid::Geometry() const
{
	return theGeom_;
}

inline 
const Handle(Poly_Triangulation)& AutLib::CadLib::Cad3d_SurfaceOnSolid::Triangulation() const
{
	return theTriangulation_;
}

inline 
Global_Handle(M_CAD Cad3d_Plane) AutLib::CadLib::Cad3d_SurfaceOnSolid::Plane() const
{
	return thePlane_;
}

inline 
const AutLib::TColCad3d_HAry1dOfEdgeOnSolid & AutLib::CadLib::Cad3d_SurfaceOnSolid::Edges() const
{
	return theEdges_;
}