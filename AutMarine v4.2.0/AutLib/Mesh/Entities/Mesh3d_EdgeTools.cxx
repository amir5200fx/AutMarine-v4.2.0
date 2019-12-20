#include <Mesh3d_EdgeTools.hxx>

#include <Geometry_Tools.hxx>
#include <Mesh3d_Edge.hxx>
#include <Mesh3d_Facet.hxx>
#include <Mesh3d_Element.hxx>
#include <Mesh3d_NodeTools.hxx>
#include <Mesh3d_ElementTools.hxx>
#include <TColMesh3d_HBasicQueueOfElement.hxx>
#include <TColMesh3d_HBasicQueueOfNode.hxx>
#include <TColMesh3d_HAvlTreeOfNode.hxx>
#include <TColMesh3d_HAvlTreeOfElement.hxx>

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

M_AUT TColEntity_Ary1dOfEdgeIndex AutLib::MeshLib::Mesh3d_EdgeTools::StaticOf(const TColMesh3d_HAry1dOfEdge & Edges)
{
	TColEntity_Ary1dOfEdgeIndex StaticEdges(Edges.Size());

	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		Get_Const_Object(Edge) = *Edges[Index];

		StaticEdges[Index].SetV12(Edge.Node(0)->Index(), Edge.Node(1)->Index());
	}

	MOVE(StaticEdges);
}

M_AUT TColMesh3d_HAry1dOfNode AutLib::MeshLib::Mesh3d_EdgeTools::RetrieveNodesFrom(const TColMesh3d_HAry1dOfEdge & Edges)
{
	TColMesh3d_HAvlTreeOfNode TNodes;

	Set_Numbering(TNodes, Mesh3d_NodeTools::IsLess);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		Get_Const_Object(Edge) = *Edges[Index];

		Debug_Null_Pointer(Edge.Node(0));
		Debug_Null_Pointer(Edge.Node(1));

		TNodes.InsertIgnoreDup(Edge.Node(0));
		TNodes.InsertIgnoreDup(Edge.Node(1));
	}

	TColMesh3d_HAry1dOfNode Nodes;
	TNodes.RetrieveTo(Nodes);

	MOVE(Nodes);
}

namespace AutLib
{
	namespace MeshLib
	{

		static inline void PairSegments(Global_Handle(Mesh3d_Node) &N1, Global_Handle(Mesh3d_Node) &N2, Global_Handle(Mesh3d_Node) &V1, Global_Handle(Mesh3d_Node) &V2)
		{
			if (N2 EQUAL V1) return;
			if (N1 EQUAL V1)
			{
				SWAP(N1, N2);
				return;
			}
			if (N2 EQUAL V2)
			{
				SWAP(V1, V2);
				return;
			}
			if (N1 EQUAL V2)
			{
				SWAP(V1, V2);
				SWAP(N1, N2);
				return;
			}
			THROW_STANDARD_EXCEPTION("Invalid Data");
		}
	}
}

TColMesh3d_HAry1dOfNode AutLib::MeshLib::Mesh3d_EdgeTools::RetrieveStarNodesAround
(
	const Mesh3d_Edge & theEdge,
	TColMesh3d_HAry1dOfEdge& theEdges
)
{
	TColMesh3d_HAry1dOfFacet Facets;
	theEdge.RetrieveTo(Facets);

	Global_Handle(Mesh3d_Facet) StartFacet(0);
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Facets)
	)
	{
		Debug_Null_Pointer(Facets[Index]);

		if (NOT Facets[Index]->RightElement())
		{
			StartFacet = Facets[Index];
			break;
		}

		if (NOT Facets[Index]->LeftElement())
		{
			StartFacet = Facets[Index];
			break;
		}
	}

	if (NOT StartFacet) { StartFacet = Facets[0]; }

	TColMesh3d_HAry1dOfElement Elements;
	theEdge.RetrieveTo(Elements);

	TColMesh3d_HAvlTreeOfElement Register;
	Set_Numbering(Register, Mesh3d_ElementTools::IsLess);

	Try_Exception_Handle_Exit(Register.Insert(Elements));

	Global_Handle(Mesh3d_Element) StartElement(0);

	if (StartFacet->LeftElement()) 
	{ 
		StartElement = StartFacet->LeftElement();
	}
	else 
	{ 
		StartElement = StartFacet->RightElement();
	}

	Debug_Null_Pointer(StartElement);

	Try_Exception_Handle_Exit(Register.Remove(StartElement));

	TColMesh3d_HBasicQueueOfElement QElements;
	QElements.EnQueue(StartElement);
	// March on elements
	while (NOT Register.IsEmpty())
	{
		Global_Handle(Mesh3d_Element) Next(0);

		forThose(Index, 0, 3)
		{
			Global_Handle(Mesh3d_Element) Neighbor = StartElement->Neighbor(Index);
			if (NOT Neighbor) continue;

			if (Register.IsContains(Neighbor))
			{
				Next = Neighbor;
				break;
			}
		}

		QElements.EnQueue(Next);

		Try_Exception_Handle_Exit(Register.Remove(Next));

		StartElement = Next;
	}

	QElements.RetrieveTo(Elements);

	Global_Handle(Mesh3d_Node) Node0 = theEdge.Node0();
	Global_Handle(Mesh3d_Node) Node1 = theEdge.Node1();

	Debug_Null_Pointer(Node0);
	Debug_Null_Pointer(Node1);

	TColMesh3d_HBasicQueueOfNode QNodes;
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Elements)
	)
	{
		Debug_Null_Pointer(Elements[Index]);
		forThose
		(
			J,
			0,
			3
		)
		{
			Debug_Null_Pointer(Elements[Index]->Node(J));
			Global_Handle(Mesh3d_Node) Node = Elements[Index]->Node(J);

			if (Node NOT_EQUAL Node0 AND Node NOT_EQUAL Node1) { QNodes.EnQueue(Node); }
		}
	}

	TColMesh3d_HAry1dOfNode Nodes;
	QNodes.RetrieveTo(Nodes);

	Standard_Integer vl = Node0->Index();
	Standard_Integer vr = Node1->Index();

	TColMesh3d_HBasicQueueOfEdge QEdges;
	forThose
	(
		Index, 
		0, 
		MaxIndexOf(Elements)
	)
	{
		Get_Const_Object(Element) = *Elements[Index];
		forThose
		(
			J,
			0,
			5
		)
		{
			Debug_Null_Pointer(Element.Edge(J));
			Get_Const_Object(Edge) = *Element.Edge(J);

			if (NOT Geometry_Tools::IsOneCommonPointTwoLineSegment(Edge.Node0()->Index(), Edge.Node1()->Index(), vl, vr))
			{
				QEdges.EnQueue(Element.Edge(J));
				break; // since just one edge has these conditions
			}
		}
	}
	QEdges.RetrieveTo(theEdges);

	forThose
	(
		Index, 
		1, 
		MaxIndexOf(Elements)
	)
	{
		Standard_Integer K0 = 2 * Index - 2;
		Standard_Integer K1 = 2 * Index - 1;
		Standard_Integer K2 = 2 * Index;
		Standard_Integer K3 = 2 * Index + 1;

		PairSegments(Nodes[K0], Nodes[K1], Nodes[K2], Nodes[K3]);
	}

	TColMesh3d_HAry1dOfNode CompactNodes;
	if (Distance(Nodes.First()->Coord(), Nodes.Last()->Coord()) EQUAL 0)
	{
		CompactNodes.Resize(Nodes.Size() / 2);
		forThose(Index, 0, Nodes.Size() / 2 - 1)
		{
			CompactNodes[Index] = Nodes[2 * Index];
		}	
	}
	else
	{
		CompactNodes.Resize(Nodes.Size() / 2 + 1);
		forThose(Index, 0, Nodes.Size() / 2 - 1)
		{
			CompactNodes[Index] = Nodes[2 * Index];
		}
		CompactNodes.Last() = Nodes.Last();
	}

	MOVE(CompactNodes);
}

Standard_Real AutLib::MeshLib::Mesh3d_EdgeTools::AngleOf(const Mesh3d_Edge & theEdge)
{
	if (NOT theEdge.IsOnFront()) { THROW_STANDARD_EXCEPTION("The edge is not belong to the front"); }

	TColMesh3d_HAry1dOfFacet Facets = theEdge.RetrieveFrontFacets();

	if (Facets.Size() NOT_EQUAL 2) { THROW_STANDARD_EXCEPTION("Not standard type"); }

	Debug_Null_Pointer(Facets[0]);
	Debug_Null_Pointer(Facets[1]);

	Get_Const_Object(Facet) = *Facets[0];

	Standard_Integer Apex;
	Try_Exception_Handle_Exit(Apex = Facet.OppositeNodeIndex(theEdge));

	Standard_Integer Id1 = (Apex + 1) % 3;
	Standard_Integer Id2 = (Id1 + 1) % 3;

	Global_Handle(Mesh3d_Node) V1 = Facet.Node(Id1);
	Global_Handle(Mesh3d_Node) V2 = Facet.Node(Id2);

	Geom_Pnt3d Normal0 = Facets[0]->Normal();
	Geom_Pnt3d Normal1 = Facets[1]->Normal();

	Geom_Pnt3d Vec = V2->Coord() - V1->Coord();
	Geom_Pnt3d Cross = CrossProduct(Normal0, Normal1);

	Standard_Real Dot = DotProduct(Vec, Cross);

	if (Dot < 0)
		return PI - acos(DotProduct(Normal0, Normal1));
	else
		return PI + acos(DotProduct(Normal0, Normal1));
}