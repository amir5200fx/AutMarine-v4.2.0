#pragma once
inline
AutLib::GeoLib::Entity_Facet::Entity_Facet(const Standard_Integer Index)
	: theIndex_(Index)
	, IsOnBoundary_(Standard_False)
{
}

inline 
AutLib::GeoLib::Entity_Facet::Entity_Facet
(
	const Standard_Integer Index, 
	Global_Handle(Entity_Node3d) Node0,
	Global_Handle(Entity_Node3d) Node1,
	Global_Handle(Entity_Node3d) Node2
)
	: theIndex_(Index)
	, IsOnBoundary_(Standard_False)
{
	theNodes_[0] = Node0;
	theNodes_[1] = Node1;
	theNodes_[2] = Node2;

	theLeft_ = NULL;
	theRight_ = NULL;
}

inline 
Global_Handle(M_GEO Entity_Node3d) AutLib::GeoLib::Entity_Facet::Node0() const
{
	return theNodes_[0];
}

inline
Global_Handle(M_GEO Entity_Node3d) AutLib::GeoLib::Entity_Facet::Node1() const
{
	return theNodes_[1];
}

inline
Global_Handle(M_GEO Entity_Node3d) AutLib::GeoLib::Entity_Facet::Node2() const
{
	return theNodes_[2];
}

inline 
Global_Handle(M_GEO Entity_Edge3d) AutLib::GeoLib::Entity_Facet::Edge0() const
{
	return theEdges_[0];
}

inline
Global_Handle(M_GEO Entity_Edge3d) AutLib::GeoLib::Entity_Facet::Edge1() const
{
	return theEdges_[1];
}

inline
Global_Handle(M_GEO Entity_Edge3d) AutLib::GeoLib::Entity_Facet::Edge2() const
{
	return theEdges_[2];
}

inline 
Global_Handle(M_GEO Entity_Element3d) AutLib::GeoLib::Entity_Facet::LeftElement() const
{
	return theLeft_;
}

inline 
Global_Handle(M_GEO Entity_Element3d) AutLib::GeoLib::Entity_Facet::RightElement() const
{
	return theRight_;
}

inline 
Global_Handle(M_GEO Entity_Node3d) AutLib::GeoLib::Entity_Facet::Node(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 2);
	return theNodes_[Index];
}

inline 
Global_Handle(M_GEO Entity_Edge3d) AutLib::GeoLib::Entity_Facet::Edge(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 2);
	return theEdges_[Index];
}

inline 
Standard_Integer AutLib::GeoLib::Entity_Facet::Index() const
{
	return theIndex_;
}

inline 
Standard_Boolean AutLib::GeoLib::Entity_Facet::IsOnBoundary() const
{
	return IsOnBoundary_;
}

inline 
const Geom_Pnt3d& AutLib::GeoLib::Entity_Facet::Normal() const
{
	Debug_If_Condition_Message(theNormal_.TwoNorm() EQUAL 0, "Null Normal");
	return theNormal_;
}

inline 
const Geom_Pnt3d & AutLib::GeoLib::Entity_Facet::ReverseNormal() const
{
	Debug_If_Condition_Message(theNormal_.TwoNorm() EQUAL 0, "Null Normal");
	return -1*theNormal_;
}

inline 
void AutLib::GeoLib::Entity_Facet::CalcNormal()
{
	theNormal_ = CrossProduct(Node1()->Coord() - Node0()->Coord(), Node2()->Coord() - Node0()->Coord());
}

inline 
void AutLib::GeoLib::Entity_Facet::SetNode0(Global_Handle(Entity_Node3d) Node)
{
	theNodes_[0] = Node;
}

inline
void AutLib::GeoLib::Entity_Facet::SetNode1(Global_Handle(Entity_Node3d) Node)
{
	theNodes_[1] = Node;
}

inline
void AutLib::GeoLib::Entity_Facet::SetNode2(Global_Handle(Entity_Node3d) Node)
{
	theNodes_[2] = Node;
}

inline 
void AutLib::GeoLib::Entity_Facet::SetEdge0(Global_Handle(Entity_Edge3d) Edge)
{
	theEdges_[0] = Edge;
}

inline
void AutLib::GeoLib::Entity_Facet::SetEdge1(Global_Handle(Entity_Edge3d) Edge)
{
	theEdges_[1] = Edge;
}

inline
void AutLib::GeoLib::Entity_Facet::SetEdge2(Global_Handle(Entity_Edge3d) Edge)
{
	theEdges_[2] = Edge;
}

inline 
void AutLib::GeoLib::Entity_Facet::SetLeftNeighbor(Global_Handle(Entity_Element3d) Element)
{
	theLeft_ = Element;
}

inline 
void AutLib::GeoLib::Entity_Facet::SetRightNeighbor(Global_Handle(Entity_Element3d) Element)
{
	theRight_ = Element;
}

inline 
void AutLib::GeoLib::Entity_Facet::SetNode(const Standard_Integer Index, Global_Handle(Entity_Node3d) Node)
{
	Debug_Bad_Index(Index, 0, 2);
	theNodes_[Index] = Node;
}

inline 
void AutLib::GeoLib::Entity_Facet::SetEdge(const Standard_Integer Index, Global_Handle(Entity_Edge3d) Edge)
{
	Debug_Bad_Index(Index, 0, 2);
	theEdges_[Index] = Edge;
}

inline 
void AutLib::GeoLib::Entity_Facet::SetAsBoundary()
{
	IsOnBoundary_ = Standard_True;
}

inline 
void AutLib::GeoLib::Entity_Facet::SetAsNonBoundary()
{
	IsOnBoundary_ = Standard_False;
}