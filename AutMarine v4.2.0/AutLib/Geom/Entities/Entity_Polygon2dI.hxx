#pragma once
inline
Standard_Real AutLib::GeoLib::Entity_Polygon2d::Deflection() const
{
	return theDeflection_;
}

inline 
M_GEO Entity_Polygon2d AutLib::GeoLib::Entity_Polygon2d::Reversed() const
{
	Entity_Polygon2d Copy = *this;
	Copy.Reverse();

	MOVE(Copy);
}

inline
Standard_Integer AutLib::GeoLib::Entity_Polygon2d::NbPoints() const
{
	return thePoints_.Size();
}

inline 
Standard_Boolean AutLib::GeoLib::Entity_Polygon2d::IsClosed() const
{
	return Distance(thePoints_.First(), thePoints_.Last()) EQUAL 0;
}

inline 
M_AUT TColGeom_Ary1dOfPnt2d & AutLib::GeoLib::Entity_Polygon2d::Points()
{
	return thePoints_;
}

inline 
Geom_Pnt2d AutLib::GeoLib::Entity_Polygon2d::Point(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, thePoints_);
	return thePoints_.Value(theIndex);
}

inline 
const M_AUT TColGeom_Ary1dOfPnt2d & AutLib::GeoLib::Entity_Polygon2d::Points() const
{
	return thePoints_;
}