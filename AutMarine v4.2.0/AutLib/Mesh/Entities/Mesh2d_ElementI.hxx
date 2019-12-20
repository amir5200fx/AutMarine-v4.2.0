#pragma once
inline
AutLib::MeshLib::Mesh2d_Element::Mesh2d_Element()
{
}

inline
AutLib::MeshLib::Mesh2d_Element::Mesh2d_Element(const Standard_Integer Index)
	: theIndex_(Index)
{
	theNeighbors_[0] = NULL;
	theNeighbors_[1] = NULL;
	theNeighbors_[2] = NULL;
}

inline 
Global_Handle(Mesh2d_Node) AutLib::MeshLib::Mesh2d_Element::Node0() const
{
	return theNodes_[0];
}

inline
Global_Handle(Mesh2d_Node) AutLib::MeshLib::Mesh2d_Element::Node1() const
{
	return theNodes_[1];
}

inline
Global_Handle(Mesh2d_Node) AutLib::MeshLib::Mesh2d_Element::Node2() const
{
	return theNodes_[2];
}

inline 
Global_Handle(Mesh2d_Edge) AutLib::MeshLib::Mesh2d_Element::Edge0() const
{
	return theEdges_[0];
}

inline
Global_Handle(Mesh2d_Edge) AutLib::MeshLib::Mesh2d_Element::Edge1() const
{
	return theEdges_[1];
}

inline
Global_Handle(Mesh2d_Edge) AutLib::MeshLib::Mesh2d_Element::Edge2() const
{
	return theEdges_[2];
}

inline 
Global_Handle(Mesh2d_Element) AutLib::MeshLib::Mesh2d_Element::Neighbor0() const
{
	return theNeighbors_[0];
}

inline
Global_Handle(Mesh2d_Element) AutLib::MeshLib::Mesh2d_Element::Neighbor1() const
{
	return theNeighbors_[1];
}

inline
Global_Handle(Mesh2d_Element) AutLib::MeshLib::Mesh2d_Element::Neighbor2() const
{
	return theNeighbors_[2];
}

inline 
Global_Handle(Mesh2d_Node) AutLib::MeshLib::Mesh2d_Element::Node(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 2);

	return theNodes_[Index];
}

inline 
Global_Handle(Mesh2d_Edge) AutLib::MeshLib::Mesh2d_Element::Edge(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 2);

	return theEdges_[Index];
}

inline 
Global_Handle(Mesh2d_Element) AutLib::MeshLib::Mesh2d_Element::Neighbor(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 2);

	return theNeighbors_[Index];
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Element::Index() const
{
	return theIndex_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Element::OppositeVertexIndex(const Mesh2d_Edge & Edge) const
{
	Standard_Integer Index = -1;
	Standard_Address Adress = (Standard_Address)&Edge;
	
	forThose(I, 0, 2)
	{
		if (theEdges_[I] == Adress)
		{
			return I;
		}
	}

	if (Index < 0)
	{
		THROW_STANDARD_EXCEPTION(" NOT FIND opposite vertex");
	}

	return Index;  // Prevent compiler warning
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Element::OppositeVertexIndex(const Mesh2d_Element & Element) const
{
	Standard_Integer Index = -1;
	Standard_Address Adress = (Standard_Address)&Element;

	forThose(I, 0, 2)
	{
		if (theNeighbors_[I] == Adress)
		{
			return I;
		}
	}

	if (Index < 0)
	{
		THROW_STANDARD_EXCEPTION(" NOT FIND opposite vertex");
	}

	return Index;  // Prevent compiler warning
}

inline 
Global_Handle(Mesh2d_Node) AutLib::MeshLib::Mesh2d_Element::OppositeVertex(const Mesh2d_Edge & Edge) const
{
	Standard_Address Adress = (Standard_Address)&Edge;

	forThose(I, 0, 2)
	{
		if (theEdges_[I] == Adress)
		{
			return theNodes_[I];
		}
	}

	return NULL;
}

inline 
Global_Handle(Mesh2d_Node) AutLib::MeshLib::Mesh2d_Element::OppositeVertex(const Mesh2d_Element & Element) const
{
	Standard_Address Adress = (Standard_Address)&Element;

	forThose(I, 0, 2)
	{
		if (theNeighbors_[I] == Adress)
		{
			return theNodes_[I];
		}
	}

	return NULL;
}

inline 
void AutLib::MeshLib::Mesh2d_Element::SetIndex(const Standard_Integer Value)
{
	theIndex_ = Value;
}

inline 
void AutLib::MeshLib::Mesh2d_Element::SetNode0(Global_Handle(Mesh2d_Node) Node)
{
	theNodes_[0] = Node;
}

inline
void AutLib::MeshLib::Mesh2d_Element::SetNode1(Global_Handle(Mesh2d_Node) Node)
{
	theNodes_[1] = Node;
}

inline
void AutLib::MeshLib::Mesh2d_Element::SetNode2(Global_Handle(Mesh2d_Node) Node)
{
	theNodes_[2] = Node;
}

inline 
void AutLib::MeshLib::Mesh2d_Element::SetEdge0(Global_Handle(Mesh2d_Edge) Edge)
{
	theEdges_[0] = Edge;
}

inline
void AutLib::MeshLib::Mesh2d_Element::SetEdge1(Global_Handle(Mesh2d_Edge) Edge)
{
	theEdges_[1] = Edge;
}

inline
void AutLib::MeshLib::Mesh2d_Element::SetEdge2(Global_Handle(Mesh2d_Edge) Edge)
{
	theEdges_[2] = Edge;
}

inline 
void AutLib::MeshLib::Mesh2d_Element::SetNeighbor0(Global_Handle(Mesh2d_Element) Element)
{
	theNeighbors_[0];
}

inline
void AutLib::MeshLib::Mesh2d_Element::SetNeighbor1(Global_Handle(Mesh2d_Element) Element)
{
	theNeighbors_[1];
}

inline
void AutLib::MeshLib::Mesh2d_Element::SetNeighbor2(Global_Handle(Mesh2d_Element) Element)
{
	theNeighbors_[2];
}

inline 
void AutLib::MeshLib::Mesh2d_Element::SetNode
(
	const Standard_Integer Index,
	Global_Handle(Mesh2d_Node) Node
)
{
	Debug_Bad_Index(Index, 0, 2);

	theNodes_[Index] = Node;
}

inline 
void AutLib::MeshLib::Mesh2d_Element::SetEdge
(
	const Standard_Integer Index,
	Global_Handle(Mesh2d_Edge) Edge
)
{
	Debug_Bad_Index(Index, 0, 2);

	theEdges_[Index] = Edge;
}

inline 
void AutLib::MeshLib::Mesh2d_Element::SetNeighbor
(
	const Standard_Integer Index,
	Global_Handle(Mesh2d_Element) Element
)
{
	Debug_Bad_Index(Index, 0, 2);

	theNeighbors_[Index] = Element;
}