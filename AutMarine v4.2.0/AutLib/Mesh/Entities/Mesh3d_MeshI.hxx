#pragma once
#include <Mesh3d_MeshTools.hxx>
inline
Standard_Integer AutLib::MeshLib::Mesh3d_Mesh::NbNodes() const
{
	return theNbNodes_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Mesh::NbEdges() const
{
	return theNbEdges_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Mesh::NbFacets() const
{
	return theNbFacets_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Mesh::NbElements() const
{
	return theNbElements_;
}

inline 
Standard_Integer & AutLib::MeshLib::Mesh3d_Mesh::NbNodes()
{
	return theNbNodes_;
}

inline 
Standard_Integer & AutLib::MeshLib::Mesh3d_Mesh::NbEdges()
{
	return theNbEdges_;
}

inline 
Standard_Integer & AutLib::MeshLib::Mesh3d_Mesh::NbFacets()
{
	return theNbFacets_;
}

inline 
Standard_Integer & AutLib::MeshLib::Mesh3d_Mesh::NbElements()
{
	return theNbElements_;
}

inline 
Standard_String AutLib::MeshLib::Mesh3d_Mesh::Name() const
{
	return theName_;
}

inline
void AutLib::MeshLib::Mesh3d_Mesh::InsertToMesh(const TColMesh3d_HAry1dOfNode & theNodes)
{
	theNodes_.Insert(theNodes);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::InsertToMesh(const TColMesh3d_HAry1dOfEdge & theEdges)
{
	forThose(Index, 0, MaxIndexOf(theEdges))
		Mesh3d_Mesh::InsertToMesh(theEdges[Index]);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::InsertToMesh(const TColMesh3d_HAry1dOfFacet & theFacets)
{
	forThose(Index, 0, MaxIndexOf(theFacets))
		Mesh3d_Mesh::InsertToMesh(theFacets[Index]);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::InsertToMesh(const TColMesh3d_HAry1dOfElement & theElements)
{
	forThose(Index, 0, MaxIndexOf(theElements))
		Mesh3d_Mesh::InsertToMesh(theElements[Index]);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::InsertToFronts(const TColMesh3d_HAry1dOfNode & theNodes)
{
	theFrontNodes_.Insert(theNodes);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::InsertToFronts(const TColMesh3d_HAry1dOfFacet & theFacets)
{
	forThose(Index, 0, MaxIndexOf(theFacets))
		Mesh3d_Mesh::InsertToFronts(theFacets[Index]);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::RemoveFromMesh(const TColMesh3d_HAry1dOfNode & theNodes)
{
	forThose(Index, 0, MaxIndexOf(theNodes))
		Mesh3d_Mesh::RemoveFromMesh(theNodes[Index]);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::RemoveFromMesh(const TColMesh3d_HAry1dOfEdge & theEdges)
{
	forThose(Index, 0, MaxIndexOf(theEdges))
		Mesh3d_Mesh::RemoveFromMesh(theEdges[Index]);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::RemoveFromMesh(const TColMesh3d_HAry1dOfFacet & theFacets)
{
	forThose(Index, 0, MaxIndexOf(theFacets))
		Mesh3d_Mesh::RemoveFromMesh(theFacets[Index]);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::RemoveFromMesh(const TColMesh3d_HAry1dOfElement & theElements)
{
	forThose(Index, 0, MaxIndexOf(theElements))
		Mesh3d_Mesh::RemoveFromMesh(theElements[Index]);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::RemoveFromFronts(const TColMesh3d_HAry1dOfNode & theNodes)
{
	forThose(Index, 0, MaxIndexOf(theNodes))
		Mesh3d_Mesh::RemoveFromFronts(theNodes[Index]);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::RemoveFromFronts(const TColMesh3d_HAry1dOfFacet & theFacets)
{
	forThose(Index, 0, MaxIndexOf(theFacets))
		Mesh3d_Mesh::RemoveFromFronts(theFacets[Index]);
}

inline
void AutLib::MeshLib::Mesh3d_Mesh::InsertToMesh(Global_Handle(Mesh3d_Node) theNode)
{
	theNodes_.Insert(theNode);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::InsertToMesh(Global_Handle(Mesh3d_Edge) theEdge)
{
	Debug_If_Condition(Mesh3d_MeshTools::CheckToInsertToMesh(theEdge));
	theEdges_.Insert(theEdge);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::InsertToMesh(Global_Handle(Mesh3d_Facet) theFacet)
{
	Debug_If_Condition(Mesh3d_MeshTools::CheckToInsertToMesh(theFacet));
	theFacets_.Insert(theFacet);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::InsertToMesh(Global_Handle(Mesh3d_Element) theElement)
{
	Debug_If_Condition(Mesh3d_MeshTools::CheckToInsertToMesh(theElement));
	theElements_.Insert(theElement);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::InsertToFronts(Global_Handle(Mesh3d_Node) theNode)
{
	theFrontNodes_.Insert(theNode);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::InsertToFronts(Global_Handle(Mesh3d_Facet) theFacet)
{
	Debug_If_Condition(Mesh3d_MeshTools::CheckToInsertToFront(theFacet));
	theFrontFacets_.Insert(theFacet);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::RemoveFromMesh(Global_Handle(Mesh3d_Node) theNode)
{
	Debug_If_Condition(Mesh3d_MeshTools::CheckToRemoveFromMesh(theNode));
	theNodes_.Remove(theNode);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::RemoveFromMesh(Global_Handle(Mesh3d_Edge) theEdge)
{
	Debug_If_Condition(Mesh3d_MeshTools::CheckToRemoveFromMesh(theEdge));
	theEdges_.Remove(theEdge);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::RemoveFromMesh(Global_Handle(Mesh3d_Facet) theFacet)
{
	Debug_If_Condition(Mesh3d_MeshTools::CheckToRemoveFromMesh(theFacet));
	theFacets_.Remove(theFacet);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::RemoveFromMesh(Global_Handle(Mesh3d_Element) theElement)
{
	Debug_If_Condition(Mesh3d_MeshTools::CheckToRemoveFromMesh(theElement));
	theElements_.Remove(theElement);
}

inline
void AutLib::MeshLib::Mesh3d_Mesh::RemoveFromFronts(Global_Handle(Mesh3d_Node) theNode)
{
	Debug_If_Condition(Mesh3d_MeshTools::CheckToRemoveFromFront(theNode));
	theFrontNodes_.Remove(theNode);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::RemoveFromFronts(Global_Handle(Mesh3d_Facet) theFacet)
{
	Debug_If_Condition(Mesh3d_MeshTools::CheckToRemoveFromFront(theFacet));
	theFrontFacets_.Remove(theFacet);
}

inline
void AutLib::MeshLib::Mesh3d_Mesh::RetrieveTo(TColMesh3d_HAry1dOfNode & Nodes) const
{
	theNodes_.RetrieveTo(Nodes);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::RetrieveTo(TColMesh3d_HAry1dOfEdge & Edges) const
{
	theEdges_.RetrieveTo(Edges);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::RetrieveTo(TColMesh3d_HAry1dOfFacet & Facets) const
{
	theFacets_.RetrieveTo(Facets);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::RetrieveTo(TColMesh3d_HAry1dOfElement & Elements) const
{
	theElements_.RetrieveTo(Elements);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::RetrieveFrontsTo(TColMesh3d_HAry1dOfNode & Nodes) const
{
	theFrontNodes_.RetrieveTo(Nodes);
}

inline 
void AutLib::MeshLib::Mesh3d_Mesh::RetrieveFrontsTo(TColMesh3d_HAry1dOfFacet & Facets) const
{
	theFrontFacets_.RetrieveTo(Facets);
}
