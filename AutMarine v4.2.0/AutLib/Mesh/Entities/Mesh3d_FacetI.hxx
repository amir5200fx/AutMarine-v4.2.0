#pragma once
inline
AutLib::MeshLib::Mesh3d_Facet::Mesh3d_Facet()
	: theIndex_(0)
	, theArea_(0)
	, theLength_(0)
	, IsCavity_(Standard_False)
	, theLeftElement_(NULL)
	, theRightElement_(NULL)
{
	theNodes_[0] = NULL;
	theNodes_[1] = NULL;
	theNodes_[2] = NULL;

	theEdges_[0] = NULL;
	theEdges_[1] = NULL;
	theEdges_[2] = NULL;
}

inline 
AutLib::MeshLib::Mesh3d_Facet::Mesh3d_Facet(const Standard_Integer Index)
	: theIndex_(Index)
	, theArea_(0)
	, theLength_(0)
	, IsCavity_(Standard_False)
	, theLeftElement_(NULL)
	, theRightElement_(NULL)
{
	theNodes_[0] = NULL;
	theNodes_[1] = NULL;
	theNodes_[2] = NULL;

	theEdges_[0] = NULL;
	theEdges_[1] = NULL;
	theEdges_[2] = NULL;
}

inline
AutLib::MeshLib::Mesh3d_Facet::Mesh3d_Facet
(
	const Standard_Integer Index,
	Global_Handle(Mesh3d_Node) theNode0,
	Global_Handle(Mesh3d_Node) theNode1,
	Global_Handle(Mesh3d_Node) theNode2
)
	: theIndex_(Index)
	, theArea_(0)
	, theLength_(0)
	, IsCavity_(Standard_False)
	, theLeftElement_(NULL)
	, theRightElement_(NULL)
{
	theNodes_[0] = theNode0;
	theNodes_[1] = theNode1;
	theNodes_[2] = theNode2;

	theEdges_[0] = NULL;
	theEdges_[1] = NULL;
	theEdges_[2] = NULL;
}

inline 
AutLib::MeshLib::Mesh3d_Facet::Mesh3d_Facet
(
	const Standard_Integer Index,
	Global_Handle(Mesh3d_Node) theNode0,
	Global_Handle(Mesh3d_Node) theNode1,
	Global_Handle(Mesh3d_Node) theNode2,
	Global_Handle(Mesh3d_Edge) theEdge0,
	Global_Handle(Mesh3d_Edge) theEdge1,
	Global_Handle(Mesh3d_Edge) theEdge2
)
	: theIndex_(Index)
	, theArea_(0)
	, theLength_(0)
	, IsCavity_(Standard_False)
	, theLeftElement_(NULL)
	, theRightElement_(NULL)
{
	theNodes_[0] = theNode0;
	theNodes_[1] = theNode1;
	theNodes_[2] = theNode2;

	theEdges_[0] = theEdge0;
	theEdges_[1] = theEdge1;
	theEdges_[2] = theEdge2;
}

inline 
AutLib::MeshLib::Mesh3d_Facet::~Mesh3d_Facet()
{
}

inline 
Global_Handle(M_MESH Mesh3d_Node) AutLib::MeshLib::Mesh3d_Facet::Node0() const
{
	return theNodes_[0];
}

inline 
Global_Handle(M_MESH Mesh3d_Node) AutLib::MeshLib::Mesh3d_Facet::Node1() const
{
	return theNodes_[1];
}

inline 
Global_Handle(M_MESH Mesh3d_Node) AutLib::MeshLib::Mesh3d_Facet::Node2() const
{
	return theNodes_[2];
}

inline 
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_Facet::Edge0() const
{
	return theEdges_[0];
}

inline 
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_Facet::Edge1() const
{
	return theEdges_[1];
}

inline 
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_Facet::Edge2() const
{
	return theEdges_[2];
}

inline 
Global_Handle(M_MESH Mesh3d_Element) AutLib::MeshLib::Mesh3d_Facet::RightElement() const
{
	return theRightElement_;
}

inline 
Global_Handle(M_MESH Mesh3d_Element) AutLib::MeshLib::Mesh3d_Facet::LeftElement() const
{
	return theLeftElement_;
}

inline 
Global_Handle(M_MESH Mesh3d_Node) AutLib::MeshLib::Mesh3d_Facet::Node(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 2);
	return theNodes_[Index];
}

inline 
Global_Handle(M_MESH Mesh3d_Node) AutLib::MeshLib::Mesh3d_Facet::OppositeNode(const Mesh3d_Edge & theEdge) const
{
	Debug_Null_Pointer(theEdge.Node0());
	Debug_Null_Pointer(theEdge.Node1());

	forThose
	(
		Index,
		0,
		2
	)
	{
		if (theNodes_[Index] NOT_EQUAL theEdge.Node0() AND theNodes_[Index] NOT_EQUAL theEdge.Node1())
		{
			return theNodes_[Index];
		}
	}

	THROW_STANDARD_EXCEPTION("Not found the node");
	return NULL;
}

inline 
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_Facet::Edge(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 2);
	return theEdges_[Index];
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Facet::Index() const
{
	return theIndex_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Facet::OppositeNodeIndex(const Mesh3d_Edge & theEdge) const
{
	Debug_Null_Pointer(theEdge.Node0());
	Debug_Null_Pointer(theEdge.Node1());

	forThose
	(
		Index,
		0,
		2
	)
	{
		if (theNodes_[Index] NOT_EQUAL theEdge.Node0() AND theNodes_[Index] NOT_EQUAL theEdge.Node1())
		{
			return Index;
		}
	}

	THROW_STANDARD_EXCEPTION("Not found the node");
	return 0;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_Facet::Area() const
{
	return theArea_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_Facet::Length() const
{
	return theLength_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_Facet::MaxRadius() const
{
	return MAX(theNodes_[0]->Radius(), MAX(theNodes_[1]->Radius(), theNodes_[2]->Radius()));
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Facet::IsCavity() const
{
	return IsCavity_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Facet::IsOnFront() const
{
	if (Node0()->IsContainAtFront((Global_Handle(Mesh3d_Facet))this)) { return Standard_True; }
	return Standard_False;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Facet::IsOrphan() const
{
	if (NOT theLeftElement_ AND NOT theRightElement_) { return Standard_True; }
	return Standard_False;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Facet::IsContain(Global_Handle(Mesh3d_Element) theElement) const
{
	Debug_Null_Pointer(theElement);
	if (theElement EQUAL theLeftElement_) return Standard_True;
	if (theElement EQUAL theRightElement_) return Standard_True;
	return Standard_False;
}

inline 
Geom_Pnt3d AutLib::MeshLib::Mesh3d_Facet::Normal() const
{
	Get_Const_Object(P0) = Node0()->Coord();
	Get_Const_Object(P1) = Node1()->Coord();
	Get_Const_Object(P2) = Node2()->Coord();

	return M_GEO CrossProduct(P1 - P0, P2 - P0).UnitLength();
}

inline 
const Geom_Pnt3d & AutLib::MeshLib::Mesh3d_Facet::Centre() const
{
	return theCentre_;
}

inline 
void AutLib::MeshLib::Mesh3d_Facet::SetIndex(const Standard_Integer Value)
{
	theIndex_ = Value;
}

inline 
void AutLib::MeshLib::Mesh3d_Facet::SetNode0(Global_Handle(Mesh3d_Node) Node)
{
	theNodes_[0] = Node;
}

inline 
void AutLib::MeshLib::Mesh3d_Facet::SetNode1(Global_Handle(Mesh3d_Node) Node)
{
	theNodes_[1] = Node;
}

inline 
void AutLib::MeshLib::Mesh3d_Facet::SetNode2(Global_Handle(Mesh3d_Node) Node)
{
	theNodes_[2] = Node;
}

inline 
void AutLib::MeshLib::Mesh3d_Facet::SetEdge0(Global_Handle(Mesh3d_Edge) Edge)
{
	theEdges_[0] = Edge;
}

inline 
void AutLib::MeshLib::Mesh3d_Facet::SetEdge1(Global_Handle(Mesh3d_Edge) Edge)
{
	theEdges_[1] = Edge;
}

inline 
void AutLib::MeshLib::Mesh3d_Facet::SetEdge2(Global_Handle(Mesh3d_Edge) Edge)
{
	theEdges_[2] = Edge;
}

inline 
void AutLib::MeshLib::Mesh3d_Facet::SetRightElement(Global_Handle(Mesh3d_Element) Element)
{
	theRightElement_ = Element;
}

inline
void AutLib::MeshLib::Mesh3d_Facet::SetLeftElement(Global_Handle(Mesh3d_Element) Element)
{
	theLeftElement_ = Element;
}

inline 
void AutLib::MeshLib::Mesh3d_Facet::SetNode(const Standard_Integer Index, Global_Handle(Mesh3d_Node) Node)
{
	Debug_Bad_Index(Index, 0, 2);
	theNodes_[Index] = Node;
}

inline 
void AutLib::MeshLib::Mesh3d_Facet::SetEdge(const Standard_Integer Index, Global_Handle(Mesh3d_Edge) Edge)
{
	Debug_Bad_Index(Index, 0, 2);
	theEdges_[Index] = Edge;
}

inline 
void AutLib::MeshLib::Mesh3d_Facet::SetCentre(const Geom_Pnt3d & Coord)
{
	theCentre_ = Coord;
}

inline 
void AutLib::MeshLib::Mesh3d_Facet::SetLength(const Standard_Real Length)
{
	theLength_ = Length;
}

inline 
void AutLib::MeshLib::Mesh3d_Facet::SetArea(const Standard_Real theArea)
{
	theArea_ = theArea;
}

inline 
void AutLib::MeshLib::Mesh3d_Facet::SetAsCavity()
{
	IsCavity_ = Standard_True;
}

inline 
void AutLib::MeshLib::Mesh3d_Facet::SetAsNotCavity()
{
	IsCavity_ = Standard_False;
}

inline 
void AutLib::MeshLib::Mesh3d_Facet::Reverse()
{
	SWAP(theNodes_[1], theNodes_[2]);
	SWAP(theEdges_[1], theEdges_[2]);
	SWAP(theRightElement_, theLeftElement_);
}