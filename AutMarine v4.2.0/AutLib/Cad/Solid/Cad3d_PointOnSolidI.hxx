#pragma once
inline
Standard_Integer AutLib::CadLib::Cad3d_PointOnSolid::NbEdges() const
{
	return theEdges_.Size();
}

inline 
Standard_Integer AutLib::CadLib::Cad3d_PointOnSolid::NbSurfaces() const
{
	return theSurfaces_.Size();
}

inline 
const Geom_Pnt3d & AutLib::CadLib::Cad3d_PointOnSolid::Coord() const
{
	return theCoord_;
}

inline 
void AutLib::CadLib::Cad3d_PointOnSolid::InsertToEdges(Global_Handle(Cad3d_EdgeOnSolid) Edge)
{
	theEdges_.Insert(Edge);
}

inline 
void AutLib::CadLib::Cad3d_PointOnSolid::InsertToSurfaces(Global_Handle(Cad3d_SurfaceOnSolid) Surface)
{
	theSurfaces_.Insert(Surface);
}

inline 
void AutLib::CadLib::Cad3d_PointOnSolid::InsertToSurfacesIgnoreDup(Global_Handle(Cad3d_SurfaceOnSolid) Surface)
{
	theSurfaces_.InsertIgnoreDup(Surface);
}

inline
void AutLib::CadLib::Cad3d_PointOnSolid::RetrieveEdgesTo(TColCad3d_HAry1dOfEdgeOnSolid & Edges) const
{
	theEdges_.RetrieveTo(Edges);
}

inline 
void AutLib::CadLib::Cad3d_PointOnSolid::RetrieveSurfacesTo(TColCad3d_HAry1dOfSurfaceOnSolid & Surfaces) const
{
	theSurfaces_.RetrieveTo(Surfaces);
}