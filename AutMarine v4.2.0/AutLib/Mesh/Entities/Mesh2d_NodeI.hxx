#pragma once

#ifndef USE_INDEX_NUMBERING
inline
AutLib::MeshLib::Mesh2d_Node::Mesh2d_Node()
	: IsOnBoundary_(Standard_False)
{
	theFront_.SetName("Front Edges Around Node");

	theEdges_.SetName("Edges Around Node");

	theElements_.SetName("Elements Around Node");
}

inline
AutLib::MeshLib::Mesh2d_Node::Mesh2d_Node
(
	const Standard_Integer Index,
	const Geom_Pnt2d & Coord
)
	: theIndex_(Index)
	, theCoord_(Coord)
	, IsOnBoundary_(Standard_False)
{
	theFront_.SetName("Front Edges Around Node");

	theEdges_.SetName("Edges Around Node");

	theElements_.SetName("Elements Around Node");
}
#endif // !USE_INDEX_NUMBERING

inline AutLib::MeshLib::Mesh2d_Node::~Mesh2d_Node()
{
}

inline 
const Geom_Pnt2d & AutLib::MeshLib::Mesh2d_Node::Coord() const
{
	return theCoord_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Node::Index() const
{
	return theIndex_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Node::NbFronts() const
{
	return theFront_.Size();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Node::NbEdges() const
{
	return theEdges_.Size();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Node::NbElements() const
{
	return theElements_.Size();
}

inline 
Standard_Real AutLib::MeshLib::Mesh2d_Node::Radius() const
{
	return theRadius_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh2d_Node::MaxAdjLength() const
{
	return theMaxL_;
}

inline 
M_AUT TColMesh2d_HAry1dOfEdge AutLib::MeshLib::Mesh2d_Node::Edges() const
{
	return theEdges_.Retrieve();
}

inline 
M_AUT TColMesh2d_HAry1dOfEdge AutLib::MeshLib::Mesh2d_Node::Fronts() const
{
	return theFront_.Retrieve();
}

inline 
M_AUT TColMesh2d_HAry1dOfElement AutLib::MeshLib::Mesh2d_Node::Elements() const
{
	return theElements_.Retrieve();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_Node::IsOnFront() const
{
	return theFront_.Size();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_Node::IsEmptyFront() const
{
	return theFront_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_Node::IsEmptyEdges() const
{
	return theEdges_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_Node::IsEmptyElements() const
{
	return theElements_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_Node::IsContainAtFront(Global_Handle(Mesh2d_Edge) Edge) const
{
	return theFront_.IsContains(Edge);
}

inline 
void AutLib::MeshLib::Mesh2d_Node::SetCoord(const Geom_Pnt2d & Coord)
{
	theCoord_ = Coord;
}

inline 
void AutLib::MeshLib::Mesh2d_Node::SetIndex(const Standard_Integer Index)
{
	theIndex_ = Index;
}

inline 
void AutLib::MeshLib::Mesh2d_Node::SetRadius(const Standard_Real Value)
{
	theRadius_ = Value;
}

inline 
void AutLib::MeshLib::Mesh2d_Node::SetMaxAdjLength(const Standard_Real Value)
{
	theMaxL_ = Value;
}

inline 
void AutLib::MeshLib::Mesh2d_Node::RetrieveFrontsTo(TColMesh2d_HBasicQueueOfEdge& Edges) const
{
	theFront_.RetrieveTo(Edges);
}

inline 
void AutLib::MeshLib::Mesh2d_Node::RetrieveEdgesTo(TColMesh2d_HAry1dOfEdge & Edges) const
{
	theEdges_.RetrieveTo(Edges);
}

inline 
void AutLib::MeshLib::Mesh2d_Node::RetrieveFrontsTo(TColMesh2d_HAry1dOfEdge & Fronts) const
{
	theFront_.RetrieveTo(Fronts);
}

inline 
void AutLib::MeshLib::Mesh2d_Node::RetrieveElementsTo(TColMesh2d_HAry1dOfElement & Elements) const
{
	theElements_.RetrieveTo(Elements);
}

inline 
void AutLib::MeshLib::Mesh2d_Node::InsertToFronts(Global_Handle(Mesh2d_Edge) Edge)
{
	theFront_.Insert(Edge);
}

inline 
void AutLib::MeshLib::Mesh2d_Node::InsertToEdges(Global_Handle(Mesh2d_Edge) Edge)
{
	theEdges_.Insert(Edge);
}

inline 
void AutLib::MeshLib::Mesh2d_Node::InsertToElements(Global_Handle(Mesh2d_Element) Element)
{
	theElements_.Insert(Element);
}

inline 
void AutLib::MeshLib::Mesh2d_Node::RemoveFromFronts(Global_Handle(Mesh2d_Edge) Edge)
{
	theFront_.Remove(Edge);
}

inline 
void AutLib::MeshLib::Mesh2d_Node::RemoveFromEdges(Global_Handle(Mesh2d_Edge) Edge)
{
	theEdges_.Remove(Edge);
}

inline
void AutLib::MeshLib::Mesh2d_Node::RemoveFromElements(Global_Handle(Mesh2d_Element) Element)
{
	theElements_.Remove(Element);
}
