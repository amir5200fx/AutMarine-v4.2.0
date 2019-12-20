#pragma once
inline
AutLib::GeoLib::Entity_Edge3d::Entity_Edge3d()
	: IsOnBoundary_(Standard_False)
{
}

inline
AutLib::GeoLib::Entity_Edge3d::Entity_Edge3d
(
	const Standard_Integer Index,
	Global_Handle(Entity_Node3d) Node0,
	Global_Handle(Entity_Node3d) Node1
)
	: theIndex_(Index)
{
	theNodes_[0] = Node0;
	theNodes_[1] = Node1;
}

inline
Standard_Integer AutLib::GeoLib::Entity_Edge3d::Index() const
{
	return theIndex_;
}

inline
Standard_Boolean AutLib::GeoLib::Entity_Edge3d::IsOnBoundary() const
{
	return IsOnBoundary_;
}

inline
Global_Handle(M_GEO Entity_Node3d) AutLib::GeoLib::Entity_Edge3d::Node(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 1);
	return theNodes_[Index];
}

inline
Global_Handle(M_GEO Entity_Node3d)& AutLib::GeoLib::Entity_Edge3d::Node(const Standard_Integer Index)
{
	Debug_Bad_Index(Index, 0, 1);
	return theNodes_[Index];
}

inline 
M_AUT TColEntity_HAry1dOfFacet AutLib::GeoLib::Entity_Edge3d::Facets() const
{
	return theFacets_.Retrive();
}

inline 
void AutLib::GeoLib::Entity_Edge3d::Facets(TColEntity_HAry1dOfFacet & Facets) const
{
	theFacets_.RetrieveTo(Facets);
}

inline 
void AutLib::GeoLib::Entity_Edge3d::InsertToFacets(Global_Handle(Entity_Facet) Facet)
{
	theFacets_.EnQueue(Facet);
}

inline
void AutLib::GeoLib::Entity_Edge3d::SetIndex(const Standard_Integer Index)
{
	theIndex_ = Index;
}

inline
void AutLib::GeoLib::Entity_Edge3d::SetNode(const Standard_Integer Index, Global_Handle(Entity_Node3d) Node)
{
	Debug_Bad_Index(Index, 0, 1);
	theNodes_[Index] = Node;
}

inline
void AutLib::GeoLib::Entity_Edge3d::SetAsBoundary()
{
	IsOnBoundary_ = Standard_True;
}

inline
void AutLib::GeoLib::Entity_Edge3d::SetAsNonBoundary()
{
	IsOnBoundary_ = Standard_False;
}