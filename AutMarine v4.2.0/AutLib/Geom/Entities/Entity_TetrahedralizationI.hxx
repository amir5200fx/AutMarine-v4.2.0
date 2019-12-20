#pragma once
inline
Standard_Integer AutLib::GeoLib::Entity_Tetrahedralization::NbPoints() const
{
	return thePoints_.Size();
}

inline 
Standard_Integer AutLib::GeoLib::Entity_Tetrahedralization::NbTetrahedrons() const
{
	return theTetrahedros_.Size();
}

inline 
const M_AUT TColGeom_Ary1dOfPnt3d & AutLib::GeoLib::Entity_Tetrahedralization::Points() const
{
	return thePoints_;
}

inline 
M_AUT TColGeom_Ary1dOfPnt3d & AutLib::GeoLib::Entity_Tetrahedralization::Points()
{
	return thePoints_;
}

inline 
const M_AUT TColEntity_Ary1dOfTetrahedronIndex & AutLib::GeoLib::Entity_Tetrahedralization::Tetrahedrons() const
{
	return theTetrahedros_;
}

inline 
M_AUT TColEntity_Ary1dOfTetrahedronIndex & AutLib::GeoLib::Entity_Tetrahedralization::Tetrahedrons()
{
	return theTetrahedros_;
}