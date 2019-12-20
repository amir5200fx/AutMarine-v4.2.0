#include <Mesh3d_FacetTools.hxx>

#include <Entity_StaticChain3d.hxx>
#include <Geometry_Intersect.hxx>
#include <Mesh3d_Element.hxx>
#include <Mesh3d_NodeTools.hxx>
#include <Mesh3d_EdgeTools.hxx>
#include <TColMesh3d_HAvlTreeOfNode.hxx>
#include <TColMesh3d_HAvlTreeOfEdge.hxx>

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

M_AUT TColEntity_Ary1dOfTriangleIndex AutLib::MeshLib::Mesh3d_FacetTools::StaticOf(const TColMesh3d_HAry1dOfFacet & Facets)
{
	TColEntity_Ary1dOfTriangleIndex Statics(Facets.Size());

	forThose
	(
		Index,
		0,
		MaxIndexOf(Statics)
	)
	{
		Debug_Null_Pointer(Facets[Index]);

		Get_Const_Object(Element) = *Facets[Index];

		Statics[Index].SetValue
		(
			Element.Node(0)->Index(),
			Element.Node(1)->Index(),
			Element.Node(2)->Index()
		);
	}

	MOVE(Statics);
}

Standard_Boolean AutLib::MeshLib::Mesh3d_FacetTools::IsGoodToFlip(const Mesh3d_Facet & theFacet)
{
	Debug_Null_Pointer(theFacet.LeftElement());
	Debug_Null_Pointer(theFacet.RightElement());

	Get_Const_Object(LeftElement) = *theFacet.LeftElement();
	Get_Const_Object(RightElement) = *theFacet.RightElement();

	Global_Handle(Mesh3d_Node) LeftVertex = LeftElement.OppositeVertex(&theFacet);
	Global_Handle(Mesh3d_Node) RightVertex = RightElement.OppositeVertex(&theFacet);

	Debug_Null_Pointer(LeftVertex);
	Debug_Null_Pointer(RightVertex);

	if (Geometry_Intersect::IsIntersectLineSegmentTriangle(LeftVertex->Coord(), RightVertex->Coord(), theFacet.Node0()->Coord(), theFacet.Node1()->Coord(), theFacet.Node2()->Coord()))
	{
		return Standard_True;
	}
	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_FacetTools::CheckFront(const TColMesh3d_HAry1dOfFacet & theFacet)
{
	forThose(Index, 0, MaxIndexOf(theFacet))
		if (NOT theFacet[Index]->IsOnFront()) return Standard_True;
	return Standard_False;
}

Global_Handle(Mesh3d_Facet) AutLib::MeshLib::Mesh3d_FacetTools::GetCommonFrontFacetOf
(
	const Mesh3d_Node & theNode0,
	const Mesh3d_Node & theNode1, 
	const Mesh3d_Node & theNode2
)
{
	TColMesh3d_HAry1dOfFacet Facets0;
	theNode0.RetrieveFrontsTo(Facets0);

	TColMesh3d_HAvlTreeOfFacet Compact0;
	Set_Numbering(Compact0, Mesh3d_FacetTools::IsLess);

	Try_Exception_Handle_Exit(Compact0.Insert(Facets0));

	TColMesh3d_HAry1dOfFacet Facets1;
	theNode1.RetrieveFrontsTo(Facets1);

	TColMesh3d_HAvlTreeOfFacet Compact1;
	Set_Numbering(Compact1, Mesh3d_FacetTools::IsLess);

	forThose(Index, 0, MaxIndexOf(Facets1))
		if (Compact0.IsContains(Facets1[Index])) Try_Exception_Handle_Exit(Compact1.Insert(Facets1[Index]));

	TColMesh3d_HAry1dOfFacet Facets2;
	theNode1.RetrieveFrontsTo(Facets2);

	forThose(Index, 0, MaxIndexOf(Facets2))
		if (Compact1.IsContains(Facets2[Index])) return Facets2[Index];

	return NULL;
}

TColMesh3d_HAry1dOfNode AutLib::MeshLib::Mesh3d_FacetTools::RetrieveNodesFrom(const TColMesh3d_HAry1dOfFacet & theFacets)
{
	TColMesh3d_HAvlTreeOfNode Compact;

	Set_Numbering(Compact, Mesh3d_NodeTools::IsLess);

	forThose
	(
		Index, 
		0,
		MaxIndexOf(theFacets)
	)
	{
		Debug_Null_Pointer(theFacets[Index]);

		Get_Const_Object(Facet) = *theFacets[Index];

		Debug_Null_Pointer(Facet.Node0());
		Debug_Null_Pointer(Facet.Node1());
		Debug_Null_Pointer(Facet.Node2());

		Compact.InsertIgnoreDup(Facet.Node0());
		Compact.InsertIgnoreDup(Facet.Node1());
		Compact.InsertIgnoreDup(Facet.Node2());
	}

	TColMesh3d_HAry1dOfNode Nodes;
	Compact.RetrieveTo(Nodes);

	MOVE(Nodes);
}

TColMesh3d_HAry1dOfEdge AutLib::MeshLib::Mesh3d_FacetTools::RetrieveEdgesFrom(const TColMesh3d_HAry1dOfFacet & theFacets)
{
	TColMesh3d_HAvlTreeOfEdge Compact;

	Set_Numbering(Compact, Mesh3d_EdgeTools::IsLess);

	forThose
	(
		Index, 
		0, 
		MaxIndexOf(theFacets)
	)
	{
		Debug_Null_Pointer(theFacets[Index]);

		Get_Const_Object(Facet) = *theFacets[Index];

		Debug_Null_Pointer(Facet.Edge0());
		Debug_Null_Pointer(Facet.Edge1());
		Debug_Null_Pointer(Facet.Edge2());

		Compact.InsertIgnoreDup(Facet.Edge0());
		Compact.InsertIgnoreDup(Facet.Edge1());
		Compact.InsertIgnoreDup(Facet.Edge2());
	}

	TColMesh3d_HAry1dOfEdge Edges;
	Compact.RetrieveTo(Edges);

	MOVE(Edges);
}

void AutLib::MeshLib::Mesh3d_FacetTools::RetrieveNodes
(
	const TColMesh3d_HAry1dOfFacet & theFacets,
	TColMesh3d_HAry1dOfNode & theNodes
)
{
	TColMesh3d_HAvlTreeOfNode Compact;

	Set_Numbering(Compact, Mesh3d_NodeTools::IsLess);

	forThose
	(
		Index,
		0,
		MaxIndexOf(theFacets)
	)
	{
		Debug_Null_Pointer(theFacets[Index]);

		Get_Const_Object(Facet) = *theFacets[Index];

		Debug_Null_Pointer(Facet.Node0());
		Debug_Null_Pointer(Facet.Node1());
		Debug_Null_Pointer(Facet.Node2());

		Compact.InsertIgnoreDup(Facet.Node0());
		Compact.InsertIgnoreDup(Facet.Node1());
		Compact.InsertIgnoreDup(Facet.Node2());
	}

	Compact.RetrieveTo(theNodes);
}

void AutLib::MeshLib::Mesh3d_FacetTools::RetrieveEdges
(
	const TColMesh3d_HAry1dOfFacet & theFacets,
	TColMesh3d_HAry1dOfEdge & theEdges
)
{
	TColMesh3d_HAvlTreeOfEdge Compact;

	Set_Numbering(Compact, Mesh3d_EdgeTools::IsLess);

	forThose
	(
		Index,
		0,
		MaxIndexOf(theFacets)
	)
	{
		Debug_Null_Pointer(theFacets[Index]);

		Get_Const_Object(Facet) = *theFacets[Index];

		Debug_Null_Pointer(Facet.Edge0());
		Debug_Null_Pointer(Facet.Edge1());
		Debug_Null_Pointer(Facet.Edge2());

		Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Facet.Edge0()));
		Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Facet.Edge1()));
		Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Facet.Edge2()));
	}
	Compact.RetrieveTo(theEdges);
}

void AutLib::MeshLib::Mesh3d_FacetTools::RetrieveNormals
(
	const TColMesh3d_HAry1dOfFacet & theFacets,
	GeoLib::Entity_StaticChain3d & theChain
)
{
	Get_Object(Pts) = theChain.Coords();
	Pts.Resize(theFacets.Size() * 2);

	Standard_Integer K = 0;
	forThose
	(
		Index, 
		0, 
		MaxIndexOf(theFacets)
	)
	{
		Debug_Null_Pointer(theFacets[Index]);

		Get_Const_Object(Facet) = *theFacets[Index];

		Pts[K] = Facet.Centre();
		K++;
		Pts[K] = Facet.Normal()*Facet.Length() + Facet.Centre();
		K++;
	}

	Get_Object(Edges) = theChain.Edges();
	Edges.Resize(theFacets.Size());

	K = 0;
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Edges)
	)
	{
		K++;
		Edges[Index].V0() = K;

		K++;
		Edges[Index].V1() = K;
	}
}