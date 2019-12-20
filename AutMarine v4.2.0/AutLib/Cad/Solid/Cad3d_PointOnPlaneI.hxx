#pragma once
inline
Standard_Integer AutLib::CadLib::Cad3d_PointOnPlane::NbEdges() const
{
	return theEdges_.Size();
}

inline
Standard_Integer AutLib::CadLib::Cad3d_PointOnPlane::Index() const
{
	return theIndex_;
}

inline 
Standard_Boolean AutLib::CadLib::Cad3d_PointOnPlane::IsFree() const
{
	return NbEdges() EQUAL 1;
}

inline 
Standard_Boolean AutLib::CadLib::Cad3d_PointOnPlane::IsOrphan() const
{
	return theEdges_.IsEmpty();
}

inline 
const Geom_Pnt2d & AutLib::CadLib::Cad3d_PointOnPlane::Coord() const
{
	return theCoord_;
}