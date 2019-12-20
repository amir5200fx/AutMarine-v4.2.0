#pragma once
inline
Standard_Integer AutLib::GeoLib::Entity_PolyLine3d::NbPoints() const
{
	return thePoints_.Size();
}

inline 
Standard_Real AutLib::GeoLib::Entity_PolyLine3d::Deflection() const
{
	return theDeflection_;
}

inline 
Standard_Boolean AutLib::GeoLib::Entity_PolyLine3d::IsClosed() const
{
	return Distance(thePoints_.First(), thePoints_.Last()) EQUAL 0;
}

inline 
M_GEO Entity_PolyLine3d AutLib::GeoLib::Entity_PolyLine3d::Reversed() const
{
	Entity_PolyLine3d Copy = *this;
	Copy.Reverse();

	MOVE(Copy);
}

inline 
const M_AUT TColGeom_Ary1dOfPnt3d & AutLib::GeoLib::Entity_PolyLine3d::Points() const
{
	return thePoints_;
}

inline 
M_AUT TColGeom_Ary1dOfPnt3d & AutLib::GeoLib::Entity_PolyLine3d::Points()
{
	return thePoints_;
}