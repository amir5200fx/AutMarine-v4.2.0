#pragma once
#include <Geometry_Tools.hxx>
#include <Entity_Facet.hxx>
inline
Standard_Integer AutLib::GeoLib::GeoMesh_TetrahedronMesh::NbNodes() const
{
	Debug_If_Condition(NOT IsDone_);
	return theNodesSequence_.Size();
}

inline 
Standard_Integer AutLib::GeoLib::GeoMesh_TetrahedronMesh::NbEdges() const
{
	Debug_If_Condition(NOT IsDone_);
	return theEdgesSequence_.Size();
}

inline 
Standard_Integer AutLib::GeoLib::GeoMesh_TetrahedronMesh::NbFacets() const
{
	Debug_If_Condition(NOT IsDone_);
	return theFacetsSequence_.Size();
}

inline 
Standard_Integer AutLib::GeoLib::GeoMesh_TetrahedronMesh::NbElements() const
{
	Debug_If_Condition(NOT IsDone_);
	return theElementsSequence_.Size();
}

inline 
Global_Handle(M_GEO Entity_Element3d) AutLib::GeoLib::GeoMesh_TetrahedronMesh::TetrahedronLocation(Global_Handle(Entity_Element3d) ElementPtr, const Geom_Pnt3d & Coord) const
{
	if (NOT ElementPtr) return ElementPtr;

	Get_Const_Object(Element) = *ElementPtr;

	Get_Const_Object(Node0) = *Element.Node0();
	Get_Const_Object(Node1) = *Element.Node1();
	Get_Const_Object(Node2) = *Element.Node2();
	Get_Const_Object(Node3) = *Element.Node3();

	/*cout << Coord << endl;
	cout << Node0.Coord() << endl;
	cout << Node1.Coord() << endl;
	cout << Node2.Coord() << endl;
	cout << Node3.Coord() << endl;
	cout << endl;*/
	
	Standard_Boolean Undefiend;

	if (IsPointRightTriangle(Coord, Node1.Coord(), Node3.Coord(), Node2.Coord(), Element.Characteristic()*EPS6, Undefiend) AND NOT Undefiend)
	{
		return TetrahedronLocation(Element.Neighbor0(), Coord);
	}
	else if (IsPointRightTriangle(Coord, Node2.Coord(), Node3.Coord(), Node0.Coord(), Element.Characteristic()*EPS6, Undefiend) AND NOT Undefiend)
	{
		return TetrahedronLocation(Element.Neighbor1(), Coord);
	}
	else if (IsPointRightTriangle(Coord, Node0.Coord(), Node3.Coord(), Node1.Coord(), Element.Characteristic()*EPS6, Undefiend) AND NOT Undefiend)
	{
		return TetrahedronLocation(Element.Neighbor2(), Coord);
	}
	else if (IsPointRightTriangle(Coord, Node0.Coord(), Node1.Coord(), Node2.Coord(), Element.Characteristic()*EPS6, Undefiend) AND NOT Undefiend)
	{
		return TetrahedronLocation(Element.Neighbor3(), Coord);
	}

	/*if (IsPointRightTriangle(Coord, Node1.Coord(), Node3.Coord(), Node2.Coord()))
	{
		return TetrahedronLocation(Element.Neighbor0(), Coord);
	}
	else if (IsPointRightTriangle(Coord, Node2.Coord(), Node3.Coord(), Node0.Coord()))
	{
		return TetrahedronLocation(Element.Neighbor1(), Coord);
	}
	else if (IsPointRightTriangle(Coord, Node0.Coord(), Node3.Coord(), Node1.Coord()))
	{
		return TetrahedronLocation(Element.Neighbor2(), Coord);
	}
	else if (IsPointRightTriangle(Coord, Node0.Coord(), Node1.Coord(), Node2.Coord()))
	{
		return TetrahedronLocation(Element.Neighbor3(), Coord);
	}*/

	/*if (ElementPtr EQUAL Element.Facet0()->RightElement())
	{
		if (IsPointOnLeftSide(Coord, Element.Facet0())) { return TetrahedronLocation(Element.Neighbor0(), Coord); }
	}
	else if (ElementPtr EQUAL Element.Facet0()->LeftElement())
	{
		if (IsPointOnRightSide(Coord, Element.Facet0())) { return TetrahedronLocation(Element.Neighbor0(), Coord); }
	}
	else { THROW_STANDARD_EXCEPTION(" Conflict Data"); }

	if (ElementPtr EQUAL Element.Facet1()->RightElement())
	{
		if (IsPointOnLeftSide(Coord, Element.Facet1())) { return TetrahedronLocation(Element.Neighbor1(), Coord); }
	}
	else if (ElementPtr EQUAL Element.Facet1()->LeftElement())
	{
		if (IsPointOnRightSide(Coord, Element.Facet1())) { return TetrahedronLocation(Element.Neighbor1(), Coord); }
	}
	else { THROW_STANDARD_EXCEPTION(" Conflict Data"); }

	if (ElementPtr EQUAL Element.Facet2()->RightElement())
	{
		if (IsPointOnLeftSide(Coord, Element.Facet2())) { return TetrahedronLocation(Element.Neighbor2(), Coord); }
	}
	else if (ElementPtr EQUAL Element.Facet2()->LeftElement())
	{
		if (IsPointOnRightSide(Coord, Element.Facet2())) { return TetrahedronLocation(Element.Neighbor2(), Coord); }
	}
	else { THROW_STANDARD_EXCEPTION(" Conflict Data"); }

	if (ElementPtr EQUAL Element.Facet3()->RightElement())
	{
		if (IsPointOnLeftSide(Coord, Element.Facet3())) { return TetrahedronLocation(Element.Neighbor3(), Coord); }
	}
	else if (ElementPtr EQUAL Element.Facet3()->LeftElement())
	{
		if (IsPointOnRightSide(Coord, Element.Facet3())) { return TetrahedronLocation(Element.Neighbor3(), Coord); }
	}
	else { THROW_STANDARD_EXCEPTION(" Conflict Data"); }*/

	// found the Tetrahedron
	return ElementPtr;
}

inline 
Global_Handle(M_GEO Entity_Element3d) AutLib::GeoLib::GeoMesh_TetrahedronMesh::FirstElement() const
{
	return theElementsSequence_[0];
}

inline 
const M_AUT TColEntity_HAry1dOfNode3d & AutLib::GeoLib::GeoMesh_TetrahedronMesh::NodesSequence() const
{
	Debug_If_Condition(NOT IsDone_);
	return theNodesSequence_;
}

inline 
const M_AUT TColEntity_HAry1dOfEdge3d & AutLib::GeoLib::GeoMesh_TetrahedronMesh::EdgesSequence() const
{
	Debug_If_Condition(NOT IsDone_);
	return theEdgesSequence_;
}

inline 
const M_AUT TColEntity_HAry1dOfFacet & AutLib::GeoLib::GeoMesh_TetrahedronMesh::FacetsSequence() const
{
	Debug_If_Condition(NOT IsDone_);
	return theFacetsSequence_;
}

inline 
const M_AUT TColEntity_HAry1dOfElement3d & AutLib::GeoLib::GeoMesh_TetrahedronMesh::ElementsSequence() const
{
	Debug_If_Condition(NOT IsDone_);
	return theElementsSequence_;
}

inline
void AutLib::GeoLib::GeoMesh_TetrahedronMesh::Insert(Global_Handle(Entity_Node3d) Node)
{
	theNodes_.Insert(Node);
}

inline 
void AutLib::GeoLib::GeoMesh_TetrahedronMesh::Insert(Global_Handle(Entity_Edge3d) Edge)
{
	theEdges_.Insert(Edge);
}

inline 
void AutLib::GeoLib::GeoMesh_TetrahedronMesh::Insert(Global_Handle(Entity_Facet) Facet)
{
	theFacets_.Insert(Facet);
}

inline 
void AutLib::GeoLib::GeoMesh_TetrahedronMesh::Insert(Global_Handle(Entity_Element3d) Element)
{
	theElements_.Insert(Element);
}

inline 
void AutLib::GeoLib::GeoMesh_TetrahedronMesh::Remove(Global_Handle(Entity_Node3d) Node)
{
	theNodes_.Remove(Node);
}

inline 
void AutLib::GeoLib::GeoMesh_TetrahedronMesh::Remove(Global_Handle(Entity_Edge3d) Edge)
{
	theEdges_.Remove(Edge);
}

inline 
void AutLib::GeoLib::GeoMesh_TetrahedronMesh::Remove(Global_Handle(Entity_Facet) Facet)
{
	theFacets_.Remove(Facet);
}

inline 
void AutLib::GeoLib::GeoMesh_TetrahedronMesh::Remove(Global_Handle(Entity_Element3d) Element)
{
	theElements_.Remove(Element);
}

inline 
void AutLib::GeoLib::GeoMesh_TetrahedronMesh::RetrieveTo(TColEntity_HAry1dOfNode3d & Nodes) const
{
	Debug_If_Condition(NOT IsDone_);
	theNodes_.RetrieveTo(Nodes);
}

inline 
void AutLib::GeoLib::GeoMesh_TetrahedronMesh::RetrieveTo(TColEntity_HAry1dOfEdge3d & Edges) const
{
	Debug_If_Condition(NOT IsDone_);
	theEdges_.RetrieveTo(Edges);
}

inline 
void AutLib::GeoLib::GeoMesh_TetrahedronMesh::RetrieveTo(TColEntity_HAry1dOfFacet & Facets) const
{
	Debug_If_Condition(NOT IsDone_);
	theFacets_.RetrieveTo(Facets);
}

inline 
void AutLib::GeoLib::GeoMesh_TetrahedronMesh::RetrieveTo(TColEntity_HAry1dOfElement3d & Elements) const
{
	Debug_If_Condition(NOT IsDone_);
	theElements_.RetrieveTo(Elements);
}

inline
Standard_Boolean AutLib::GeoLib::GeoMesh_TetrahedronMesh::IsPointOnRightSide(const Geom_Pnt3d & theCoord, const Global_Handle(Entity_Facet) Facet) const
{
	Get_Const_Object(Norm) = Facet->Normal();
	Get_Const_Object(P0) = Facet->Node0()->Coord();

	return DotProduct(theCoord - P0, Norm) < 0.0;
}

inline 
Standard_Boolean AutLib::GeoLib::GeoMesh_TetrahedronMesh::IsPointOnLeftSide(const Geom_Pnt3d & theCoord, const Global_Handle(Entity_Facet) Facet) const
{
	const Geom_Pnt3d& Norm = Facet->Normal();
	const Geom_Pnt3d& P0 = Facet->Node0()->Coord();

	return DotProduct(theCoord - P0, Norm) > 0.0;
}

inline 
Standard_Boolean AutLib::GeoLib::GeoMesh_TetrahedronMesh::IsPointRightTriangle
(
	const Geom_Pnt3d & theCoord,
	const Geom_Pnt3d & theP1, 
	const Geom_Pnt3d & theP2,
	const Geom_Pnt3d & theP3
) const
{
	Geom_Pnt3d Normal = CrossProduct(theP3 - theP1, theP3 - theP2);

	if (DotProduct((theCoord - theP1), Normal) < 1.0e-8)
	{
		return Standard_True;
	}
	else
	{
		return Standard_False;
	}
}

inline 
Standard_Boolean AutLib::GeoLib::GeoMesh_TetrahedronMesh::IsPointRightTriangle
(
	const Geom_Pnt3d & Point,
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3,
	const Standard_Real Tolerance, 
	Standard_Boolean & Undefiend
) const
{
	Geom_Pnt3d Normal = CrossProduct(P3 - P1, P3 - P2);

	Standard_Real Dot = DotProduct(Point - P1, Normal);

	if (ABS(Dot) > Tolerance)
	{
		Undefiend = Standard_False;

		if (Dot < 0) return Standard_True;
		else return Standard_False;
	}

	if (Geometry_Tools::IsPointOnTriangle(Point, P1, P2, P3, Tolerance))
	{
		Undefiend = Standard_False;

		return Standard_False;
	}

	Undefiend = Standard_True;
	return Standard_False;
}