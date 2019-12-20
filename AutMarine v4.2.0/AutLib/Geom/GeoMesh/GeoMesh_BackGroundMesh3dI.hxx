#pragma once
inline
Standard_Real AutLib::GeoLib::GeoMesh_BackGroundMesh3d::ElementSize(const Geom_Pnt3d & theCoord) const
{
	Standard_Boolean Sense;

	Standard_Real Size = ElementSize(theCoord, Sense);

	if (Size <= 0)
	{
		THROW_STANDARD_EXCEPTION(" Invalid Element Size");
	}

	if (NOT Sense)
	{
		THROW_STANDARD_EXCEPTION(" Element not found");
		return -1;
	}
	return Size;
}

inline
Standard_Real AutLib::GeoLib::GeoMesh_BackGroundMesh3d::Length
(
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2
) const
{
	Standard_Real H1 = ElementSize(P1);

	return (1.0 / H1)*Distance(P1, P2);
}

inline
M_GEO GeoMesh_TetrahedronMesh & AutLib::GeoLib::GeoMesh_BackGroundMesh3d::Mesh()
{
	return theMesh_;
}

inline
const M_GEO GeoMesh_TetrahedronMesh & AutLib::GeoLib::GeoMesh_BackGroundMesh3d::Mesh() const
{
	return theMesh_;
}

inline 
const Global_Handle(M_GEO Entity_Box3d) AutLib::GeoLib::GeoMesh_BackGroundMesh3d::BoundingBox() const
{
	return theBoundingBox_;
}

inline 
M_AUT TColStd_Ary1dOfReal & AutLib::GeoLib::GeoMesh_BackGroundMesh3d::Sources() const
{
	return theSources_;
}