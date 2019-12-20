#pragma once
inline
Standard_Integer AutLib::GeoLib::DelTri3d::NbPoints() const
{
	return thePts_.Size();
}

inline 
Standard_Integer AutLib::GeoLib::DelTri3d::NbTetrahedrons() const
{
	return theV_.Size();
}

inline 
const M_AUT TColGeom_Ary1dOfPnt3d & AutLib::GeoLib::DelTri3d::Coords() const
{
	return thePts_;
}

inline 
const M_AUT TColEntity_Ary1dOfTetrahedronIndex & AutLib::GeoLib::DelTri3d::Tetrahedrons() const
{
	return theV_;
}

inline 
const M_AUT TColEntity_Ary1dOfTetrahedronIndex & AutLib::GeoLib::DelTri3d::Neighbors() const
{
	return theE_;
}