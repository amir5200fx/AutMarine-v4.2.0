#pragma once
inline
AutLib::GeoLib::Entity_Node2d::Entity_Node2d()
	: IsOnBoundary_(Standard_False)
{
}

inline 
AutLib::GeoLib::Entity_Node2d::Entity_Node2d
(
	const Standard_Integer Index, 
	const Geom_Pnt2d & Coord
)
	: theIndex_(Index)
	, theCoord_(Coord)
	, IsOnBoundary_(Standard_False)
{
}

inline 
void AutLib::GeoLib::Entity_Node2d::SetIndex(const Standard_Integer Index)
{
	theIndex_ = Index;
}

inline 
void AutLib::GeoLib::Entity_Node2d::SetCoord(const Geom_Pnt2d & Coord)
{
	theCoord_ = Coord;
}

inline 
void AutLib::GeoLib::Entity_Node2d::SetAsBoundary()
{
	IsOnBoundary_ = Standard_True;
}

inline 
void AutLib::GeoLib::Entity_Node2d::Edges(TColEntity_HAry1dOfEdge2d & Edges) const
{
	theEdges_.RetrieveTo(Edges);
}

inline 
void AutLib::GeoLib::Entity_Node2d::Elements(TColEntity_HAry1dOfElement2d & Elements) const
{
	theElements_.RetrieveTo(Elements);
}

inline 
void AutLib::GeoLib::Entity_Node2d::InsertToEdges(Global_Handle(Entity_Edge2d) Edge)
{
	theEdges_.EnQueue(Edge);
}

inline 
void AutLib::GeoLib::Entity_Node2d::InsertToElements(Global_Handle(Entity_Element2d) Element)
{
	theElements_.EnQueue(Element);
}

inline 
Standard_Integer AutLib::GeoLib::Entity_Node2d::Index() const
{
	return theIndex_;
}

inline 
Standard_Integer AutLib::GeoLib::Entity_Node2d::NbEdges() const
{
	return theEdges_.Size();
}

inline 
Standard_Integer AutLib::GeoLib::Entity_Node2d::NbElements() const
{
	return theElements_.Size();
}

inline 
const M_GEO Geom_Pnt2d & AutLib::GeoLib::Entity_Node2d::Coord() const
{
	return theCoord_;
}

inline 
M_AUT TColEntity_HAry1dOfEdge2d AutLib::GeoLib::Entity_Node2d::Edges() const
{
	return theEdges_.Retrive();
}

inline 
M_AUT TColEntity_HAry1dOfElement2d AutLib::GeoLib::Entity_Node2d::Elements() const
{
	return theElements_.Retrive();
}