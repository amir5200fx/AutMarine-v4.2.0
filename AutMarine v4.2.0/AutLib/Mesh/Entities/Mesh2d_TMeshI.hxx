#pragma once
#include <Mesh2d_EdgeTools.hxx>
inline
void AutLib::MeshLib::Mesh2d_TMesh::AttachToMeshNodes(Global_Handle(Mesh2d_Element) ElementPtr)
{
	Debug_Null_Pointer(ElementPtr);

	Get_Object(Element) = *ElementPtr;

	Element.Node(0)->InsertToElements(ElementPtr);
	Element.Node(1)->InsertToElements(ElementPtr);
	Element.Node(2)->InsertToElements(ElementPtr);
}

inline 
void AutLib::MeshLib::Mesh2d_TMesh::AttachToMeshNodes(Global_Handle(Mesh2d_Edge) EdgePtr)
{
	Debug_Null_Pointer(EdgePtr);

	Get_Object(Edge) = *EdgePtr;

	Edge.Node0()->InsertToEdges(EdgePtr);
	Edge.Node1()->InsertToEdges(EdgePtr);
}

inline
void
AutLib::MeshLib::Mesh2d_TMesh::AttachToFrontNodes(Global_Handle(Mesh2d_Edge) EdgePtr)
{
	Debug_Null_Pointer(EdgePtr);

	Get_Object(Edge) = *EdgePtr;

	Edge.Node0()->InsertToFronts(EdgePtr);
	Edge.Node1()->InsertToFronts(EdgePtr);
}

inline 
void AutLib::MeshLib::Mesh2d_TMesh::deAttachFromMesh(Global_Handle(Mesh2d_Element) ElementPtr)
{
	Debug_Null_Pointer(ElementPtr);

	Get_Object(Element) = *ElementPtr;

	Debug_Null_Pointer(Element.Node(0));
	Debug_Null_Pointer(Element.Node(1));
	Debug_Null_Pointer(Element.Node(2));

	Element.Node(0)->RemoveFromElements(ElementPtr);
	Element.Node(1)->RemoveFromElements(ElementPtr);
	Element.Node(2)->RemoveFromElements(ElementPtr);

	Debug_Null_Pointer(Element.Edge(0));
	Debug_Null_Pointer(Element.Edge(1));
	Debug_Null_Pointer(Element.Edge(2));

	Get_Object(Edge0) = *Element.Edge(0);
	Get_Object(Edge1) = *Element.Edge(1);
	Get_Object(Edge2) = *Element.Edge(2);

	if (NOT Edge0.RightElement() AND NOT Mesh2d_EdgeTools::IsOnBoundary(Element.Edge(0))) { THROW_STANDARD_EXCEPTION("Contradictory data"); }
	if (NOT Edge1.RightElement() AND NOT Mesh2d_EdgeTools::IsOnBoundary(Element.Edge(1))) { THROW_STANDARD_EXCEPTION("Contradictory data"); }
	if (NOT Edge2.RightElement() AND NOT Mesh2d_EdgeTools::IsOnBoundary(Element.Edge(2))) { THROW_STANDARD_EXCEPTION("Contradictory data"); }

	if (Edge0.RightElement() EQUAL ElementPtr)
	{
		Edge0.SetRightElement(NULL);
		Edge0.Reverse();
	}
	else
	{
		Edge0.SetLeftElement(NULL);
	}

	if (Edge1.RightElement() EQUAL ElementPtr)
	{
		Edge1.SetRightElement(NULL);
		Edge1.Reverse();
	}
	else
	{
		Edge1.SetLeftElement(NULL);
	}

	if (Edge2.RightElement() EQUAL ElementPtr)
	{
		Edge2.SetRightElement(NULL);
		Edge2.Reverse();
	}
	else
	{
		Edge2.SetLeftElement(NULL);
	}

	Mesh2d_Element* Neighbor0 = Element.Neighbor(0);
	Mesh2d_Element* Neighbor1 = Element.Neighbor(1);
	Mesh2d_Element* Neighbor2 = Element.Neighbor(2);

	if (Neighbor0) { Neighbor0->SetNeighbor(Neighbor0->OppositeVertexIndex(*ElementPtr), NULL); }
	if (Neighbor1) { Neighbor1->SetNeighbor(Neighbor1->OppositeVertexIndex(*ElementPtr), NULL); }
	if (Neighbor2) { Neighbor2->SetNeighbor(Neighbor2->OppositeVertexIndex(*ElementPtr), NULL); }
}

inline 
void AutLib::MeshLib::Mesh2d_TMesh::deAttachFromMesh(Global_Handle(Mesh2d_Edge) EdgePtr)
{
	Debug_Null_Pointer(EdgePtr);

	Get_Const_Object(Edge) = *EdgePtr;

	if (Edge.RightElement() OR Edge.LeftElement()) { THROW_STANDARD_EXCEPTION(" Its not an orphan edge"); }

	Edge.Node0()->RemoveFromEdges(EdgePtr);
	Edge.Node1()->RemoveFromEdges(EdgePtr);
}

inline 
void AutLib::MeshLib::Mesh2d_TMesh::deAttachFromFront(Global_Handle(Mesh2d_Edge) EdgePtr)
{
	Debug_Null_Pointer(EdgePtr);

	Get_Const_Object(Edge) = *EdgePtr;

	Edge.Node0()->RemoveFromFronts(EdgePtr);
	Edge.Node1()->RemoveFromFronts(EdgePtr);
}

inline 
void AutLib::MeshLib::Mesh2d_TMesh::RemoveFromTopology(Global_Handle(Mesh2d_Edge) theEdge, const Standard_Boolean BoundaryCheck)
{
	Debug_Null_Pointer(theEdge);

	if (BoundaryCheck)
	{
		if (Mesh2d_EdgeTools::IsOnBoundary(theEdge)) { return; }
	}

	if (NOT theEdge->IsOrphan()) { THROW_STANDARD_EXCEPTION(" The edge is not orphan"); }

	// deAttatch from mesh
	Mesh2d_TMesh::deAttachFromMesh(theEdge);

	if (NOT theEdge->IsOnFront()) { THROW_STANDARD_EXCEPTION(" The edge is not belong to the front"); }

	// deAttatch from front
	Mesh2d_TMesh::deAttachFromFront(theEdge);

	Mesh2d_Mesh::RemoveFromMesh(theEdge);
}

inline
void AutLib::MeshLib::Mesh2d_TMesh::UpdateMaxLength
(
	const Standard_Real theLength,
	Mesh2d_Edge & theEdge
)
{
	theEdge.Node0()->SetMaxAdjLength(MAX(theLength, theEdge.Node0()->MaxAdjLength()));
	theEdge.Node1()->SetMaxAdjLength(MAX(theLength, theEdge.Node1()->MaxAdjLength()));
}