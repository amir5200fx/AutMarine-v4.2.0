#pragma once
inline
const AutLib::TColCad3d_HAry1dOfSurfaceOnSolid & AutLib::CadLib::Cad3d_ShellOnSolid::Surfaces() const
{
	return theSurfaces_;
}

inline 
Standard_Integer AutLib::CadLib::Cad3d_ShellOnSolid::NbSurfaces() const
{
	return theSurfaces_.Size();
}

inline 
Standard_Integer AutLib::CadLib::Cad3d_ShellOnSolid::Index() const
{
	return theIndex_;
}

inline 
const M_GEO Entity_Box3d & AutLib::CadLib::Cad3d_ShellOnSolid::BoundingBox() const
{
	return theBox_;
}