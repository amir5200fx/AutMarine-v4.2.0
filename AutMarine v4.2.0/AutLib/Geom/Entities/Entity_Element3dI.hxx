#pragma once
inline
AutLib::GeoLib::Entity_Element3d::Entity_Element3d()
{
}

inline 
AutLib::GeoLib::Entity_Element3d::Entity_Element3d(const Standard_Integer Index)
	: theIndex_(Index)
{
}

inline 
Global_Handle(M_GEO Entity_Node3d) AutLib::GeoLib::Entity_Element3d::Node0() const
{
	return theNodes_[0];
}

inline
Global_Handle(M_GEO Entity_Node3d) AutLib::GeoLib::Entity_Element3d::Node1() const
{
	return theNodes_[1];
}

inline
Global_Handle(M_GEO Entity_Node3d) AutLib::GeoLib::Entity_Element3d::Node2() const
{
	return theNodes_[2];
}

inline
Global_Handle(M_GEO Entity_Node3d) AutLib::GeoLib::Entity_Element3d::Node3() const
{
	return theNodes_[3];
}

inline 
Global_Handle(M_GEO Entity_Edge3d) AutLib::GeoLib::Entity_Element3d::Edge0() const
{
	return theEdges_[0];
}

inline
Global_Handle(M_GEO Entity_Edge3d) AutLib::GeoLib::Entity_Element3d::Edge1() const
{
	return theEdges_[1];
}

inline
Global_Handle(M_GEO Entity_Edge3d) AutLib::GeoLib::Entity_Element3d::Edge2() const
{
	return theEdges_[2];
}

inline
Global_Handle(M_GEO Entity_Edge3d) AutLib::GeoLib::Entity_Element3d::Edge3() const
{
	return theEdges_[3];
}

inline
Global_Handle(M_GEO Entity_Edge3d) AutLib::GeoLib::Entity_Element3d::Edge4() const
{
	return theEdges_[4];
}

inline
Global_Handle(M_GEO Entity_Edge3d) AutLib::GeoLib::Entity_Element3d::Edge5() const
{
	return theEdges_[5];
}

inline 
Global_Handle(M_GEO Entity_Facet) AutLib::GeoLib::Entity_Element3d::Facet0() const
{
	return theFacets_[0];
}

inline
Global_Handle(M_GEO Entity_Facet) AutLib::GeoLib::Entity_Element3d::Facet1() const
{
	return theFacets_[1];
}

inline
Global_Handle(M_GEO Entity_Facet) AutLib::GeoLib::Entity_Element3d::Facet2() const
{
	return theFacets_[2];
}

inline
Global_Handle(M_GEO Entity_Facet) AutLib::GeoLib::Entity_Element3d::Facet3() const
{
	return theFacets_[3];
}

inline 
Global_Handle(M_GEO Entity_Element3d) AutLib::GeoLib::Entity_Element3d::Neighbor0() const
{
	return theNeighbors_[0];
}

inline
Global_Handle(M_GEO Entity_Element3d) AutLib::GeoLib::Entity_Element3d::Neighbor1() const
{
	return theNeighbors_[1];
}

inline
Global_Handle(M_GEO Entity_Element3d) AutLib::GeoLib::Entity_Element3d::Neighbor2() const
{
	return theNeighbors_[2];
}

inline
Global_Handle(M_GEO Entity_Element3d) AutLib::GeoLib::Entity_Element3d::Neighbor3() const
{
	return theNeighbors_[3];
}

inline 
Global_Handle(M_GEO Entity_Node3d) AutLib::GeoLib::Entity_Element3d::Node(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 3);
	return theNodes_[Index];
}

inline 
Global_Handle(M_GEO Entity_Edge3d) AutLib::GeoLib::Entity_Element3d::Edge(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 5);
	return theEdges_[Index];
}

inline 
Global_Handle(M_GEO Entity_Facet) AutLib::GeoLib::Entity_Element3d::Facet(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 3);
	return theFacets_[Index];
}

inline 
Global_Handle(M_GEO Entity_Element3d) AutLib::GeoLib::Entity_Element3d::Neighbor(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 3);
	return theNeighbors_[Index];
}

inline 
Standard_Integer AutLib::GeoLib::Entity_Element3d::Index() const
{
	return theIndex_;
}

inline 
Standard_Integer AutLib::GeoLib::Entity_Element3d::OppositeVertexIndex(const Entity_Facet & Facet) const
{
	Standard_Integer Index = -1;
	Standard_Address Adress = (Standard_Address)&Facet;

	forThose(I, 0, 3) if (theFacets_[I] EQUAL Adress) { return I; }
	if (Index < 0) { THROW_STANDARD_EXCEPTION(" NOT FIND opposite vertex"); }
	return 0;  // Prevent compiler warning
}

inline 
Standard_Integer AutLib::GeoLib::Entity_Element3d::OppositeVertexIndex(const Entity_Element3d & Element) const
{
	Standard_Integer Index = -1;
	Standard_Address Adress = (Standard_Address)&Element;

	forThose(I, 0, 3) if (theNeighbors_[I] EQUAL Adress) { return I; }
	if (Index < 0) { THROW_STANDARD_EXCEPTION(" NOT FIND opposite vertex"); }
	return 0;  // Prevent compiler warning
}

inline 
Standard_Real AutLib::GeoLib::Entity_Element3d::Volume() const
{
	return theVolume_;
}

inline 
Standard_Real AutLib::GeoLib::Entity_Element3d::Characteristic() const
{
	return thel_;
}

inline 
Global_Handle(M_GEO Entity_Node3d) AutLib::GeoLib::Entity_Element3d::OppositeVertex(const Entity_Facet & Facet) const
{
	Standard_Address Adress = (Standard_Address)&Facet;

	forThose(Index, 0, 3) if (theFacets_[Index] EQUAL Adress) { return theNodes_[Index]; }
	return NULL;
}

inline 
Global_Handle(M_GEO Entity_Node3d) AutLib::GeoLib::Entity_Element3d::OppositeVertex(const Entity_Element3d & Element) const
{
	Standard_Address Adress = (Standard_Address)&Element;

	forThose(Index, 0, 3) if (theNeighbors_[Index] EQUAL Adress) { return theNodes_[Index]; }
	return NULL;
}

inline 
void AutLib::GeoLib::Entity_Element3d::SetIndex(const Standard_Integer Value)
{
	theIndex_ = Value;
}

inline 
void AutLib::GeoLib::Entity_Element3d::SetNode0(Global_Handle(Entity_Node3d) Node)
{
	theNodes_[0] = Node;
}

inline
void AutLib::GeoLib::Entity_Element3d::SetNode1(Global_Handle(Entity_Node3d) Node)
{
	theNodes_[1] = Node;
}

inline
void AutLib::GeoLib::Entity_Element3d::SetNode2(Global_Handle(Entity_Node3d) Node)
{
	theNodes_[2] = Node;
}

inline
void AutLib::GeoLib::Entity_Element3d::SetNode3(Global_Handle(Entity_Node3d) Node)
{
	theNodes_[3] = Node;
}

inline 
void AutLib::GeoLib::Entity_Element3d::SetEdge0(Global_Handle(Entity_Edge3d) Edge)
{
	theEdges_[0] = Edge;
}

inline
void AutLib::GeoLib::Entity_Element3d::SetEdge1(Global_Handle(Entity_Edge3d) Edge)
{
	theEdges_[1] = Edge;
}

inline
void AutLib::GeoLib::Entity_Element3d::SetEdge2(Global_Handle(Entity_Edge3d) Edge)
{
	theEdges_[2] = Edge;
}

inline
void AutLib::GeoLib::Entity_Element3d::SetEdge3(Global_Handle(Entity_Edge3d) Edge)
{
	theEdges_[3] = Edge;
}

inline
void AutLib::GeoLib::Entity_Element3d::SetEdge4(Global_Handle(Entity_Edge3d) Edge)
{
	theEdges_[4] = Edge;
}

inline
void AutLib::GeoLib::Entity_Element3d::SetEdge5(Global_Handle(Entity_Edge3d) Edge)
{
	theEdges_[5] = Edge;
}

inline 
void AutLib::GeoLib::Entity_Element3d::SetNeighbor0(Global_Handle(Entity_Element3d) Element)
{
	theNeighbors_[0] = Element;
}

inline
void AutLib::GeoLib::Entity_Element3d::SetNeighbor1(Global_Handle(Entity_Element3d) Element)
{
	theNeighbors_[1] = Element;
}

inline
void AutLib::GeoLib::Entity_Element3d::SetNeighbor2(Global_Handle(Entity_Element3d) Element)
{
	theNeighbors_[2] = Element;
}

inline
void AutLib::GeoLib::Entity_Element3d::SetNeighbor3(Global_Handle(Entity_Element3d) Element)
{
	theNeighbors_[3] = Element;
}

inline 
void AutLib::GeoLib::Entity_Element3d::SetNode(const Standard_Integer Index, Global_Handle(Entity_Node3d) Node)
{
	Debug_Bad_Index(Index, 0, 3);
	theNodes_[Index] = Node;
}

inline 
void AutLib::GeoLib::Entity_Element3d::SetEdge(const Standard_Integer Index, Global_Handle(Entity_Edge3d) Edge)
{
	Debug_Bad_Index(Index, 0, 5);
	theEdges_[Index] = Edge;
}

inline 
void AutLib::GeoLib::Entity_Element3d::SetFacet(const Standard_Integer Index, Global_Handle(Entity_Facet) Facet)
{
	Debug_Bad_Index(Index, 0, 3);
	theFacets_[Index] = Facet;
}

inline 
void AutLib::GeoLib::Entity_Element3d::SetNeighbor(const Standard_Integer Index, Global_Handle(Entity_Element3d) Element)
{
	Debug_Bad_Index(Index, 0, 3);
	theNeighbors_[Index] = Element;
}