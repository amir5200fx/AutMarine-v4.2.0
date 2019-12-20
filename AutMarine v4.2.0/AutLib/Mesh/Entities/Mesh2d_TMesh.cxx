#include <Mesh2d_TMesh.hxx>

#include <Geometry_Tools.hxx>
#include <Mesh2d_Node.hxx>
#include <Mesh2d_NodeTools.hxx>
#include <Mesh2d_EdgeTools.hxx>
#include <Mesh2d_SizeMap.hxx>
#include <TColMesh2d_HBasicQueueOfNode.hxx>
#include <TColMesh2d_HBasicQueueOfEdge.hxx>

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

AutLib::MeshLib::Mesh2d_TMesh::Mesh2d_TMesh()
{
}

AutLib::MeshLib::Mesh2d_TMesh::~Mesh2d_TMesh()
{
}

Global_Handle(Mesh2d_Element) AutLib::MeshLib::Mesh2d_TMesh::AddToTopology
(
	Global_Handle(Mesh2d_Edge) theFront, 
	Global_Handle(Mesh2d_Node) theNode, 
	const Mesh2d_SizeMap & theSizeMap,
	const Standard_Boolean RemoveFromFront
)
{
	theInfo_.Reset();

	if (RemoveFromFront)
	{
		//! deAttach the current from fronts
		deAttachFromFront(theFront);

		//! Remove the current from fronts
		RemoveFromFronts(theFront);
	}

	theInfo_.SetCurrent(theFront);
	theInfo_.SetValidNode(theNode);

	SetPairedEdges();

	Try_Exception_Handle_Exit(UpdateEdges(theSizeMap));

	CreateElement();

	UpdateElement();

	// remove non-GF nodes from the ADT
	Debug_Null_Pointer(theInfo_.CreatedElement());
	Get_Object(theElement) = *theInfo_.CreatedElement();

	if (Geometry_Tools::SignedAreaOfTriangle(theElement.Node0()->Coord(), theElement.Node1()->Coord(), theElement.Node2()->Coord()) <= 0)
	{
		THROW_STANDARD_EXCEPTION("Reversed Element");
	}

	forThose
	(
		Index,
		0,
		2
	)
	{
		Debug_Null_Pointer(theElement.Node(Index));

		if (theElement.Node(Index)->IsEmptyFront())
		{
			Try_Exception_Handle_Exit(RemoveFromFronts(theElement.Node(Index)));
		}
	}
	return theInfo_.CreatedElement();
}

void AutLib::MeshLib::Mesh2d_TMesh::ForcedToRemoveFromTopology
(
	Global_Handle(Mesh2d_Edge) theEdge, 
	const Standard_Boolean BoundaryChecking
)
{
	Debug_Null_Pointer(theEdge);

	if (Global_DownCast(Mesh2d_BoundaryEdge, theEdge)) { return; }

	TColMesh2d_HAry1dOfElement Elements(2);
	Elements[0] = theEdge->LeftElement();
	Elements[1] = theEdge->RightElement();

	forThose
	(
		Index,
		0,
		MaxIndexOf(Elements)
	)
	{
		Debug_Null_Pointer(Elements[Index]);

		TColMesh2d_HAry1dOfNode RetrieveNodes, RemoveNodes;
		TColMesh2d_HAry1dOfEdge RetrieveEdges, RemoveEdges;

		RemoveFromTopology
		(
			Elements[Index],
			RetrieveEdges,
			RetrieveNodes,
			RemoveEdges,
			RemoveNodes,
			Standard_True
		);
	}
}

void AutLib::MeshLib::Mesh2d_TMesh::RemoveFromTopology
(
	Global_Handle(Mesh2d_Element) theElement,
	TColMesh2d_HAry1dOfEdge & theRetrievedEdges,
	TColMesh2d_HAry1dOfNode & theRetrievedNodes,
	TColMesh2d_HAry1dOfEdge & theRemovedEdges,
	TColMesh2d_HAry1dOfNode & theRemovedNodes,
	const Standard_Boolean BoundaryChecking
)
{
	Debug_Null_Pointer(theElement);
	Get_Const_Object(Element) = *theElement;

	TColMesh2d_HBasicQueueOfNode QRetrievedNodes;
	forThose
	(
		Index,
		0,
		2
	)
	{
		Debug_Null_Pointer(Element.Node(Index));
		Get_Const_Object(Node) = Element.Node(Index);

		if (NOT Node->IsOnFront())
		{
			Try_Exception_Handle_Exit(Mesh2d_Mesh::InsertToFronts(Node));
			QRetrievedNodes.EnQueue(Node);
		}
	}
	QRetrievedNodes.RetrieveTo(theRetrievedNodes);

	Try_Exception_Handle_Exit(Mesh2d_TMesh::deAttachFromMesh(theElement));
	Try_Exception_Handle_Exit(Mesh2d_Mesh::RemoveFromMesh(theElement));

	TColMesh2d_HBasicQueueOfEdge QRetrievedEdges;
	TColMesh2d_HBasicQueueOfEdge QRemovedEdges;
	forThose
	(
		Index,
		0,
		2
	)
	{
		Debug_Null_Pointer(Element.Edge(Index));
		Get_Const_Object(Edge) = Element.Edge(Index);

		if (Edge->IsOrphan() AND NOT Mesh2d_EdgeTools::IsOnBoundary(Edge))
		{
			Try_Exception_Handle_Exit(Mesh2d_TMesh::RemoveFromTopology(Edge, BoundaryChecking));
			QRemovedEdges.EnQueue(Edge);
		}
		else
		{
			if (NOT Edge->IsOnFront())
			{
				Try_Exception_Handle_Exit(Mesh2d_TMesh::AttachToFrontNodes(Edge));
				QRetrievedEdges.EnQueue(Edge);
			}
		}
	}
	QRetrievedEdges.RetrieveTo(theRetrievedEdges);
	QRemovedEdges.RetrieveTo(theRemovedEdges);

	TColMesh2d_HBasicQueueOfNode QRemovedNodes;
	forThose
	(
		Index,
		0,
		2
	)
	{
		Debug_Null_Pointer(Element.Node(Index));
		Get_Const_Object(Node) = Element.Node(Index);

		if (NOT Node->NbElements() AND NOT Mesh2d_NodeTools::IsOnBoundary(Node))
		{
			Try_Exception_Handle_Exit(Mesh2d_Mesh::RemoveFromFronts(Node));
			Try_Exception_Handle_Exit(Mesh2d_Mesh::RemoveFromMesh(Node));

			QRemovedNodes.EnQueue(Node);
		}
	}
	QRemovedNodes.RetrieveTo(theRemovedNodes);
}

void AutLib::MeshLib::Mesh2d_TMesh::SetPairedEdges()
{
	theInfo_.SetCreatedEdge0(NULL);
	theInfo_.SetCreatedEdge1(NULL);

	theInfo_.SetPairedEdge0(NULL);
	theInfo_.SetPairedEdge1(NULL);

	Get_Const_Object(CurrentEdge) = *theInfo_.Current();

	Standard_Integer Vn = theInfo_.ValidNode()->Index();

	Debug_Null_Pointer(CurrentEdge.Node0());
	Debug_Null_Pointer(CurrentEdge.Node1());

	Standard_Integer V0 = CurrentEdge.Node0()->Index();
	Standard_Integer V1 = CurrentEdge.Node1()->Index();

	TColMesh2d_HBasicQueueOfEdge QEdges;
	theInfo_.ValidNode()->RetrieveFrontsTo(QEdges);

	Global_Handle(Mesh2d_Edge) Edge;
	while (QEdges.DeQueue(Edge))
	{
		Debug_Null_Pointer(Edge);
		Get_Const_Object(theEdge) = *Edge;

		Standard_Integer E0 = theEdge.Node0()->Index();
		Standard_Integer E1 = theEdge.Node1()->Index();

		if (M_GEO Geometry_Tools::IsPairedTwoLineSegment(E0, E1, V0, Vn))
		{
			theInfo_.SetPairedEdge1(Edge);
		}

		if (M_GEO Geometry_Tools::IsPairedTwoLineSegment(E0, E1, V1, Vn))
		{
			theInfo_.SetPairedEdge0(Edge);
		}
	}
}

void AutLib::MeshLib::Mesh2d_TMesh::UpdateEdges(const Mesh2d_SizeMap & theSizeMap)
{
	Get_Const_Object(CurrentEdge) = *theInfo_.Current();

	Global_Handle(Mesh2d_Edge) Edge = theInfo_.PairedEdge0();

	if (Edge)
	{
		theInfo_.SetCreatedEdge0(NULL);

		// remove the old coicident face from the GF
		Try_Exception_Handle_Exit(deAttachFromFront(Edge));
		//Try_Exception_Handle_Exit(Mesh.RemoveFromFronts(Edge));

		// remove cavity face
		if (Edge->IsCavity())
		{
			Edge->SetCavity(Standard_False);
		}
	}
	else
	{
		NbEdges()++;

		Get_Const_Object(P1) = theInfo_.ValidNode()->Coord();
		Get_Const_Object(P2) = CurrentEdge.Node1()->Coord();

		Standard_Real Length = theSizeMap.CalcDistance(P1, P2);

		Global_Handle(Mesh2d_Edge) newEdge = new Mesh2d_Edge
		(
			NbEdges(),
			Length,
			theSizeMap.CalcCentreOf(P1, P2),
			theInfo_.ValidNode(),
			CurrentEdge.Node1()
		);

		theInfo_.SetCreatedEdge0(newEdge);

		// insert the new Face into the FACES TREE
		AttachToFrontNodes(newEdge);
		AttachToMeshNodes(newEdge);

		InsertToMesh(newEdge);
	}

	Edge = theInfo_.PairedEdge1();

	if (Edge)
	{
		theInfo_.SetCreatedEdge1(NULL);

		// remove the old coicident face from the GF
		Try_Exception_Handle_Exit(deAttachFromFront(Edge));
		//Try_Exception_Handle_Exit(Mesh.RemoveFromFronts(Edge));

		// remove cavity face
		if (Edge->IsCavity())
		{
			Edge->SetCavity(Standard_False);
		}
	}
	else
	{
		NbEdges()++;

		Get_Const_Object(P1) = theInfo_.ValidNode()->Coord();
		Get_Const_Object(P2) = CurrentEdge.Node0()->Coord();

		Standard_Real Length = theSizeMap.CalcDistance(P1, P2);

		Global_Handle(Mesh2d_Edge) newEdge = new Mesh2d_Edge
		(
			NbEdges(),
			Length,
			theSizeMap.CalcCentreOf(P1, P2),
			CurrentEdge.Node0(),
			theInfo_.ValidNode()
		);

		theInfo_.SetCreatedEdge1(newEdge);

		// insert the new Face into the FACES TREE
		AttachToFrontNodes(newEdge);
		AttachToMeshNodes(newEdge);

		InsertToMesh(newEdge);
	}
}

void AutLib::MeshLib::Mesh2d_TMesh::CreateElement()
{
	NbElements()++;
	Global_Handle(Mesh2d_Element) theElement = new Mesh2d_Element(NbElements());

	Debug_Null_Pointer(theElement);
	Get_Object(Element) = *theElement;

	Debug_Null_Pointer(theInfo_.Current());
	Get_Const_Object(Current) = *theInfo_.Current();

	Element.SetNode(0, Current.Node0());
	Element.SetNode(1, Current.Node1());
	Element.SetNode(2, theInfo_.ValidNode());

	if (theInfo_.IsCreatedEdge0()) { Element.SetEdge(0, theInfo_.CreatedEdge0()); }
	else { Element.SetEdge(0, theInfo_.PairedEdge0()); }

	if (theInfo_.IsCreatedEdge1()) { Element.SetEdge(1, theInfo_.CreatedEdge1()); }
	else { Element.SetEdge(1, theInfo_.PairedEdge1()); }

	Element.SetEdge(2, theInfo_.Current());

	theInfo_.SetCreatedElement(theElement);
}

void AutLib::MeshLib::Mesh2d_TMesh::UpdateElement()
{
	Global_Handle(Mesh2d_Element) theElement = theInfo_.CreatedElement();
	Debug_Null_Pointer(theElement);

	AttachToMeshNodes(theElement);

	/* Attach the element to the edges */

	Get_Object(theCurrent) = *theInfo_.Current();

	// update right/ left side element pointer of the faces
	// update adjacent elements
	theCurrent.SetLeftElement(theElement);
	theElement->SetNeighbor(2, theCurrent.RightElement());

	if (theCurrent.RightElement())
	{
		theCurrent.RightElement()->SetNeighbor(theCurrent.RightElement()->OppositeVertexIndex(theCurrent), theElement);
	}

	if (theInfo_.IsCreatedEdge0())
	{
		theInfo_.CreatedEdge0()->SetRightElement(theElement);
		theElement->SetNeighbor(0, NULL);
	}
	else
	{
		Global_Handle(Mesh2d_Edge) Edge = theInfo_.PairedEdge0();
		Debug_Null_Pointer(Edge);

		Global_Handle(Mesh2d_Element) Neighbor0 = Edge->RightElement();
		theElement->SetNeighbor(0, Neighbor0);

		if (Edge->LeftElement()) { THROW_STANDARD_EXCEPTION("Contradiction data"); }

		Edge->SetLeftElement(theElement);

		if (Neighbor0) { Neighbor0->SetNeighbor(Neighbor0->OppositeVertexIndex(*Edge), theElement); }
	}

	if (theInfo_.IsCreatedEdge1())
	{
		theInfo_.CreatedEdge1()->SetRightElement(theElement);
		theElement->SetNeighbor(1, NULL);
	}
	else
	{
		Global_Handle(Mesh2d_Edge) Edge = theInfo_.PairedEdge1();
		Debug_Null_Pointer(Edge);

		Global_Handle(Mesh2d_Element) Neighbor1 = Edge->RightElement();
		theElement->SetNeighbor(1, Neighbor1);

		if (Edge->LeftElement()) { THROW_STANDARD_EXCEPTION("Contradiction data"); }

		Edge->SetLeftElement(theElement);

		if (Neighbor1) { Neighbor1->SetNeighbor(Neighbor1->OppositeVertexIndex(*Edge), theElement); }
	}

	// updating the ELMENTS TREE
	InsertToMesh(theElement);
}