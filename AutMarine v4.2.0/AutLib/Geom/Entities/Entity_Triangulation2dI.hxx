#pragma once
inline
Standard_Integer AutLib::GeoLib::Entity_Triangulation2d::NbPoints() const
{
	return thePoints_.Size();
}

inline 
Standard_Integer AutLib::GeoLib::Entity_Triangulation2d::NbTriangles() const
{
	return theTriangles_.Size();
}

inline 
const M_AUT TColGeom_Ary1dOfPnt2d & AutLib::GeoLib::Entity_Triangulation2d::Points() const
{
	return thePoints_;
}

inline 
M_AUT TColGeom_Ary1dOfPnt2d & AutLib::GeoLib::Entity_Triangulation2d::Points()
{
	return thePoints_;
}

inline 
const M_AUT TColEntity_Ary1dOfTriangleIndex & AutLib::GeoLib::Entity_Triangulation2d::Triangles() const
{
	return theTriangles_;
}

inline 
M_AUT TColEntity_Ary1dOfTriangleIndex & AutLib::GeoLib::Entity_Triangulation2d::Triangles()
{
	return theTriangles_;
}