#pragma once
inline
Standard_Real AutLib::GeoLib::GeoMesh_BackGroundMesh2d::ElementSize(const Geom_Pnt2d & theCoord) const
{
	Standard_Boolean Sense;

	Standard_Real Size = ElementSize(theCoord, Sense);

	if (NOT Sense)
	{
		THROW_STANDARD_EXCEPTION(" Element not found");
		return -1;
	}
	return Size;
}

inline 
Standard_Real AutLib::GeoLib::GeoMesh_BackGroundMesh2d::ElementSize
(
	const Geom_Pnt2d & theCoord,
	Standard_Boolean & Sense
) const
{
	Global_Handle(Entity_Element2d) ElementPtr = theMesh_.TriangleLocation(theCurrentElement_, theCoord);

	if (NOT ElementPtr)
	{
		Sense = Standard_False;
		return -1;
	}

	theCurrentElement_ = ElementPtr;

	const Entity_Element2d& Element = *ElementPtr;

	Standard_Real A1 = Geometry_Tools::AreaOfTriangleAdapt(Element.Node1()->Coord(), Element.Node2()->Coord(), theCoord);
	Standard_Real A2 = Geometry_Tools::AreaOfTriangleAdapt(Element.Node2()->Coord(), Element.Node0()->Coord(), theCoord);
	Standard_Real A3 = Geometry_Tools::AreaOfTriangleAdapt(Element.Node0()->Coord(), Element.Node1()->Coord(), theCoord);

	Standard_Real H1 = theSources_[Index_Of(Element.Node0()->Index())];
	Standard_Real H2 = theSources_[Index_Of(Element.Node1()->Index())];
	Standard_Real H3 = theSources_[Index_Of(Element.Node2()->Index())];

	Sense = Standard_True;

	return (A1*H1 + A2*H2 + A3*H3) / (A1 + A2 + A3);
}

inline 
Standard_Real AutLib::GeoLib::GeoMesh_BackGroundMesh2d::Length(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2) const
{
	Standard_Real H1 = ElementSize(P1);
	/*Standard_Real H2 = ElementSize(P2);

	if (ABS(H2 - H1) <= Precision::Confusion())
	{
	return Distance(P1, P2) / H1;
	}

	Standard_Real Coeff=(H2-H1)/ (H2*H1*log10(H2 / H1));

	return Coeff*Distance(P1, P2);*/

	return (1.0 / H1)*Distance(P1, P2);
}

inline
M_GEO GeoMesh_TriangleMesh2d & AutLib::GeoLib::GeoMesh_BackGroundMesh2d::Mesh()
{
	return theMesh_;
}

inline 
const M_GEO GeoMesh_TriangleMesh2d & AutLib::GeoLib::GeoMesh_BackGroundMesh2d::Mesh() const
{
	return theMesh_;
}

inline
const Global_Handle(M_GEO Entity_Box2d) AutLib::GeoLib::GeoMesh_BackGroundMesh2d::BoundingBox() const
{
	return theBoundingBox_;
}

inline 
M_AUT TColStd_Ary1dOfReal & AutLib::GeoLib::GeoMesh_BackGroundMesh2d::Sources() const
{
	return theSources_;
}