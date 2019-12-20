#pragma once
#ifndef USE_INDEX_NUMBERING
inline
AutLib::MeshLib::Mesh3d_Edge::Mesh3d_Edge()
	: theIndex_(0)
	, theLength_(0)
	, IsCavity_(Standard_False)
{
	theNodes_[0] = NULL;
	theNodes_[1] = NULL;
}

inline
AutLib::MeshLib::Mesh3d_Edge::Mesh3d_Edge
(
	const Standard_Integer Index,
	const Standard_Real Length,
	Global_Handle(Mesh3d_Node) Node0,
	Global_Handle(Mesh3d_Node) Node1
)
	: theIndex_(Index)
	, theLength_(Length)
	, IsCavity_(Standard_False)
{
	theNodes_[0] = Node0;
	theNodes_[1] = Node1;
}

#endif

inline 
Geom_Pnt3d AutLib::MeshLib::Mesh3d_Edge::Centre() const
{
	return MEAN(Node0()->Coord(), Node1()->Coord());
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Edge::Index() const
{
	return theIndex_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Edge::NbFrontFacets() const
{
	return theFrontFacet_.Size();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Edge::NbFacets() const
{
	return theFacets_.Size();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Edge::NbElements() const
{
	return theElements_.Size();
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_Edge::Length() const
{
	return theLength_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Edge::IsCavity() const
{
	return IsCavity_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Edge::IsOnFront() const
{
	Debug_Null_Pointer(Node0());
	return Node0()->IsContainAtFront((Global_Handle(Mesh3d_Edge))this);
}

inline 
M_AUT TColMesh3d_HAry1dOfFacet AutLib::MeshLib::Mesh3d_Edge::RetrieveFrontFacets() const
{
	return theFrontFacet_.Retrieve();
}

inline 
M_AUT TColMesh3d_HAry1dOfFacet AutLib::MeshLib::Mesh3d_Edge::RetrieveFacets() const
{
	return theFacets_.Retrieve();
}

inline 
M_AUT TColMesh3d_HAry1dOfElement AutLib::MeshLib::Mesh3d_Edge::RetrieveElements() const
{
	return theElements_.Retrieve();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Edge::IsFrontFacetsEmpty() const
{
	return theFrontFacet_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Edge::IsOrphan() const
{
	if (NOT NbElements()) { return Standard_True; }
	return Standard_False;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Edge::IsFacetsEmpty() const
{
	return theFacets_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Edge::IsElementsEmpty() const
{
	return theElements_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Edge::IsContainAtMesh(Global_Handle(Mesh3d_Facet) theFacet) const
{
	Debug_Null_Pointer(theFacet);
	return theFacets_.IsContains(theFacet);
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Edge::IsContainAtMesh(Global_Handle(Mesh3d_Element) theElement) const
{
	Debug_Null_Pointer(theElement);
	return theElements_.IsContains(theElement);
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Edge::IsContainAtFront(Global_Handle(Mesh3d_Facet) Facet) const
{
	Debug_Null_Pointer(Facet);
	return theFrontFacet_.IsContains(Facet);
}

inline 
Global_Handle(M_MESH Mesh3d_Node) AutLib::MeshLib::Mesh3d_Edge::Node0() const
{
	return theNodes_[0];
}

inline 
Global_Handle(M_MESH Mesh3d_Node) AutLib::MeshLib::Mesh3d_Edge::Node1() const
{
	return theNodes_[1];
}

inline 
Global_Handle(M_MESH Mesh3d_Node) AutLib::MeshLib::Mesh3d_Edge::Node(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 1);
	return theNodes_[Index];
}

inline 
Global_Handle(M_MESH Mesh3d_Node)& AutLib::MeshLib::Mesh3d_Edge::Node(const Standard_Integer Index)
{
	Debug_Bad_Index(Index, 0, 1);
	return theNodes_[Index];
}

inline 
void AutLib::MeshLib::Mesh3d_Edge::Reverse()
{
	SWAP(theNodes_[0], theNodes_[1]);
}

inline 
void AutLib::MeshLib::Mesh3d_Edge::SetAsCavity()
{
	IsCavity_ = Standard_True;
}

inline 
void AutLib::MeshLib::Mesh3d_Edge::SetAsNotCavity()
{
	IsCavity_ = Standard_False;
}

inline 
void AutLib::MeshLib::Mesh3d_Edge::SetIndex(const Standard_Integer Index)
{
	theIndex_ = Index;
}

inline 
void AutLib::MeshLib::Mesh3d_Edge::SetLength(const Standard_Real Length)
{
	theLength_ = Length;
}

inline 
void AutLib::MeshLib::Mesh3d_Edge::SetNode(const Standard_Integer Index, Global_Handle(Mesh3d_Node) Node)
{
	Debug_Bad_Index(Index, 0, 1);
	theNodes_[Index] = Node;
}

inline 
void AutLib::MeshLib::Mesh3d_Edge::RetrieveFrontsTo(TColMesh3d_HAry1dOfFacet & Facets) const
{
	theFrontFacet_.RetrieveTo(Facets);
}

inline 
void AutLib::MeshLib::Mesh3d_Edge::RetrieveFrontsTo(TColMesh3d_HBasicQueueOfFacet & theFacets) const
{
	theFrontFacet_.RetrieveTo(theFacets);
}

inline 
void AutLib::MeshLib::Mesh3d_Edge::RetrieveTo(TColMesh3d_HAry1dOfFacet & Facets) const
{
	theFacets_.RetrieveTo(Facets);
}

inline 
void AutLib::MeshLib::Mesh3d_Edge::RetrieveTo(TColMesh3d_HAry1dOfElement & Elements) const
{
	theElements_.RetrieveTo(Elements);
}

inline 
void AutLib::MeshLib::Mesh3d_Edge::InsertToFronts(Global_Handle(Mesh3d_Facet) Facet)
{
	theFrontFacet_.Insert(Facet);
}

inline 
void AutLib::MeshLib::Mesh3d_Edge::InsertToFacets(Global_Handle(Mesh3d_Facet) Facet)
{
	theFacets_.Insert(Facet);
}

inline 
void AutLib::MeshLib::Mesh3d_Edge::InsertToElements(Global_Handle(Mesh3d_Element) Element)
{
	theElements_.Insert(Element);
}

inline 
void AutLib::MeshLib::Mesh3d_Edge::RemoveFromFronts(Global_Handle(Mesh3d_Facet) Facet)
{
	theFrontFacet_.Remove(Facet);
}

inline 
void AutLib::MeshLib::Mesh3d_Edge::RemoveFromFacets(Global_Handle(Mesh3d_Facet) Facet)
{
	theFacets_.Remove(Facet);
}

inline
void AutLib::MeshLib::Mesh3d_Edge::RemoveFromElements(Global_Handle(Mesh3d_Element) Element)
{
	theElements_.Remove(Element);
}