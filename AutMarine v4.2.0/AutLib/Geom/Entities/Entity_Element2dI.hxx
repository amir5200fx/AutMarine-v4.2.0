#pragma once
inline
AutLib::GeoLib::Entity_Element2d::Entity_Element2d()
{
	theNodes_[0] = NULL;
	theNodes_[1] = NULL;
	theNodes_[2] = NULL;
}

inline 
AutLib::GeoLib::Entity_Element2d::Entity_Element2d(const Standard_Integer Index)
	: theIndex_(Index)
{
}

inline 
Global_Handle(M_GEO Entity_Node2d) AutLib::GeoLib::Entity_Element2d::Node0() const
{
	return theNodes_[0];
}

inline 
Global_Handle(M_GEO Entity_Node2d) AutLib::GeoLib::Entity_Element2d::Node1() const
{
	return theNodes_[1];
}

inline 
Global_Handle(M_GEO Entity_Node2d) AutLib::GeoLib::Entity_Element2d::Node2() const
{
	return theNodes_[2];
}

inline 
Global_Handle(M_GEO Entity_Edge2d) AutLib::GeoLib::Entity_Element2d::Edge0() const
{
	return theEdges_[0];
}

inline 
Global_Handle(M_GEO Entity_Edge2d) AutLib::GeoLib::Entity_Element2d::Edge1() const
{
	return theEdges_[1];
}

inline 
Global_Handle(M_GEO Entity_Edge2d) AutLib::GeoLib::Entity_Element2d::Edge2() const
{
	return theEdges_[2];
}

inline 
Global_Handle(M_GEO Entity_Element2d) AutLib::GeoLib::Entity_Element2d::Neighbor0() const
{
	return theNeighbors_[0];
}

inline 
Global_Handle(M_GEO Entity_Element2d) AutLib::GeoLib::Entity_Element2d::Neighbor1() const
{
	return theNeighbors_[1];
}

inline 
Global_Handle(M_GEO Entity_Element2d) AutLib::GeoLib::Entity_Element2d::Neighbor2() const
{
	return theNeighbors_[2];
}

inline 
Global_Handle(M_GEO Entity_Node2d) AutLib::GeoLib::Entity_Element2d::Node(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 2);
	return theNodes_[Index];
}

inline 
Global_Handle(M_GEO Entity_Edge2d) AutLib::GeoLib::Entity_Element2d::Edge(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 2);
	return theEdges_[Index];
}

inline 
Global_Handle(M_GEO Entity_Element2d) AutLib::GeoLib::Entity_Element2d::Neighbor(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 2);
	return theNeighbors_[Index];
}

inline 
Standard_Integer AutLib::GeoLib::Entity_Element2d::Index() const
{
	return theIndex_;
}

inline 
Standard_Integer AutLib::GeoLib::Entity_Element2d::OppositeVertexIndex(const Entity_Edge2d & Edge) const
{
	Standard_Integer Index = -1;
	Standard_Address Adress = (Standard_Address)&Edge;

	forThose(I, 0, 2) if (theEdges_[I] EQUAL Adress) { return I; }
	if (Index < 0) { THROW_STANDARD_EXCEPTION(" NOT FIND opposite vertex"); }
	return 0;  // Prevent compiler warning
}

inline 
Standard_Integer AutLib::GeoLib::Entity_Element2d::OppositeVertexIndex(const Entity_Element2d & Element) const
{
	Standard_Integer Index = -1;
	Standard_Address Adress = (Standard_Address)&Element;

	forThose(I, 0, 2) if (theNeighbors_[I] EQUAL Adress) { return I; }
	if (Index < 0) { THROW_STANDARD_EXCEPTION(" NOT FIND opposite vertex"); }
	return 0;  // Prevent compiler warning
}

inline 
Global_Handle(M_GEO Entity_Node2d) AutLib::GeoLib::Entity_Element2d::OppositeVertex(const Entity_Edge2d & Edge) const
{
	Standard_Address Adress = (Standard_Address)&Edge;

	forThose(Index, 0, 2) if (theEdges_[Index] EQUAL Adress) { return theNodes_[Index]; }
	return NULL;
}

inline 
Global_Handle(M_GEO Entity_Node2d) AutLib::GeoLib::Entity_Element2d::OppositeVertex(const Entity_Element2d & Element) const
{
	Standard_Address Adress = (Standard_Address)&Element;

	forThose(Index, 0, 2) if (theNeighbors_[Index] EQUAL Adress) { return theNodes_[Index]; }
	return NULL;
}

inline
void AutLib::GeoLib::Entity_Element2d::SetIndex(const Standard_Integer Value)
{
	theIndex_ = Value;
}

inline 
void AutLib::GeoLib::Entity_Element2d::SetNode0(Global_Handle(Entity_Node2d) Node)
{
	theNodes_[0] = Node;
}

inline 
void AutLib::GeoLib::Entity_Element2d::SetNode1(Global_Handle(Entity_Node2d) Node)
{
	theNodes_[1] = Node;
}

inline 
void AutLib::GeoLib::Entity_Element2d::SetNode2(Global_Handle(Entity_Node2d) Node)
{
	theNodes_[2] = Node;
}

inline 
void AutLib::GeoLib::Entity_Element2d::SetEdge0(Global_Handle(Entity_Edge2d) Edge)
{
	theEdges_[0] = Edge;
}

inline 
void AutLib::GeoLib::Entity_Element2d::SetEdge1(Global_Handle(Entity_Edge2d) Edge)
{
	theEdges_[1] = Edge;
}

inline 
void AutLib::GeoLib::Entity_Element2d::SetEdge2(Global_Handle(Entity_Edge2d) Edge)
{
	theEdges_[2] = Edge;
}

inline 
void AutLib::GeoLib::Entity_Element2d::SetNeighbor0(Global_Handle(Entity_Element2d) Element)
{
	theNeighbors_[0] = Element;
}

inline 
void AutLib::GeoLib::Entity_Element2d::SetNeighbor1(Global_Handle(Entity_Element2d) Element)
{
	theNeighbors_[1] = Element;
}

inline 
void AutLib::GeoLib::Entity_Element2d::SetNeighbor2(Global_Handle(Entity_Element2d) Element)
{
	theNeighbors_[2] = Element;
}

inline
void AutLib::GeoLib::Entity_Element2d::SetNode(const Standard_Integer Index, Global_Handle(Entity_Node2d) Node)
{
	Debug_Bad_Index(Index, 0, 2);
	theNodes_[Index] = Node;
}

inline 
void AutLib::GeoLib::Entity_Element2d::SetEdge(const Standard_Integer Index, Global_Handle(Entity_Edge2d) Edge)
{
	Debug_Bad_Index(Index, 0, 2);
	theEdges_[Index] = Edge;
}

inline 
void AutLib::GeoLib::Entity_Element2d::SetNeighbor(const Standard_Integer Index, Global_Handle(Entity_Element2d) Element)
{
	Debug_Bad_Index(Index, 0, 2);
	theNeighbors_[Index] = Element;
}