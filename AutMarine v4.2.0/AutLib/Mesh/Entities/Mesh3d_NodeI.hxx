#pragma once
#ifndef USE_INDEX_NUMBERING
inline
AutLib::MeshLib::Mesh3d_Node::Mesh3d_Node()
{
	theFrontEdges_.SetName(" Front Edges Around Node");
	theFrontFacets_.SetName(" Front Facets Around Node");

	theEdges_.SetName(" Edges Around Node");
	theFacets_.SetName(" Facets Around Node");
	theElements_.SetName(" Elements Around Node");
}

inline
AutLib::MeshLib::Mesh3d_Node::Mesh3d_Node
(
	const Standard_Integer Index,
	const Geom_Pnt3d & Coord
)
	: theIndex_(Index)
	, theCoord_(Coord)
{
	theFrontEdges_.SetName(" Front Edges Around Node");
	theFrontFacets_.SetName(" Front Facets Around Node");

	theEdges_.SetName(" Edges Around Node");
	theFacets_.SetName(" Facets Around Node");
	theElements_.SetName(" Elements Around Node");
}
#endif

inline 
AutLib::MeshLib::Mesh3d_Node::~Mesh3d_Node()
{
}

inline 
const Geom_Pnt3d & AutLib::MeshLib::Mesh3d_Node::Coord() const
{
	return theCoord_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Node::Index() const
{
	return theIndex_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Node::NbFrontEdges() const
{
	return theFrontEdges_.Size();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Node::NbFrontFacets() const
{
	return theFrontFacets_.Size();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Node::NbEdges() const
{
	return theEdges_.Size();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Node::NbFacets() const
{
	return theFacets_.Size();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Node::NbElements() const
{
	return theElements_.Size();
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_Node::Radius() const
{
	return theRadius_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_Node::MaxAdjLength() const
{
	return theMaxL_;
}

inline 
M_AUT TColMesh3d_HAry1dOfEdge AutLib::MeshLib::Mesh3d_Node::RetriveFrontEdges() const
{
	return theFrontEdges_.Retrieve();
}

inline 
M_AUT TColMesh3d_HAry1dOfFacet AutLib::MeshLib::Mesh3d_Node::RetrieveFrontFacets() const
{
	return theFrontFacets_.Retrieve();
}

inline 
M_AUT TColMesh3d_HAry1dOfEdge AutLib::MeshLib::Mesh3d_Node::RetrieveEdges() const
{
	return theEdges_.Retrieve();
}

inline 
M_AUT TColMesh3d_HAry1dOfFacet AutLib::MeshLib::Mesh3d_Node::RetrieveFacets() const
{
	return theFacets_.Retrieve();
}

inline 
M_AUT TColMesh3d_HAry1dOfElement AutLib::MeshLib::Mesh3d_Node::RetrieveElements() const
{
	return theElements_.Retrieve();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Node::IsFrontEdgesEmpty() const
{
	return theFrontEdges_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Node::IsFrontFacetsEmpty() const
{
	return theFrontFacets_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Node::IsEdgesEmpty() const
{
	return theEdges_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Node::IsFacetsEmpty() const
{
	return theFacets_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Node::IsElementsEmpty() const
{
	return theElements_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Node::IsContainAtMesh(Global_Handle(Mesh3d_Edge) theEdge) const
{
	Debug_Null_Pointer(theEdge);
	return theEdges_.IsContains(theEdge);
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Node::IsContainAtMesh(Global_Handle(Mesh3d_Facet) theFacet) const
{
	Debug_Null_Pointer(theFacet);
	return theFacets_.IsContains(theFacet);
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Node::IsContainAtMesh(Global_Handle(Mesh3d_Element) theElement) const
{
	Debug_Null_Pointer(theElement);
	return theElements_.IsContains(theElement);
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Node::IsContainAtFront(Global_Handle(Mesh3d_Edge) Edge) const
{
	Debug_Null_Pointer(Edge);
	return theFrontEdges_.IsContains(Edge);
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Node::IsContainAtFront(Global_Handle(Mesh3d_Facet) Facet) const
{
	Debug_Null_Pointer(Facet);
	return theFrontFacets_.IsContains(Facet);
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Node::IsOnFront() const
{
	return theFrontEdges_.Size();
}

inline 
void AutLib::MeshLib::Mesh3d_Node::SetCoord(const Geom_Pnt3d & Coord)
{
	theCoord_ = Coord;
}

inline 
void AutLib::MeshLib::Mesh3d_Node::SetIndex(const Standard_Integer Index)
{
	theIndex_ = Index;
}

inline 
void AutLib::MeshLib::Mesh3d_Node::SetRadius(const Standard_Real Value)
{
	theRadius_ = Value;
}

inline 
void AutLib::MeshLib::Mesh3d_Node::SetMaxAdjLength(const Standard_Real Value)
{
	theMaxL_ = Value;
}

inline
void AutLib::MeshLib::Mesh3d_Node::RetrieveFrontsTo(TColMesh3d_HAry1dOfEdge & Edges) const
{
	theFrontEdges_.RetrieveTo(Edges);
}

inline 
void AutLib::MeshLib::Mesh3d_Node::RetrieveFrontsTo(TColMesh3d_HAry1dOfFacet & Facets) const
{
	theFrontFacets_.RetrieveTo(Facets);
}

inline 
void AutLib::MeshLib::Mesh3d_Node::RetrieveFrontsTo(TColMesh3d_HBasicQueueOfEdge & theEdges) const
{
	theFrontEdges_.RetrieveTo(theEdges);
}

inline 
void AutLib::MeshLib::Mesh3d_Node::RetrievTo(TColMesh3d_HAry1dOfEdge & Edges) const
{
	theEdges_.RetrieveTo(Edges);
}

inline 
void AutLib::MeshLib::Mesh3d_Node::RetrieveTo(TColMesh3d_HAry1dOfFacet & Facets) const
{
	theFacets_.RetrieveTo(Facets);
}

inline 
void AutLib::MeshLib::Mesh3d_Node::RetrieveTo(TColMesh3d_HAry1dOfElement & Elements) const
{
	theElements_.RetrieveTo(Elements);
}

inline 
void AutLib::MeshLib::Mesh3d_Node::InsertToFronts(Global_Handle(Mesh3d_Edge) Edge)
{
	theFrontEdges_.Insert(Edge);
}

inline 
void AutLib::MeshLib::Mesh3d_Node::InsertToFronts(Global_Handle(Mesh3d_Facet) Facet)
{
	theFrontFacets_.Insert(Facet);
}

inline 
void AutLib::MeshLib::Mesh3d_Node::InsertToEdges(Global_Handle(Mesh3d_Edge) Edge)
{
	theEdges_.Insert(Edge);
}

inline 
void AutLib::MeshLib::Mesh3d_Node::InsertToFacets(Global_Handle(Mesh3d_Facet) Facet)
{
	theFacets_.Insert(Facet);
}

inline 
void AutLib::MeshLib::Mesh3d_Node::InsertToElements(Global_Handle(Mesh3d_Element) Element)
{
	theElements_.Insert(Element);
}

inline 
void AutLib::MeshLib::Mesh3d_Node::RemoveFromFronts(Global_Handle(Mesh3d_Edge) Edge)
{
	theFrontEdges_.Remove(Edge);
}

inline
void AutLib::MeshLib::Mesh3d_Node::RemoveFromFronts(Global_Handle(Mesh3d_Facet) Facet)
{
	theFrontFacets_.Remove(Facet);
}

inline 
void AutLib::MeshLib::Mesh3d_Node::RemoveFromEdges(Global_Handle(Mesh3d_Edge) Edge)
{
	theEdges_.Remove(Edge);
}

inline 
void AutLib::MeshLib::Mesh3d_Node::RemoveFromFacets(Global_Handle(Mesh3d_Facet) Facet)
{
	theFacets_.Remove(Facet);
}

inline
void AutLib::MeshLib::Mesh3d_Node::RemoveFromElements(Global_Handle(Mesh3d_Element) Element)
{
	theElements_.Remove(Element);
}