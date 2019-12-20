#pragma once
inline
AutLib::GeoLib::Entity_Node3d::Entity_Node3d()
	: IsOnBoundary_(Standard_False)
{
}

inline
AutLib::GeoLib::Entity_Node3d::Entity_Node3d
(
	const Standard_Integer Index,
	const Geom_Pnt3d & Coord
)
	: theIndex_(Index)
	, theCoord_(Coord)
	, IsOnBoundary_(Standard_False)
{
}

inline
void AutLib::GeoLib::Entity_Node3d::SetIndex(const Standard_Integer Index)
{
	theIndex_ = Index;
}

inline
void AutLib::GeoLib::Entity_Node3d::SetCoord(const Geom_Pnt3d & Coord)
{
	theCoord_ = Coord;
}

inline
void AutLib::GeoLib::Entity_Node3d::SetAsBoundary()
{
	IsOnBoundary_ = Standard_True;
}

inline
void AutLib::GeoLib::Entity_Node3d::Edges(TColEntity_HAry1dOfEdge3d & Edges) const
{
	theEdges_.RetrieveTo(Edges);
}

inline 
void AutLib::GeoLib::Entity_Node3d::Facets(TColEntity_HAry1dOfFacet & Facets) const
{
	theFacets_.RetrieveTo(Facets);
}

inline
void AutLib::GeoLib::Entity_Node3d::Elements(TColEntity_HAry1dOfElement3d & Elements) const
{
	theElements_.RetrieveTo(Elements);
}

inline
void AutLib::GeoLib::Entity_Node3d::InsertToEdges(Global_Handle(Entity_Edge3d) Edge)
{
	theEdges_.EnQueue(Edge);
}

inline 
void AutLib::GeoLib::Entity_Node3d::InsertToFacets(Global_Handle(Entity_Facet) Facet)
{
	theFacets_.EnQueue(Facet);
}

inline
void AutLib::GeoLib::Entity_Node3d::InsertToElements(Global_Handle(Entity_Element3d) Element)
{
	theElements_.EnQueue(Element);
}

inline
Standard_Integer AutLib::GeoLib::Entity_Node3d::Index() const
{
	return theIndex_;
}

inline
Standard_Integer AutLib::GeoLib::Entity_Node3d::NbEdges() const
{
	return theEdges_.Size();
}

inline 
Standard_Integer AutLib::GeoLib::Entity_Node3d::NbFacets() const
{
	return theFacets_.Size();
}

inline
Standard_Integer AutLib::GeoLib::Entity_Node3d::NbElements() const
{
	return theElements_.Size();
}

inline
const M_GEO Geom_Pnt3d & AutLib::GeoLib::Entity_Node3d::Coord() const
{
	return theCoord_;
}

inline
M_AUT TColEntity_HAry1dOfEdge3d AutLib::GeoLib::Entity_Node3d::Edges() const
{
	return theEdges_.Retrive();
}

inline 
M_AUT TColEntity_HAry1dOfFacet AutLib::GeoLib::Entity_Node3d::Facets() const
{
	return theFacets_.Retrive();
}

inline
M_AUT TColEntity_HAry1dOfElement3d AutLib::GeoLib::Entity_Node3d::Elements() const
{
	return theElements_.Retrive();
}