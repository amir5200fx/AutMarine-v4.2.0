#include <Mesh3d_NodeTools.hxx>

#include <Mesh3d_Edge.hxx>
#include <Mesh3d_FacetTools.hxx>

using namespace AutLib;
using namespace MeshLib;

Standard_Integer AutLib::MeshLib::Mesh3d_NodeTools::GetMaxIndexOf(const TColMesh3d_HAry1dOfNode & theNodes)
{
	if (theNodes.IsEmpty()) { THROW_STANDARD_EXCEPTION(" Empty List"); }

	Standard_Integer MaxIndex = theNodes[0]->Index();
	forThose(Index, 0, MaxIndexOf(theNodes))
	{
		Debug_Null_Pointer(theNodes[Index]);

		Get_Const_Object(Node) = *theNodes[Index];

		if (Node.Index() > MaxIndex) MaxIndex = Node.Index();
	}
	return MaxIndex;
}

M_AUT TColGeom_Ary1dOfPnt3d AutLib::MeshLib::Mesh3d_NodeTools::GetCoordOf(const TColMesh3d_HAry1dOfNode & Nodes)
{
	TColGeom_Ary1dOfPnt3d Points(Nodes.Size());

	forThose
	(
		Index,
		0, 
		MaxIndexOf(Points)
	)
	{
		Debug_Null_Pointer(Nodes[Index]);

		Points[Index] = Nodes[Index]->Coord();
	}

	MOVE(Points);
}

Global_Handle(Mesh3d_Edge) AutLib::MeshLib::Mesh3d_NodeTools::HasAFrontEdgeBetween
(
	const Mesh3d_Node & theNode0,
	const Mesh3d_Node & theNode1
)
{
	TColMesh3d_HAry1dOfEdge Edges;
	theNode0.RetrieveFrontsTo(Edges);

	forThose
	(
		Index,
		0, 
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		if (Edges[Index]->Node0() EQUAL &theNode1 OR Edges[Index]->Node1() EQUAL &theNode1)
		{
			return Edges[Index];
		}
	}
	return NULL;
}

void AutLib::MeshLib::Mesh3d_NodeTools::RetrieveFrontFacets
(
	const TColMesh3d_HAry1dOfNode & theNodes,
	TColMesh3d_HAry1dOfFacet & theFacets
)
{
	TColMesh3d_HAvlTreeOfFacet Compact;
	Set_Numbering(Compact, Mesh3d_FacetTools::IsLess);

	forThose
	(
		Index,
		0,
		MaxIndexOf(theNodes)
	)
	{
		Debug_Null_Pointer(theNodes[Index]);

		TColMesh3d_HAry1dOfFacet Facets;
		theNodes[Index]->RetrieveFrontsTo(Facets);

		forThose
		(
			J,
			0,
			MaxIndexOf(Facets)
		)
		{
			Debug_Null_Pointer(Facets[J]);
			Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Facets[J]));
		}
	}
	Compact.RetrieveTo(theFacets);
}