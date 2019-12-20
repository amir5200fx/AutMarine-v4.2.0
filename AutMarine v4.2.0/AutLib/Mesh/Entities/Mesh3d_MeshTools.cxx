#include <Mesh3d_MeshTools.hxx>

#include <Mesh3d_Node.hxx>
#include <Mesh3d_Edge.hxx>
#include <Mesh3d_Facet.hxx>
#include <Mesh3d_Element.hxx>
#include <Mesh3d_ElementTools.hxx>
#include <Mesh3d_Mesh.hxx>
#include <Mesh3d_BoundaryFacet.hxx>
#include <TColMesh3d_HAvlTreeOfElement.hxx>

Standard_Boolean AutLib::MeshLib::Mesh3d_MeshTools::CheckToInsertToMesh(Global_Handle(Mesh3d_Edge) theEdge)
{
	Debug_Null_Pointer(theEdge);

	Get_Const_Object(Edge) = *theEdge;

	if (NOT Edge.Node0()->IsContainAtFront(theEdge))
	{
		cout << " Failed to Insert To Mesh: The Edge Not Attached to the nodes of the front" << endl;
		return Standard_True;
	}

	if (NOT Edge.Node1()->IsContainAtFront(theEdge))
	{
		cout << " Failed to Insert To Mesh: The Edge Not Attached to the nodes of the front" << endl;
		return Standard_True;
	}

	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_MeshTools::CheckToInsertToMesh(Global_Handle(Mesh3d_Facet) theFacet)
{
	Debug_Null_Pointer(theFacet);

	Get_Const_Object(Facet) = *theFacet;

	if (NOT Facet.Node0()->IsContainAtMesh(theFacet))
	{
		cout << " Failed to Insert To Mesh: The Edge Not Attached to the nodes of the mesh" << endl;
		return Standard_True;
	}

	if (NOT Facet.Node1()->IsContainAtMesh(theFacet))
	{
		cout << " Failed to Insert To Mesh: The Edge Not Attached to the nodes of the mesh" << endl;
		return Standard_True;
	}

	if (NOT Facet.Node2()->IsContainAtMesh(theFacet))
	{
		cout << " Failed to Insert To Mesh: The Edge Not Attached to the nodes of the mesh" << endl;
		return Standard_True;
	}

	if (NOT Facet.Edge0()->IsContainAtMesh(theFacet))
	{
		cout << " Failed to Insert To Mesh: The Edge Not Attached to the edges of the mesh" << endl;
		return Standard_True;
	}

	if (NOT Facet.Edge1()->IsContainAtMesh(theFacet))
	{
		cout << " Failed to Insert To Mesh: The Edge Not Attached to the edges of the mesh" << endl;
		return Standard_True;
	}

	if (NOT Facet.Edge2()->IsContainAtMesh(theFacet))
	{
		cout << " Failed to Insert To Mesh: The Edge Not Attached to the edges of the mesh" << endl;
		return Standard_True;
	}

	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_MeshTools::CheckToInsertToMesh(Global_Handle(Mesh3d_Element) theElement)
{
	Debug_Null_Pointer(theElement);

	Get_Const_Object(Element) = *theElement;

	forThose(Index, 0, 3)
	{
		Debug_Null_Pointer(Element.Node(Index));
		if (NOT Element.Node(Index)->IsContainAtMesh(theElement))
		{
			cout << " Failed to Insert To Mesh: The Edge Not Attached to the nodes of the mesh" << endl;
			return Standard_True;
		}
	}

	forThose(Index, 0, 5)
	{
		Debug_Null_Pointer(Element.Edge(Index));
		if (NOT Element.Edge(Index)->IsContainAtMesh(theElement))
		{
			cout << " Failed to Insert To Mesh: The Edge Not Attached to the edges of the mesh" << endl;
			return Standard_True;
		}
	}

	forThose(Index, 0, 3)
	{
		Debug_Null_Pointer(Element.Facet(Index));
		if (NOT Element.Facet(Index)->IsContain(theElement))
		{
			cout << " Failed to Insert To Mesh: The Edge Not Attached to the facets of the mesh" << endl;
			return Standard_True;
		}
	}

	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_MeshTools::CheckToInsertToFront(Global_Handle(Mesh3d_Edge) theEdge)
{
	Debug_Null_Pointer(theEdge);

	Get_Const_Object(Edge) = *theEdge;

	if (NOT Edge.Node0()->IsContainAtFront(theEdge))
	{
		cout << " Failed to Insert To Mesh: The Edge Not Attached to the nodes of the front" << endl;
		return Standard_True;
	}

	if (NOT Edge.Node1()->IsContainAtFront(theEdge))
	{
		cout << " Failed to Insert To Mesh: The Edge Not Attached to the nodes of the front" << endl;
		return Standard_True;
	}

	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_MeshTools::CheckToInsertToFront(Global_Handle(Mesh3d_Facet) theFacet)
{
	Debug_Null_Pointer(theFacet);

	Get_Const_Object(Facet) = *theFacet;

	if (NOT Facet.Node0()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Insert To Mesh: The Facet Not Attached to the nodes of the front" << endl;
		return Standard_True;
	}

	if (NOT Facet.Node1()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Insert To Mesh: The Facet Not Attached to the nodes of the front" << endl;
		return Standard_True;
	}

	if (NOT Facet.Node2()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Insert To Mesh: The Facet Not Attached to the nodes of the front" << endl;
		return Standard_True;
	}

	if (NOT Facet.Edge0()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Insert To Mesh: The Facet Not Attached to the edges of the front" << endl;
		return Standard_True;
	}

	if (NOT Facet.Edge1()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Insert To Mesh: The Facet Not Attached to the edges of the front" << endl;
		return Standard_True;
	}

	if (NOT Facet.Edge2()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Insert To Mesh: The Facet Not Attached to the edges of the front" << endl;
		return Standard_True;
	}

	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_MeshTools::CheckToRemoveFromMesh(Global_Handle(Mesh3d_Node) theNode)
{
	Debug_Null_Pointer(theNode);

	Get_Const_Object(Node) = *theNode;

	if (NOT Node.IsEdgesEmpty())
	{
		cout << " Failed to Remove from Mesh: The Node has some edges around!" << endl;
		return Standard_True;
	}
	if (NOT Node.IsFacetsEmpty())
	{
		cout << " Failed to Remove from Mesh: The Node has some facets around!" << endl;
		return Standard_True;
	}
	if (NOT Node.IsElementsEmpty())
	{
		cout << " Failed to Remove from Mesh: The Node has some elements around!" << endl;
		return Standard_True;
	}

	if (NOT Node.IsFrontEdgesEmpty())
	{
		cout << " Failed to Remove from Mesh: The Node has some front edges around!" << endl;
		return Standard_True;
	}
	if (NOT Node.IsFrontFacetsEmpty())
	{
		cout << " Failed to Remove from Mesh: The Node has some front facets around!" << endl;
		return Standard_True;
	}

	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_MeshTools::CheckToRemoveFromMesh(Global_Handle(Mesh3d_Edge) theEdge)
{
	Debug_Null_Pointer(theEdge);

	Get_Const_Object(Edge) = *theEdge;

	if (NOT Edge.IsFacetsEmpty())
	{
		cout << " Failed to Remove from Mesh: The Edge has some facets around!" << endl;
		return Standard_True;
	}

	if (NOT Edge.IsElementsEmpty())
	{
		cout << " Failed to Remove from Mesh: The Edge has some elements around!" << endl;
		return Standard_True;
	}

	if (Edge.Node0()->IsContainAtMesh(theEdge))
	{
		cout << " Failed to Remove from Mesh: The Edge Not deAttached from the nodes of the mesh" << endl;
		return Standard_True;
	}

	if (Edge.Node1()->IsContainAtMesh(theEdge))
	{
		cout << " Failed to Remove from Mesh: The Edge Not deAttached from the nodes of the mesh" << endl;
		return Standard_True;
	}

	if (Edge.Node0()->IsContainAtFront(theEdge))
	{
		cout << " Failed to Remove from Mesh: The Edge Not deAttached from the nodes of the front" << endl;
		return Standard_True;
	}

	if (Edge.Node1()->IsContainAtFront(theEdge))
	{
		cout << " Failed to Remove from Mesh: The Edge Not deAttached from the nodes of the front" << endl;
		return Standard_True;
	}

	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_MeshTools::CheckToRemoveFromMesh(Global_Handle(Mesh3d_Facet) theFacet)
{
	Debug_Null_Pointer(theFacet);

	Get_Const_Object(Facet) = *theFacet;

	if (NOT Facet.IsOrphan())
	{
		cout << " Failed to Remove from Mesh: The Facet has some elements around!" << endl;
		return Standard_True;
	}

	if (Facet.Node0()->IsContainAtMesh(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the nodes of the mesh" << endl;
		return Standard_True;
	}

	if (Facet.Node1()->IsContainAtMesh(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the nodes of the mesh" << endl;
		return Standard_True;
	}

	if (Facet.Node2()->IsContainAtMesh(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the nodes of the mesh" << endl;
		return Standard_True;
	}

	if (Facet.Node0()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the nodes of the mesh" << endl;
		return Standard_True;
	}

	if (Facet.Node1()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the nodes of the mesh" << endl;
		return Standard_True;
	}

	if (Facet.Node2()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the nodes of the mesh" << endl;
		return Standard_True;
	}

	if (Facet.Edge0()->IsContainAtMesh(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the edges of the mesh" << endl;
		return Standard_True;
	}

	if (Facet.Edge1()->IsContainAtMesh(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the edges of the mesh" << endl;
		return Standard_True;
	}

	if (Facet.Edge2()->IsContainAtMesh(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the edges of the mesh" << endl;
		return Standard_True;
	}

	if (Facet.Edge0()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the edges of the mesh" << endl;
		return Standard_True;
	}

	if (Facet.Edge1()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the edges of the mesh" << endl;
		return Standard_True;
	}

	if (Facet.Edge2()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the edges of the mesh" << endl;
		return Standard_True;
	}

	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_MeshTools::CheckToRemoveFromMesh(Global_Handle(Mesh3d_Element) theElement)
{
	Debug_Null_Pointer(theElement);

	Get_Const_Object(Element) = *theElement;

	forThose(Index, 0, 3)
	{
		Debug_Null_Pointer(Element.Node(Index));
		if (Element.Node(Index)->IsContainAtMesh(theElement))
		{
			cout << " Failed to Remove from Mesh: The Element Not deAttached from the nodes of the mesh" << endl;
			return Standard_True;
		}
	}

	forThose(Index, 0, 5)
	{
		Debug_Null_Pointer(Element.Edge(Index));
		if (Element.Edge(Index)->IsContainAtMesh(theElement))
		{
			cout << " Failed to Remove from Mesh: The Element Not deAttached from the edges of the mesh" << endl;
			return Standard_True;
		}
	}

	forThose(Index, 0, 3)
	{
		Debug_Null_Pointer(Element.Facet(Index));
		if (Element.Facet(Index)->IsContain(theElement))
		{
			cout << " Failed to Remove from Mesh: The Element Not deAttached from the facets of the mesh" << endl;
			return Standard_True;
		}
	}

	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_MeshTools::CheckToRemoveFromFront(Global_Handle(Mesh3d_Node) theNode)
{
	Debug_Null_Pointer(theNode);

	Get_Const_Object(Node) = *theNode;

	if (NOT Node.IsFrontEdgesEmpty())
	{
		cout << " Failed to Remove from Mesh: The Node has some front edges around!" << endl;
		return Standard_True;
	}
	if (NOT Node.IsFrontFacetsEmpty())
	{
		cout << " Failed to Remove from Mesh: The Node has some front facets around!" << endl;
		return Standard_True;
	}

	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_MeshTools::CheckToRemoveFromFront(Global_Handle(Mesh3d_Edge) theEdge)
{
	Debug_Null_Pointer(theEdge);

	Get_Const_Object(Edge) = *theEdge;

	if (Edge.Node0()->IsContainAtFront(theEdge))
	{
		cout << " Failed to Remove from Mesh: The Edge Not deAttached from the nodes of the front" << endl;
		return Standard_True;
	}

	if (Edge.Node1()->IsContainAtFront(theEdge))
	{
		cout << " Failed to Remove from Mesh: The Edge Not deAttached from the nodes of the front" << endl;
		return Standard_True;
	}

	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_MeshTools::CheckToRemoveFromFront(Global_Handle(Mesh3d_Facet) theFacet)
{
	Debug_Null_Pointer(theFacet);

	Get_Const_Object(Facet) = *theFacet;

	if (Facet.Node0()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the nodes of the mesh" << endl;
		return Standard_True;
	}

	if (Facet.Node1()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the nodes of the mesh" << endl;
		return Standard_True;
	}

	if (Facet.Node2()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the nodes of the mesh" << endl;
		return Standard_True;
	}

	if (Facet.Edge0()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the edges of the mesh" << endl;
		return Standard_True;
	}

	if (Facet.Edge1()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the edges of the mesh" << endl;
		return Standard_True;
	}

	if (Facet.Edge2()->IsContainAtFront(theFacet))
	{
		cout << " Failed to Remove from Mesh: The Facet Not deAttached from the edges of the mesh" << endl;
		return Standard_True;
	}

	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_MeshTools::DeepCheckToConfirmFrontEntity(Global_Handle(Mesh3d_Facet) theFacetPtr)
{
	Debug_Null_Pointer(theFacetPtr);

	Get_Const_Object(Facet) = *theFacetPtr;

	if (Facet.LeftElement()) { return Standard_False; }

	if (NOT Global_DownCast(Mesh3d_BoundaryFacet, theFacetPtr))
	{
		if (NOT Facet.RightElement()) { return Standard_False; }
	}

	/*if (NOT Facet.IsOnBoundary())
	{
		if (NOT Facet.RightElement()) { return Standard_False; }
	}*/

	Debug_Null_Pointer(Facet.Node0());
	Debug_Null_Pointer(Facet.Node1());
	Debug_Null_Pointer(Facet.Node2());

	if (NOT Facet.Node0()->IsContainAtFront(theFacetPtr)) { return Standard_False; }
	if (NOT Facet.Node1()->IsContainAtFront(theFacetPtr)) { return Standard_False; }
	if (NOT Facet.Node2()->IsContainAtFront(theFacetPtr)) { return Standard_False; }

	Debug_Null_Pointer(Facet.Edge0());
	Debug_Null_Pointer(Facet.Edge1());
	Debug_Null_Pointer(Facet.Edge2());

	if (NOT Facet.Edge0()->IsContainAtFront(theFacetPtr)) { return Standard_False; }
	if (NOT Facet.Edge1()->IsContainAtFront(theFacetPtr)) { return Standard_False; }
	if (NOT Facet.Edge2()->IsContainAtFront(theFacetPtr)) { return Standard_False; }

	return Standard_True;
}

void AutLib::MeshLib::Mesh3d_MeshTools::IdentifyElementsAdjustedToFrontFacets
(
	const TColMesh3d_HAry1dOfFacet & theFacets,
	TColMesh3d_HAry1dOfElement & theElements
)
{
	TColMesh3d_HAvlTreeOfElement Compact;
	Set_Numbering(Compact, Mesh3d_ElementTools::IsLess);

	forThose
	(
		Index, 
		0,
		MaxIndexOf(theFacets)
	)
	{
		Debug_Null_Pointer(theFacets[Index]);

		Debug_If_Condition(Mesh3d_MeshTools::DeepCheckToConfirmFrontEntity(theFacets[Index]));

		Debug_Null_Pointer(theFacets[Index]->RightElement());

		Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(theFacets[Index]->RightElement()));
	}
	Compact.RetrieveTo(theElements);
}