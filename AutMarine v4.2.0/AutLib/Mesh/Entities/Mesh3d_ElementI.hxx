#pragma once
inline
AutLib::MeshLib::Mesh3d_Element::Mesh3d_Element()
	: theIndex_(0)
{
	forThose(Index, 0, 3)
		theNeighbors_[Index] = NULL;
}

inline 
AutLib::MeshLib::Mesh3d_Element::Mesh3d_Element(const Standard_Integer Index)
	: theIndex_(Index)
{
	forThose(Index, 0, 3)
		theNeighbors_[Index] = NULL;
}

inline 
Global_Handle(M_MESH Mesh3d_Node) AutLib::MeshLib::Mesh3d_Element::Node(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 3);
	return theNodes_[Index];
}

inline
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_Element::Edge(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 5);
	return theEdges_[Index];
}

inline 
Global_Handle(M_MESH Mesh3d_Facet) AutLib::MeshLib::Mesh3d_Element::Facet(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 3);
	return theFacets_[Index];
}

inline 
Global_Handle(M_MESH Mesh3d_Element) AutLib::MeshLib::Mesh3d_Element::Neighbor(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 3);
	return theNeighbors_[Index];
}

inline 
Global_Handle(M_MESH Mesh3d_Node) AutLib::MeshLib::Mesh3d_Element::OppositeVertex(const Global_Handle(Mesh3d_Facet) Facet) const
{
	forThose(Index, 0, 3) if (theFacets_[Index] EQUAL Facet) { return theNodes_[Index]; }
	return NULL;
}

inline 
Global_Handle(M_MESH Mesh3d_Node) AutLib::MeshLib::Mesh3d_Element::OppositeVertex(const Global_Handle(Mesh3d_Element) Element) const
{
	forThose(Index, 0, 3) if (theNeighbors_[Index] EQUAL Element) { return theNodes_[Index]; }
	return NULL;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Element::Index() const
{
	return theIndex_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Element::OppositeVertexIndex(const Global_Handle(Mesh3d_Facet) Facet) const
{
	forThose(Index, 0, 3) if (theFacets_[Index] EQUAL Facet) { return Index; }
	return -1;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Element::OppositeVertexIndex(const Global_Handle(Mesh3d_Element) Element) const
{
	forThose(Index, 0, 3) if (theNeighbors_[Index] EQUAL Element) { return Index; }
	return -1;
}

inline 
Geom_Pnt3d AutLib::MeshLib::Mesh3d_Element::Centre() const
{
	return 0.25*(Node(0)->Coord() + Node(1)->Coord() + Node(2)->Coord() + Node(3)->Coord());
}

inline
void AutLib::MeshLib::Mesh3d_Element::SetIndex(const Standard_Integer Index)
{
	theIndex_ = Index;
}

inline 
void AutLib::MeshLib::Mesh3d_Element::SetNode(const Standard_Integer Index, Global_Handle(Mesh3d_Node) Node)
{
	Debug_Bad_Index(Index, 0, 3);
	theNodes_[Index] = Node;
}

inline 
void AutLib::MeshLib::Mesh3d_Element::SetEdge(const Standard_Integer Index, Global_Handle(Mesh3d_Edge) Edge)
{
	Debug_Bad_Index(Index, 0, 5);
	theEdges_[Index] = Edge;
}

inline 
void AutLib::MeshLib::Mesh3d_Element::SetFacet(const Standard_Integer Index, Global_Handle(Mesh3d_Facet) Facet)
{
	Debug_Bad_Index(Index, 0, 3);
	theFacets_[Index] = Facet;
}

inline 
void AutLib::MeshLib::Mesh3d_Element::SetNeighbor(const Standard_Integer Index, Global_Handle(Mesh3d_Element) Element)
{
	Debug_Bad_Index(Index, 0, 3);
	theNeighbors_[Index] = Element;
}