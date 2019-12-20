#pragma once
inline
Standard_Integer AutLib::GeoLib::Entity_Triangulation3d::NbPoints() const
{
	return thePoints_.Size();
}

inline 
Standard_Integer AutLib::GeoLib::Entity_Triangulation3d::NbTriangles() const
{
	return theTriangles_.Size();
}

inline 
const M_GEO Entity_TriangleIndex & AutLib::GeoLib::Entity_Triangulation3d::Triangle(const Standard_Integer Index) const
{
	Debug_Bad_Index_Array1(Index, theTriangles_);
	return theTriangles_[Index];
}

inline 
const M_AUT TColGeom_Ary1dOfPnt3d & AutLib::GeoLib::Entity_Triangulation3d::Points() const
{
	return thePoints_;
}

inline 
M_AUT TColGeom_Ary1dOfPnt3d & AutLib::GeoLib::Entity_Triangulation3d::Points()
{
	return thePoints_;
}

inline 
const M_AUT TColEntity_Ary1dOfTriangleIndex & AutLib::GeoLib::Entity_Triangulation3d::Triangles() const
{
	return theTriangles_;
}

inline 
M_AUT TColEntity_Ary1dOfTriangleIndex & AutLib::GeoLib::Entity_Triangulation3d::Triangles()
{
	return theTriangles_;
}