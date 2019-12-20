#pragma once
#include <Mesh3d_BoundaryNode.hxx>
#include <Mesh3d_BoundaryEdge.hxx>
#include <Mesh3d_BoundaryFacet.hxx>
inline
void AutLib::MeshLib::Mesh3d_TMesh::AttachToMeshNodes(Global_Handle(Mesh3d_Element) ElementPtr)
{
	Debug_Null_Pointer(ElementPtr);

	Get_Object(Element) = *ElementPtr;

	Element.Node(0)->InsertToElements(ElementPtr);
	Element.Node(1)->InsertToElements(ElementPtr);
	Element.Node(2)->InsertToElements(ElementPtr);
	Element.Node(3)->InsertToElements(ElementPtr);
}

inline 
void AutLib::MeshLib::Mesh3d_TMesh::AttachToMeshNodes(Global_Handle(Mesh3d_Facet) FacetPtr)
{
	Debug_Null_Pointer(FacetPtr);

	Get_Object(Facet) = *FacetPtr;

	Facet.Node0()->InsertToFacets(FacetPtr);
	Facet.Node1()->InsertToFacets(FacetPtr);
	Facet.Node2()->InsertToFacets(FacetPtr);
}

inline 
void AutLib::MeshLib::Mesh3d_TMesh::AttachToMeshNodes(Global_Handle(Mesh3d_Edge) EdgePtr)
{
	Debug_Null_Pointer(EdgePtr);

	Get_Object(Edge) = *EdgePtr;

	Edge.Node0()->InsertToEdges(EdgePtr);
	Edge.Node1()->InsertToEdges(EdgePtr);
}

inline 
void AutLib::MeshLib::Mesh3d_TMesh::AttachToMeshEdges(Global_Handle(Mesh3d_Element) ElementPtr)
{
	Debug_Null_Pointer(ElementPtr);

	Get_Object(Element) = *ElementPtr;

	Element.Edge(0)->InsertToElements(ElementPtr);
	Element.Edge(1)->InsertToElements(ElementPtr);
	Element.Edge(2)->InsertToElements(ElementPtr);
	Element.Edge(3)->InsertToElements(ElementPtr);
	Element.Edge(4)->InsertToElements(ElementPtr);
	Element.Edge(5)->InsertToElements(ElementPtr);
}

inline 
void AutLib::MeshLib::Mesh3d_TMesh::AttachToMeshEdges(Global_Handle(Mesh3d_Facet) FacetPtr)
{
	Debug_Null_Pointer(FacetPtr);

	Get_Object(Facet) = *FacetPtr;

	Facet.Edge0()->InsertToFacets(FacetPtr);
	Facet.Edge1()->InsertToFacets(FacetPtr);
	Facet.Edge2()->InsertToFacets(FacetPtr);
}

inline 
void AutLib::MeshLib::Mesh3d_TMesh::AttachToFrontNodes(Global_Handle(Mesh3d_Facet) FacetPtr)
{
	Debug_Null_Pointer(FacetPtr);

	Get_Object(Facet) = *FacetPtr;

	Facet.Node0()->InsertToFronts(FacetPtr);
	Facet.Node1()->InsertToFronts(FacetPtr);
	Facet.Node2()->InsertToFronts(FacetPtr);
}

inline 
void AutLib::MeshLib::Mesh3d_TMesh::AttachToFrontNodes(Global_Handle(Mesh3d_Edge) EdgePtr)
{
	Debug_Null_Pointer(EdgePtr);

	Get_Object(Edge) = *EdgePtr;

	Edge.Node0()->InsertToFronts(EdgePtr);
	Edge.Node1()->InsertToFronts(EdgePtr);
}

inline 
void AutLib::MeshLib::Mesh3d_TMesh::AttachToFrontEdges(Global_Handle(Mesh3d_Facet) FacetPtr)
{
	Debug_Null_Pointer(FacetPtr);

	Get_Object(Facet) = *FacetPtr;

	Facet.Edge0()->InsertToFronts(FacetPtr);
	Facet.Edge1()->InsertToFronts(FacetPtr);
	Facet.Edge2()->InsertToFronts(FacetPtr);
}

inline 
void AutLib::MeshLib::Mesh3d_TMesh::AttachToFront(Global_Handle(Mesh3d_Facet) Facet)
{
	Mesh3d_TMesh::AttachToFrontEdges(Facet);
	Mesh3d_TMesh::AttachToFrontNodes(Facet);
}

inline 
void AutLib::MeshLib::Mesh3d_TMesh::AttachToMesh(Global_Handle(Mesh3d_Facet) Facet)
{
	Mesh3d_TMesh::AttachToMeshNodes(Facet);
	Mesh3d_TMesh::AttachToMeshEdges(Facet);
}

inline 
void AutLib::MeshLib::Mesh3d_TMesh::deAttachFromMesh(Global_Handle(Mesh3d_Element) ElementPtr)
{
	Debug_Null_Pointer(ElementPtr);
	Get_Object(Element) = *ElementPtr;

	forThose
	(
		Index,
		0,
		3
	)
	{
		Debug_Null_Pointer(Element.Node(Index));
		Element.Node(Index)->RemoveFromElements(ElementPtr);
	}

	forThose
	(
		Index,
		0,
		5
	)
	{
		Debug_Null_Pointer(Element.Edge(Index));
		Element.Edge(Index)->RemoveFromElements(ElementPtr);
	}

	forThose
	(
		Index,
		0,
		3
	)
	{
		Debug_Null_Pointer(Element.Facet(Index));
		Get_Object(Facet) = *Element.Facet(Index);

		if (NOT Facet.RightElement() AND NOT Global_DownCast(Mesh3d_BoundaryFacet, Element.Facet(Index))) 
		{ THROW_STANDARD_EXCEPTION("Contradictory data"); }

		if (Facet.RightElement() EQUAL ElementPtr)
		{
			Facet.SetRightElement(NULL);
			Facet.Reverse();
		}
		else
		{
			Facet.SetLeftElement(NULL);
		}
	}

	forThose
	(
		Index,
		0,
		3
	)
	{
		Mesh3d_Element* Neighbor = Element.Neighbor(Index);
		if (Neighbor) { Neighbor->SetNeighbor(Neighbor->OppositeVertexIndex(ElementPtr), NULL); }
	}
}

inline 
void AutLib::MeshLib::Mesh3d_TMesh::deAttachFromMesh(Global_Handle(Mesh3d_Facet) FacetPtr)
{
	Debug_Null_Pointer(FacetPtr);

	Get_Const_Object(Facet) = *FacetPtr;

	if (Facet.LeftElement()) { THROW_STANDARD_EXCEPTION("Its not an orphan facet"); }
	if (Facet.RightElement()) { THROW_STANDARD_EXCEPTION("Its not an orphan facet"); }

	Facet.Node0()->RemoveFromFacets(FacetPtr);
	Facet.Node1()->RemoveFromFacets(FacetPtr);
	Facet.Node2()->RemoveFromFacets(FacetPtr);

	Facet.Edge0()->RemoveFromFacets(FacetPtr);
	Facet.Edge1()->RemoveFromFacets(FacetPtr);
	Facet.Edge2()->RemoveFromFacets(FacetPtr);


	// Remove from fronts	
	/*Facet.Node0()->RemoveFromFronts(FacetPtr);
	Facet.Node1()->RemoveFromFronts(FacetPtr);
	Facet.Node2()->RemoveFromFronts(FacetPtr);

	Facet.Edge0()->RemoveFromFronts(FacetPtr);
	Facet.Edge1()->RemoveFromFronts(FacetPtr);
	Facet.Edge2()->RemoveFromFronts(FacetPtr);*/
}

inline 
void AutLib::MeshLib::Mesh3d_TMesh::deAttachFromMesh(Global_Handle(Mesh3d_Edge) EdgePtr)
{
	Debug_Null_Pointer(EdgePtr);

	Get_Const_Object(Edge) = *EdgePtr;

	if (NOT Edge.IsFacetsEmpty() OR NOT Edge.IsFrontFacetsEmpty()) { THROW_STANDARD_EXCEPTION(" Its not an orphan edge"); }

	Edge.Node0()->RemoveFromEdges(EdgePtr);
	Edge.Node1()->RemoveFromEdges(EdgePtr);

	// Remove from fronts
	/*Edge.Node0()->RemoveFromFronts(EdgePtr);
	Edge.Node1()->RemoveFromFronts(EdgePtr);*/
}

inline 
void AutLib::MeshLib::Mesh3d_TMesh::deAttachFromFront(Global_Handle(Mesh3d_Facet) FacetPtr)
{
	Debug_Null_Pointer(FacetPtr);

	Get_Const_Object(Facet) = *FacetPtr;

	Debug_Null_Pointer(Facet.Node0());
	Debug_Null_Pointer(Facet.Node1());
	Debug_Null_Pointer(Facet.Node2());

	Debug_Null_Pointer(Facet.Edge0());
	Debug_Null_Pointer(Facet.Edge1());
	Debug_Null_Pointer(Facet.Edge2());

	Facet.Node0()->RemoveFromFronts(FacetPtr);
	Facet.Node1()->RemoveFromFronts(FacetPtr);
	Facet.Node2()->RemoveFromFronts(FacetPtr);

	Facet.Edge0()->RemoveFromFronts(FacetPtr);
	Facet.Edge1()->RemoveFromFronts(FacetPtr);
	Facet.Edge2()->RemoveFromFronts(FacetPtr);
}

inline 
void AutLib::MeshLib::Mesh3d_TMesh::deAttachFromFront(Global_Handle(Mesh3d_Edge) EdgePtr)
{
	Debug_Null_Pointer(EdgePtr);

	Get_Const_Object(Edge) = *EdgePtr;

	Edge.Node0()->RemoveFromFronts(EdgePtr);
	Edge.Node1()->RemoveFromFronts(EdgePtr);
}

inline
void AutLib::MeshLib::Mesh3d_TMesh::RemoveFromTopology
(
	Global_Handle(Mesh3d_Facet) theFacet,
	const Standard_Boolean BoundaryCheck
)
{
	Debug_Null_Pointer(theFacet);

	if (BoundaryCheck)
	{
		if (Global_DownCast(Mesh3d_BoundaryFacet, theFacet)) { return; }
	}

	if (NOT theFacet->IsOrphan()) { THROW_STANDARD_EXCEPTION(" The Facet is not orphan"); }

	// deAttatch from mesh
	Mesh3d_TMesh::deAttachFromMesh(theFacet);

	if (NOT theFacet->IsOnFront()) { THROW_STANDARD_EXCEPTION("The facet is not belong to the front"); }

	// deAttatch from front
	Mesh3d_TMesh::deAttachFromFront(theFacet);

	Mesh3d_Mesh::RemoveFromFronts(theFacet);

	Mesh3d_Mesh::RemoveFromMesh(theFacet);
}

inline 
void AutLib::MeshLib::Mesh3d_TMesh::RemoveFromTopology(Global_Handle(Mesh3d_Edge) theEdge, const Standard_Boolean BoundaryCheck)
{
	Debug_Null_Pointer(theEdge);

	if (BoundaryCheck)
	{
		if (Global_DownCast(Mesh3d_BoundaryEdge, theEdge)) { return; }
	}

	if (NOT theEdge->IsOrphan()) { THROW_STANDARD_EXCEPTION(" The edge is not orphan"); }

	// deAttatch from mesh
	Mesh3d_TMesh::deAttachFromMesh(theEdge);

	if (NOT theEdge->IsOnFront()) { THROW_STANDARD_EXCEPTION(" The edge is not belong to the front"); }

	// deAttatch from front
	Mesh3d_TMesh::deAttachFromFront(theEdge);

	Mesh3d_Mesh::RemoveFromMesh(theEdge);
}

inline
void AutLib::MeshLib::Mesh3d_TMesh::UpdateMaxLength
(
	const Standard_Real theLength,
	Mesh3d_Edge & theEdge
)
{
	theEdge.Node0()->SetMaxAdjLength(MAX(theLength, theEdge.Node0()->MaxAdjLength()));
	theEdge.Node1()->SetMaxAdjLength(MAX(theLength, theEdge.Node1()->MaxAdjLength()));
}