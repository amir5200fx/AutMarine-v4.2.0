#pragma once
inline
Standard_Integer AutLib::FvmLib::FvmMesh_Node2d::Index() const
{
	return theIndex_;
}

inline
const Geom_Pnt2d & AutLib::FvmLib::FvmMesh_Node2d::Coord() const
{
	return theCoord_;
}