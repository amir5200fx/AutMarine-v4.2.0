#include <Mesh3d_CavityShellFourFacetTools.hxx>

#include <Mesh3d_Facet.hxx>
#include <Mesh3d_NodeTools.hxx>
#include <Mesh3d_CavityShellFourFacet.hxx>
#include <TColMesh3d_HAry1dOfFacet.hxx>
#include <TColMesh3d_HAvlTreeOfNode.hxx>

void AutLib::MeshLib::Mesh3d_CavityShellFourFacetTools::RetrieveCandidates
(
	const Mesh3d_CavityShellFourFacet & theShell,
	Global_Handle(Mesh3d_Facet)& theFacet,
	Global_Handle(Mesh3d_Node)& theNode
)
{
	TColMesh3d_HAry1dOfFacet Facets;
	theShell.RetrieveFacetsTo(Facets);

	if (Facets.Size() NOT_EQUAL 4) { THROW_STANDARD_EXCEPTION("Invalid CavityShellFourFacet"); }

	theFacet = Facets[0];

	TColMesh3d_HAvlTreeOfNode Compact;
	Set_Numbering(Compact, Mesh3d_NodeTools::IsLess);

	Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Facets[1]->Node0()));
	Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Facets[1]->Node1()));
	Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Facets[1]->Node2()));

	Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Facets[2]->Node0()));
	Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Facets[2]->Node1()));
	Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Facets[2]->Node2()));

	Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Facets[3]->Node0()));
	Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Facets[3]->Node1()));
	Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Facets[3]->Node2()));

	theNode = NULL;
	TColMesh3d_HAry1dOfNode Nodes;
	Compact.RetrieveTo(Nodes);

	forThose
	(
		Index,
		0, 
		MaxIndexOf(Nodes)
	)
	{
		Debug_Null_Pointer(Nodes[Index]);

		if (Nodes[Index] NOT_EQUAL theFacet->Node0() AND Nodes[Index] NOT_EQUAL theFacet->Node1() AND Nodes[Index] NOT_EQUAL theFacet->Node2())
		{
			theNode = Nodes[Index];
			break;
		}
	}
}