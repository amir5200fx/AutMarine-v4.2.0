#include <Mesh3d_TMesh.hxx>

#include <Geometry_Tools.hxx>
#include <Mesh3d_BoundaryNode.hxx>
#include <Mesh3d_BoundaryEdge.hxx>
#include <Mesh3d_BoundaryFacet.hxx>
#include <Mesh3d_SizeMap.hxx>
#include <TColMesh3d_HBasicQueueOfNode.hxx>
#include <TColMesh3d_HBasicQueueOfEdge.hxx>
#include <TColMesh3d_HBasicQueueOfFacet.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::MeshLib::Mesh3d_TMesh::Mesh3d_TMesh()
{
}

AutLib::MeshLib::Mesh3d_TMesh::~Mesh3d_TMesh()
{
}

Global_Handle(Mesh3d_Element) AutLib::MeshLib::Mesh3d_TMesh::AddToTopology
(
	Global_Handle(Mesh3d_Facet) theFront,
	Global_Handle(Mesh3d_Node) theNode,
	const Mesh3d_SizeMap & theSizeMap,
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

	SetPairedFacets();

	UpdateEdges(theSizeMap);

	Try_Exception_Handle_Exit(UpdateFacets(theSizeMap));

	CreateElement();

	UpdateElement();

	Debug_Null_Pointer(theInfo_.CreatedElement());
	Get_Object(theElement) = *theInfo_.CreatedElement();

	forThose
	(
		Index,
		0,
		5
	)
	{
		Debug_Null_Pointer(theElement.Edge(Index));

		if (theElement.Edge(Index)->IsFrontFacetsEmpty())
		{
			Get_Object(Edge) = *theElement.Edge(Index);

			Try_Exception_Handle_Exit(Edge.Node0()->RemoveFromFronts(&Edge));
			Try_Exception_Handle_Exit(Edge.Node1()->RemoveFromFronts(&Edge));
		}
	}

	forThose
	(
		Index,
		0,
		3
	)
	{
		Debug_Null_Pointer(theElement.Node(Index));

		if (theElement.Node(Index)->IsFrontFacetsEmpty())
		{
			Try_Exception_Handle_Exit(RemoveFromFronts(theElement.Node(Index)));
		}
	}

	return theInfo_.CreatedElement();
}

void AutLib::MeshLib::Mesh3d_TMesh::ForcedToRemoveFromTopology
(
	Global_Handle(Mesh3d_Edge) theEdge,
	const Standard_Boolean BoundaryChecking
)
{
	Debug_Null_Pointer(theEdge);

	if (Global_DownCast(Mesh3d_BoundaryEdge, theEdge)) { return; }

	TColMesh3d_HAry1dOfElement Elements;
	theEdge->RetrieveTo(Elements);

	if (Elements.IsEmpty()) { THROW_STANDARD_EXCEPTION("Invalid Data"); }

	forThose
	(
		Index,
		0,
		MaxIndexOf(Elements)
	)
	{
		Debug_Null_Pointer(Elements[Index]);

		TColMesh3d_HAry1dOfNode RetrieveNodes, RemoveNodes;
		TColMesh3d_HAry1dOfEdge RetrieveEdges, RemoveEdges;
		TColMesh3d_HAry1dOfFacet RetrieveFacets, RemoveFacets;

		RemoveFromTopology
		(
			Elements[Index],
			RetrieveFacets,
			RetrieveEdges,
			RetrieveNodes,
			RemoveFacets,
			RemoveEdges,
			RemoveNodes,
			Standard_True
		);
	}
}

void AutLib::MeshLib::Mesh3d_TMesh::ForcedToRemoveFromTopology
(
	Global_Handle(Mesh3d_Facet) theFacet,
	const Standard_Boolean BoundaryChecking
)
{
	Debug_Null_Pointer(theFacet);

	if (Global_DownCast(Mesh3d_BoundaryFacet, theFacet)) { return; }

	TColMesh3d_HAry1dOfElement Elements(2);
	Elements[0] = theFacet->LeftElement();
	Elements[1] = theFacet->RightElement();

	forThose
	(
		Index,
		0,
		MaxIndexOf(Elements)
	)
	{
		Debug_Null_Pointer(Elements[Index]);

		TColMesh3d_HAry1dOfNode RetrieveNodes, RemoveNodes;
		TColMesh3d_HAry1dOfEdge RetrieveEdges, RemoveEdges;
		TColMesh3d_HAry1dOfFacet RetrieveFacets, RemoveFacets;

		RemoveFromTopology
		(
			Elements[Index],
			RetrieveFacets,
			RetrieveEdges,
			RetrieveNodes,
			RemoveFacets,
			RemoveEdges,
			RemoveNodes,
			Standard_True
		);
	}
}

void AutLib::MeshLib::Mesh3d_TMesh::RemoveFromTopology
(
	Global_Handle(Mesh3d_Element) theElement, 
	TColMesh3d_HAry1dOfFacet & theRetrievedFacets,
	TColMesh3d_HAry1dOfEdge & theRetrievedEdges, 
	TColMesh3d_HAry1dOfNode & theRetrievedNodes,
	TColMesh3d_HAry1dOfFacet & theRemovedFacets,
	TColMesh3d_HAry1dOfEdge & theRemovedEdges,
	TColMesh3d_HAry1dOfNode & theRemovedNodes,
	const Standard_Boolean BoundaryChecking
)
{
	Debug_Null_Pointer(theElement);
	Get_Const_Object(Element) = *theElement;

	// Retrieve nodes that not belong to the Front
	TColMesh3d_HBasicQueueOfNode QRetrievedNodes;
	forThose
	(
		Index,
		0,
		3
	)
	{
		Debug_Null_Pointer(Element.Node(Index));
		Get_Const_Object(Node) = Element.Node(Index);

		if (NOT Node->IsOnFront()) 
		{ 
			Try_Exception_Handle_Exit(Mesh3d_Mesh::InsertToFronts(Node));
			QRetrievedNodes.EnQueue(Node);
		}
	}
	QRetrievedNodes.RetrieveTo(theRetrievedNodes);

	// deAttach the Element from current Mesh and remove it
	Try_Exception_Handle_Exit(Mesh3d_TMesh::deAttachFromMesh(theElement));
	Try_Exception_Handle_Exit(Mesh3d_Mesh::RemoveFromMesh(theElement));

	TColMesh3d_HBasicQueueOfFacet QRetrievedFacets;
	TColMesh3d_HBasicQueueOfFacet QRemovedFacets;
	forThose
	(
		Index,
		0,
		3
	)
	{
		Debug_Null_Pointer(Element.Facet(Index));
		Get_Const_Object(Facet) = Element.Facet(Index);

		if (Facet->IsOrphan() AND NOT Global_DownCast(Mesh3d_BoundaryFacet, Facet))
		{
			Try_Exception_Handle_Exit(Mesh3d_TMesh::RemoveFromTopology(Facet, BoundaryChecking));
			QRemovedFacets.EnQueue(Facet);
		}
		else
		{
			Try_Exception_Handle_Exit(Mesh3d_TMesh::AttachToFront(Facet));
			Try_Exception_Handle_Exit(Mesh3d_TMesh::InsertToFronts(Facet));
			QRetrievedFacets.EnQueue(Facet);
		}
	}
	QRemovedFacets.RetrieveTo(theRemovedFacets);
	QRetrievedFacets.RetrieveTo(theRetrievedFacets);

	// The orphan edge that not belong to the boundary must be destroyed!
	// The edge that not belong to the Front must be retrieved
	TColMesh3d_HBasicQueueOfEdge QRetrievedEdges;
	TColMesh3d_HBasicQueueOfEdge QRemovedEdges;
	forThose
	(
		Index,
		0, 
		5
	)
	{
		Debug_Null_Pointer(Element.Edge(Index));
		Get_Const_Object(Edge) = Element.Edge(Index);

		if (Edge->IsOrphan() AND NOT Global_DownCast(Mesh3d_BoundaryEdge, Edge))
		{
			Try_Exception_Handle_Exit(Mesh3d_TMesh::RemoveFromTopology(Edge, BoundaryChecking));
			QRemovedEdges.EnQueue(Edge);
		}
		else
		{
			if (NOT Edge->IsOnFront())
			{
				Try_Exception_Handle_Exit(Mesh3d_TMesh::AttachToFrontNodes(Edge));
				QRetrievedEdges.EnQueue(Edge);
			}
		}
	}
	QRetrievedEdges.RetrieveTo(theRetrievedEdges);
	QRemovedEdges.RetrieveTo(theRemovedEdges);

	// Destroy the nodes that orphan and not belong to the boundary
	TColMesh3d_HBasicQueueOfNode QRemovedNodes;
	forThose
	(
		Index,
		0,
		3
	)
	{
		Debug_Null_Pointer(Element.Node(Index));
		Get_Const_Object(Node) = Element.Node(Index);

		if (NOT Node->NbElements() AND NOT Global_DownCast(Mesh3d_BoundaryNode, Node))
		{
			Try_Exception_Handle_Exit(Mesh3d_Mesh::RemoveFromFronts(Node));
			Try_Exception_Handle_Exit(Mesh3d_Mesh::RemoveFromMesh(Node));

			QRemovedNodes.EnQueue(Node);
		}
	}
	QRemovedNodes.RetrieveTo(theRemovedNodes);
}

void AutLib::MeshLib::Mesh3d_TMesh::RemoveFromTopology
(
	Global_Handle(Mesh3d_Element) theElement, 
	Standard_Boolean BoundaryChecking
)
{
	Debug_Null_Pointer(theElement);
	Get_Const_Object(Element) = *theElement;

	forThose
	(
		Index,
		0,
		3
	)
	{
		Debug_Null_Pointer(Element.Node(Index));
		Get_Const_Object(Node) = Element.Node(Index);

		if (NOT Node->IsOnFront())
		{
			Try_Exception_Handle_Exit(Mesh3d_Mesh::InsertToFronts(Node));
		}
	}

	// deAttach the Element from current Mesh and remove it
	Try_Exception_Handle_Exit(Mesh3d_TMesh::deAttachFromMesh(theElement));
	Try_Exception_Handle_Exit(Mesh3d_Mesh::RemoveFromMesh(theElement));

	forThose
	(
		Index,
		0,
		3
	)
	{
		Debug_Null_Pointer(Element.Facet(Index));
		Get_Const_Object(Facet) = Element.Facet(Index);

		if (Facet->IsOrphan() AND NOT Global_DownCast(Mesh3d_BoundaryFacet, Facet))
		{
			Try_Exception_Handle_Exit(Mesh3d_TMesh::RemoveFromTopology(Facet, BoundaryChecking));
		}
		else
		{
			Try_Exception_Handle_Exit(Mesh3d_TMesh::AttachToFront(Facet));
			Try_Exception_Handle_Exit(Mesh3d_TMesh::InsertToFronts(Facet));
		}
	}

	// The orphan edge that not belong to the boundary must be destroyed!
	// The edge that not belong to the Front must be retrieved
	forThose
	(
		Index,
		0,
		5
	)
	{
		Debug_Null_Pointer(Element.Edge(Index));
		Get_Const_Object(Edge) = Element.Edge(Index);

		if (Edge->IsOrphan() AND NOT Global_DownCast(Mesh3d_BoundaryEdge, Edge))
		{
			Try_Exception_Handle_Exit(Mesh3d_TMesh::RemoveFromTopology(Edge, BoundaryChecking));
		}
		else
		{
			if (NOT Edge->IsOnFront())
			{
				Try_Exception_Handle_Exit(Mesh3d_TMesh::AttachToFrontNodes(Edge));
			}
		}
	}

	// Destroy the nodes that orphan and not belong to the boundary
	forThose
	(
		Index,
		0,
		3
	)
	{
		Debug_Null_Pointer(Element.Node(Index));
		Get_Const_Object(Node) = Element.Node(Index);

		if (NOT Node->NbElements() AND NOT Global_DownCast(Mesh3d_BoundaryNode, Node))
		{
			Try_Exception_Handle_Exit(Mesh3d_Mesh::RemoveFromFronts(Node));
			Try_Exception_Handle_Exit(Mesh3d_Mesh::RemoveFromMesh(Node));
		}
	}
}

void AutLib::MeshLib::Mesh3d_TMesh::SetPairedEdges()
{
	TColMesh3d_HBasicQueueOfEdge QEdges;
	theInfo_.ValidNode()->RetrieveFrontsTo(QEdges);

	Get_Const_Object(CurrentFacet) = *theInfo_.Current();

	Standard_Integer Vn = theInfo_.ValidNode()->Index();

	Debug_Null_Pointer(CurrentFacet.Node0());
	Debug_Null_Pointer(CurrentFacet.Node1());
	Debug_Null_Pointer(CurrentFacet.Node2());

	Standard_Integer V0 = CurrentFacet.Node0()->Index();
	Standard_Integer V1 = CurrentFacet.Node1()->Index();
	Standard_Integer V2 = CurrentFacet.Node2()->Index();

	Global_Handle(Mesh3d_Edge) Edge;
	while (QEdges.DeQueue(Edge))
	{
		Debug_Null_Pointer(Edge);
		Get_Const_Object(theEdge) = *Edge;

		Standard_Integer E0 = theEdge.Node0()->Index();
		Standard_Integer E1 = theEdge.Node1()->Index();

		if (Geometry_Tools::IsPairedTwoLineSegment(E0, E1, V0, Vn))
		{
			theInfo_.SetPairedEdge3(Edge);
		}

		if (Geometry_Tools::IsPairedTwoLineSegment(E0, E1, V1, Vn))
		{
			theInfo_.SetPairedEdge4(Edge);
		}

		if (Geometry_Tools::IsPairedTwoLineSegment(E0, E1, V2, Vn))
		{
			theInfo_.SetPairedEdge5(Edge);
		}
	}
}

void AutLib::MeshLib::Mesh3d_TMesh::SetPairedFacets()
{
	theInfo_.SetCreatedFacet0(NULL);
	theInfo_.SetCreatedFacet1(NULL);
	theInfo_.SetCreatedFacet2(NULL);

	theInfo_.SetPairedFacet0(NULL);
	theInfo_.SetPairedFacet1(NULL);
	theInfo_.SetPairedFacet2(NULL);

	Get_Const_Object(theCurrent) = *theInfo_.Current();

	Debug_Null_Pointer(theCurrent.Edge0());
	Debug_Null_Pointer(theCurrent.Edge1());
	Debug_Null_Pointer(theCurrent.Edge2());

	TColMesh3d_HBasicQueueOfFacet QFacets0, QFacets1, QFacets2;
	theCurrent.Edge0()->RetrieveFrontsTo(QFacets0);
	theCurrent.Edge1()->RetrieveFrontsTo(QFacets1);
	theCurrent.Edge2()->RetrieveFrontsTo(QFacets2);

	Get_Const_Object(theValidNode) = *theInfo_.ValidNode();

	Global_Handle(Mesh3d_Facet) Facet;
	while (QFacets0.DeQueue(Facet))
	{
		Debug_Null_Pointer(Facet);
		Get_Const_Object(theFacet) = *Facet;

		Standard_Boolean IsPaired = Geometry_Tools::IsPairedTwoTriangle
		(
			theCurrent.Node1()->Index(),
			theCurrent.Node2()->Index(),
			theValidNode.Index(),
			theFacet.Node0()->Index(),
			theFacet.Node1()->Index(),
			theFacet.Node2()->Index()
		);

		if (IsPaired)
		{
			theInfo_.SetPairedFacet0(Facet);
			break;
		}
	}

	while (QFacets1.DeQueue(Facet))
	{
		Debug_Null_Pointer(Facet);
		Get_Const_Object(theFacet) = *Facet;

		Standard_Boolean IsPaired = Geometry_Tools::IsPairedTwoTriangle
		(
			theCurrent.Node2()->Index(),
			theCurrent.Node0()->Index(),
			theValidNode.Index(),
			theFacet.Node0()->Index(),
			theFacet.Node1()->Index(),
			theFacet.Node2()->Index()
		);

		if (IsPaired)
		{
			theInfo_.SetPairedFacet1(Facet);
			break;
		}
	}

	while (QFacets2.DeQueue(Facet))
	{
		Debug_Null_Pointer(Facet);
		Get_Const_Object(theFacet) = *Facet;

		Standard_Boolean IsPaired = Geometry_Tools::IsPairedTwoTriangle
		(
			theCurrent.Node0()->Index(),
			theCurrent.Node1()->Index(),
			theValidNode.Index(),
			theFacet.Node0()->Index(),
			theFacet.Node1()->Index(),
			theFacet.Node2()->Index()
		);

		if (IsPaired)
		{
			theInfo_.SetPairedFacet2(Facet);
			break;
		}
	}
}

void AutLib::MeshLib::Mesh3d_TMesh::UpdateEdges(const Mesh3d_SizeMap& theSizeMap)
{
	Global_Handle(Mesh3d_Node) Node = theInfo_.ValidNode();
	Get_Const_Object(Coord) = Node->Coord();

	Get_Const_Object(theCurrent) = *theInfo_.Current();

	Debug_If_Condition(theInfo_.IsPairedEdge3() AND theInfo_.IsCreatedEdge3());
	Debug_If_Condition(theInfo_.IsPairedEdge4() AND theInfo_.IsCreatedEdge4());
	Debug_If_Condition(theInfo_.IsPairedEdge5() AND theInfo_.IsCreatedEdge5());

	if (theInfo_.IsPairedEdge3())
	{
		theInfo_.SetCreatedEdge3(NULL);
	}
	else
	{
		NbEdges()++;

		Standard_Real Length = theSizeMap.CalcDistance(theCurrent.Node0()->Coord(), Coord);

		Global_Handle(Mesh3d_Edge) newEdge = new Mesh3d_Edge(NbEdges(), Length, theCurrent.Node0(), theInfo_.ValidNode());

		Debug_Null_Pointer(newEdge);

		UpdateMaxLength(Length, *newEdge);

		AttachToMeshNodes(newEdge);
		AttachToFrontNodes(newEdge);

		InsertToMesh(newEdge);

		theInfo_.SetCreatedEdge3(newEdge);
	}

	if (theInfo_.IsPairedEdge4())
	{
		theInfo_.SetCreatedEdge4(NULL);
	}
	else
	{
		NbEdges()++;

		Standard_Real Length = theSizeMap.CalcDistance(theCurrent.Node1()->Coord(), Coord);

		Global_Handle(Mesh3d_Edge) newEdge = new Mesh3d_Edge(NbEdges(), Length, theCurrent.Node1(), theInfo_.ValidNode());

		Debug_Null_Pointer(newEdge);

		UpdateMaxLength(Length, *newEdge);

		AttachToMeshNodes(newEdge);
		AttachToFrontNodes(newEdge);

		InsertToMesh(newEdge);

		theInfo_.SetCreatedEdge4(newEdge);
	}

	if (theInfo_.IsPairedEdge5())
	{
		theInfo_.SetCreatedEdge5(NULL);
	}
	else
	{
		NbEdges()++;

		Standard_Real Length = theSizeMap.CalcDistance(theCurrent.Node2()->Coord(), Coord);

		Global_Handle(Mesh3d_Edge) newEdge = new Mesh3d_Edge(NbEdges(), Length, theCurrent.Node2(), theInfo_.ValidNode());

		Debug_Null_Pointer(newEdge);

		UpdateMaxLength(Length, *newEdge);

		AttachToMeshNodes(newEdge);
		AttachToFrontNodes(newEdge);

		InsertToMesh(newEdge);

		theInfo_.SetCreatedEdge5(newEdge);
	}
}

void AutLib::MeshLib::Mesh3d_TMesh::UpdateFacets(const Mesh3d_SizeMap& theSizeMap)
{
	Get_Const_Object(theCurrent) = *theInfo_.Current();

	Global_Handle(Mesh3d_Edge) E0 = theCurrent.Edge0();
	Global_Handle(Mesh3d_Edge) E1 = theCurrent.Edge1();
	Global_Handle(Mesh3d_Edge) E2 = theCurrent.Edge2();

	Global_Handle(Mesh3d_Edge) E3;
	Global_Handle(Mesh3d_Edge) E4;
	Global_Handle(Mesh3d_Edge) E5;

	if (theInfo_.CreatedEdge3()) E3 = theInfo_.CreatedEdge3();
	else E3 = theInfo_.PairedEdge3();

	if (theInfo_.CreatedEdge4()) E4 = theInfo_.CreatedEdge4();
	else E4 = theInfo_.PairedEdge4();

	if (theInfo_.CreatedEdge5()) E5 = theInfo_.CreatedEdge5();
	else E5 = theInfo_.PairedEdge5();

	Debug_Null_Pointer(E0);
	Debug_Null_Pointer(E1);
	Debug_Null_Pointer(E2);
	Debug_Null_Pointer(E3);
	Debug_Null_Pointer(E4);
	Debug_Null_Pointer(E5);

	Global_Handle(Mesh3d_Facet) Facet = theInfo_.PairedFacet0();

	if (Facet)
	{
		theInfo_.SetCreatedFacet0(NULL);

		// remove the old coicident face from the GF
		Try_Exception_Handle_Exit(deAttachFromFront(Facet));
		Try_Exception_Handle_Exit(RemoveFromFronts(Facet));

		// remove cavity face
		if (Facet->IsCavity())
		{
			Facet->SetAsNotCavity();
		}
	}
	else
	{
		NbFacets()++;

		Global_Handle(Mesh3d_Facet) newFacet = new Mesh3d_Facet
		(
			NbFacets(),
			theCurrent.Node1(),
			theCurrent.Node2(),
			theInfo_.ValidNode(),
			E5,
			E4,
			E0
		);

		theInfo_.SetCreatedFacet0(newFacet);

		// insert the new Face into the FACES TREE
		AttachToFront(newFacet);
		AttachToMesh(newFacet);

		InsertToFronts(newFacet);
		InsertToMesh(newFacet);

		CalcGeometryOf(*newFacet, theSizeMap);
	}

	Facet = theInfo_.PairedFacet1();

	if (Facet)
	{
		theInfo_.SetCreatedFacet1(NULL);

		// remove the old coicident face from the GF
		Try_Exception_Handle_Exit(deAttachFromFront(Facet));
		Try_Exception_Handle_Exit(RemoveFromFronts(Facet));

		// remove cavity face
		if (Facet->IsCavity())
		{
			Facet->SetAsNotCavity();
		}
	}
	else
	{
		NbFacets()++;

		Global_Handle(Mesh3d_Facet) newFacet = new Mesh3d_Facet
		(
			NbFacets(),
			theCurrent.Node2(),
			theCurrent.Node0(),
			theInfo_.ValidNode(),
			E3,
			E5,
			E1
		);

		theInfo_.SetCreatedFacet1(newFacet);

		// insert the new Face into the FACES TREE
		AttachToFront(newFacet);
		AttachToMesh(newFacet);

		InsertToFronts(newFacet);
		InsertToMesh(newFacet);

		CalcGeometryOf(*newFacet, theSizeMap);
	}

	Facet = theInfo_.PairedFacet2();

	if (Facet)
	{
		theInfo_.SetCreatedFacet2(NULL);

		// remove the old coicident face from the GF
		Try_Exception_Handle_Exit(deAttachFromFront(Facet));
		Try_Exception_Handle_Exit(RemoveFromFronts(Facet));

		// remove cavity face
		if (Facet->IsCavity())
		{
			Facet->SetAsNotCavity();
		}
	}
	else
	{
		NbFacets()++;

		Global_Handle(Mesh3d_Facet) newFacet = new Mesh3d_Facet
		(
			NbFacets(),
			theCurrent.Node0(),
			theCurrent.Node1(),
			theInfo_.ValidNode(),
			E4,
			E3,
			E2
		);

		theInfo_.SetCreatedFacet2(newFacet);

		// insert the new Face into the FACES TREE
		AttachToFront(newFacet);
		AttachToMesh(newFacet);

		InsertToFronts(newFacet);
		InsertToMesh(newFacet);

		CalcGeometryOf(*newFacet, theSizeMap);
	}
}

void AutLib::MeshLib::Mesh3d_TMesh::CreateElement()
{
	NbElements()++;
	Global_Handle(Mesh3d_Element) theElement = new Mesh3d_Element(NbElements());

	Debug_Null_Pointer(theElement);
	Get_Object(Element) = *theElement;

	Debug_Null_Pointer(theInfo_.Current());
	Get_Const_Object(Current) = *theInfo_.Current();

	Element.SetNode(0, Current.Node0());
	Element.SetNode(1, Current.Node1());
	Element.SetNode(2, Current.Node2());
	Element.SetNode(3, theInfo_.ValidNode());

	Element.SetEdge(0, Current.Edge0());
	Element.SetEdge(1, Current.Edge1());
	Element.SetEdge(2, Current.Edge2());

	if (theInfo_.IsCreatedEdge3()) { Element.SetEdge(3, theInfo_.CreatedEdge3()); }
	else { Element.SetEdge(3, theInfo_.PairedEdge3()); }

	if (theInfo_.IsCreatedEdge4()) { Element.SetEdge(4, theInfo_.CreatedEdge4()); }
	else { Element.SetEdge(4, theInfo_.PairedEdge4()); }

	if (theInfo_.IsCreatedEdge5()) { Element.SetEdge(5, theInfo_.CreatedEdge5()); }
	else { Element.SetEdge(5, theInfo_.PairedEdge5()); }

	if (theInfo_.IsCreatedFacet0()) { Element.SetFacet(0, theInfo_.CreatedFacet0()); }
	else { Element.SetFacet(0, theInfo_.PairedFacet0()); }

	if (theInfo_.IsCreatedFacet1()) { Element.SetFacet(1, theInfo_.CreatedFacet1()); }
	else { Element.SetFacet(1, theInfo_.PairedFacet1()); }

	if (theInfo_.IsCreatedFacet2()) { Element.SetFacet(2, theInfo_.CreatedFacet2()); }
	else { Element.SetFacet(2, theInfo_.PairedFacet2()); }

	Element.SetFacet(3, theInfo_.Current());

	theInfo_.SetCreatedElement(theElement);
}

void AutLib::MeshLib::Mesh3d_TMesh::UpdateElement()
{
	Global_Handle(Mesh3d_Element) theElement = theInfo_.CreatedElement();
	Debug_Null_Pointer(theElement);

	AttachToMeshNodes(theElement);
	AttachToMeshEdges(theElement);

	/* Attach the element to the facets */

	Get_Object(theCurrent) = *theInfo_.Current();

	// update right/ left side element pointer of the faces
	// update adjacent elements
	theCurrent.SetLeftElement(theElement);
	theElement->SetNeighbor(3, theCurrent.RightElement());

	if (theCurrent.RightElement())
	{
		theCurrent.RightElement()->SetNeighbor(theCurrent.RightElement()->OppositeVertexIndex(&theCurrent), theElement);
	}

	if (theInfo_.IsCreatedFacet0())
	{
		theInfo_.CreatedFacet0()->SetRightElement(theElement);
		theElement->SetNeighbor(0, NULL);
	}
	else
	{
		Global_Handle(Mesh3d_Facet) Facet = theInfo_.PairedFacet0();
		Debug_Null_Pointer(Facet);

		Global_Handle(Mesh3d_Element) Neighbor0 = Facet->RightElement();
		theElement->SetNeighbor(0, Neighbor0);

		if (Facet->LeftElement()) { THROW_STANDARD_EXCEPTION("Contradiction data"); }

		Facet->SetLeftElement(theElement);

		if (Neighbor0) { Neighbor0->SetNeighbor(Neighbor0->OppositeVertexIndex(Facet), theElement); }
	}

	if (theInfo_.IsCreatedFacet1())
	{
		theInfo_.CreatedFacet1()->SetRightElement(theElement);
		theElement->SetNeighbor(1, NULL);
	}
	else
	{
		Global_Handle(Mesh3d_Facet) Facet = theInfo_.PairedFacet1();
		Debug_Null_Pointer(Facet);

		Global_Handle(Mesh3d_Element) Neighbor1 = Facet->RightElement();
		theElement->SetNeighbor(1, Neighbor1);

		if (Facet->LeftElement()) { THROW_STANDARD_EXCEPTION("Contradiction data"); }

		Facet->SetLeftElement(theElement);

		if (Neighbor1) { Neighbor1->SetNeighbor(Neighbor1->OppositeVertexIndex(Facet), theElement); }
	}

	if (theInfo_.IsCreatedFacet2())
	{
		theInfo_.CreatedFacet2()->SetRightElement(theElement);
		theElement->SetNeighbor(2, NULL);
	}
	else
	{
		Global_Handle(Mesh3d_Facet) Facet = theInfo_.PairedFacet2();
		Debug_Null_Pointer(Facet);

		Global_Handle(Mesh3d_Element) Neighbor2 = Facet->RightElement();
		theElement->SetNeighbor(2, Neighbor2);

		if (Facet->LeftElement()) { THROW_STANDARD_EXCEPTION("Contradiction data"); }

		Facet->SetLeftElement(theElement);

		if (Neighbor2) { Neighbor2->SetNeighbor(Neighbor2->OppositeVertexIndex(Facet), theElement); }
	}

	// updating the ELMENTS TREE
	InsertToMesh(theElement);
}

void AutLib::MeshLib::Mesh3d_TMesh::CalcGeometryOf(Mesh3d_Facet & theFacet, const Mesh3d_SizeMap& theSizeMap) const
{
	Debug_Null_Pointer(theFacet.Node0());
	Debug_Null_Pointer(theFacet.Node1());
	Debug_Null_Pointer(theFacet.Node2());

	Get_Const_Object(P0) = theFacet.Node0()->Coord();
	Get_Const_Object(P1) = theFacet.Node1()->Coord();
	Get_Const_Object(P2) = theFacet.Node2()->Coord();

	theFacet.SetArea(theSizeMap.CalcArea(P0, P1, P2));
	theFacet.SetCentre((P0 + P1 + P2) / 3.0);

	Debug_Null_Pointer(theFacet.Edge0());
	Debug_Null_Pointer(theFacet.Edge1());
	Debug_Null_Pointer(theFacet.Edge2());

	theFacet.SetLength(MAX(theFacet.Edge0()->Length(), MAX(theFacet.Edge1()->Length(), theFacet.Edge2()->Length())));
}