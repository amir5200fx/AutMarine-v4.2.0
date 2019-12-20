#include <Mesh3d_CavityShell.hxx>

#include <Mesh3d_NodeTools.hxx>
#include <Mesh3d_FacetTools.hxx>
#include <Mesh3d_CavityEntityNonConvexity.hxx>
#include <Mesh3d_CavityEntitySwapEdge.hxx>
#include <Mesh3d_CavityEntityTools.hxx>
#include <TColMesh3d_HBasicQueueOfNode.hxx>
#include <TColMesh3d_HBasicQueueOfFacet.hxx>
#include <TColMesh3d_HBasicQueueOfCavityEntityNonConvexity.hxx>
#include <TColMesh3d_HBasicQueueOfCavityEntitySwapEdge.hxx>

using namespace AutLib;

AutLib::MeshLib::Mesh3d_CavityShell::Mesh3d_CavityShell()
{
	Set_Numbering(theFacets_, Mesh3d_FacetTools::IsLess);
	Set_Numbering(theEntities_, Mesh3d_CavityEntityTools::IsLess);
}

AutLib::MeshLib::Mesh3d_CavityShell::~Mesh3d_CavityShell()
{
}

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityShell::IsOnShell(const Global_Handle(Mesh3d_Node) theNode) const
{
	TColMesh3d_HAry1dOfFacet Facets;
	RetrieveFacetsTo(Facets);

	TColMesh3d_HAry1dOfNode Nodes = Mesh3d_FacetTools::RetrieveNodesFrom(Facets);
	forThose(Index, 0, MaxIndexOf(Nodes))
	{
		if (Nodes[Index] EQUAL theNode) return Standard_True;
	}
	return Standard_False;
}

Geom_Pnt3d AutLib::MeshLib::Mesh3d_CavityShell::Centre() const
{
	TColMesh3d_HAry1dOfNode Nodes;
	Mesh3d_CavityShell::RetrieveNodesTo(Nodes);

	Geom_Pnt3d Centre;
	forThose(Index, 0, MaxIndexOf(Nodes))
	{
		Centre += Nodes[Index]->Coord();
	}
	return Centre / (Standard_Real)Nodes.Size();
}

TColMesh3d_HAry1dOfFacet AutLib::MeshLib::Mesh3d_CavityShell::RetrieveFacetsOnShell(const TColMesh3d_HAry1dOfFacet & theFacets) const
{
	TColMesh3d_HBasicQueueOfFacet QFacets;
	forThose
	(
		Index,
		0,
		MaxIndexOf(theFacets)
	)
	{
		Debug_Null_Pointer(theFacets[Index]);
		if (IsOnShell(theFacets[Index])) QFacets.EnQueue(theFacets[Index]);
	}
	TColMesh3d_HAry1dOfFacet Facets;
	QFacets.RetrieveTo(Facets);

	MOVE(Facets);
}

Global_Handle(Mesh3d_Node) AutLib::MeshLib::Mesh3d_CavityShell::HasPick() const
{
	TColMesh3d_HAry1dOfNode totNodes;
	RetrieveNodesTo(totNodes);
	forThose
	(
		Index,
		0,
		MaxIndexOf(totNodes)
	)
	{
		Debug_Null_Pointer(totNodes[Index]);

		if (totNodes[Index]->NbFrontFacets() EQUAL 3) return totNodes[Index];

		TColMesh3d_HAry1dOfFacet totFacets;
		totNodes[Index]->RetrieveFrontsTo(totFacets);

		TColMesh3d_HAry1dOfFacet Facets = RetrieveFacetsOnShell(totFacets);

		if(Facets.Size() EQUAL 3) return totNodes[Index];
	}
	return NULL;
}

void AutLib::MeshLib::Mesh3d_CavityShell::RetrieveNodesTo(TColMesh3d_HAry1dOfNode & theNodes) const
{
	TColMesh3d_HAry1dOfFacet Facets;
	Mesh3d_CavityShell::RetrieveFacetsTo(Facets);

	Mesh3d_FacetTools::RetrieveNodes(Facets, theNodes);
}

void AutLib::MeshLib::Mesh3d_CavityShell::RetrieveEdgesTo(TColMesh3d_HAry1dOfEdge & theEdges) const
{
	TColMesh3d_HAry1dOfFacet Facets;
	Mesh3d_CavityShell::RetrieveFacetsTo(Facets);

	Mesh3d_FacetTools::RetrieveEdges(Facets, theEdges);
}

void AutLib::MeshLib::Mesh3d_CavityShell::RetrieveNonConvexitiesTo(TColMesh3d_HAry1dOfCavityEntityNonConvexity & theNonConvexities) const
{
	TColMesh3d_HAry1dOfCavityEntity Entities;
	RetrieveEntitiesTo(Entities);

	TColMesh3d_HBasicQueueOfCavityEntityNonConvexity QNonConvexity;
	forThose
	(
		Index, 
		0, 
		MaxIndexOf(Entities)
	)
	{
		Debug_Null_Pointer(Entities[Index]);

		Global_Handle(Mesh3d_CavityEntityNonConvexity) NonConvexity = Global_DownCast(Mesh3d_CavityEntityNonConvexity, Entities[Index]);
		if (NonConvexity)
		{
			QNonConvexity.EnQueue(NonConvexity);
		}
	}
	QNonConvexity.RetrieveTo(theNonConvexities);
}

void AutLib::MeshLib::Mesh3d_CavityShell::RetrieveSwapEdgesTo(TColMesh3d_HAry1dOfCavityEntitySwapEdge & theSwapEdges) const
{
	TColMesh3d_HAry1dOfCavityEntity Entities;
	RetrieveEntitiesTo(Entities);

	TColMesh3d_HBasicQueueOfCavityEntitySwapEdge QSwapEdges;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Entities)
	)
	{
		Debug_Null_Pointer(Entities[Index]);

		Global_Handle(Mesh3d_CavityEntitySwapEdge) SwapEdge = Global_DownCast(Mesh3d_CavityEntitySwapEdge, Entities[Index]);
		if (SwapEdge)
		{
			QSwapEdges.EnQueue(SwapEdge);
		}
	}
	QSwapEdges.RetrieveTo(theSwapEdges);
}

void AutLib::MeshLib::Mesh3d_CavityShell::Update()
{
	TColMesh3d_HAry1dOfNode Nodes;
	RetrieveNodesTo(Nodes);

	TColMesh3d_HBasicQueueOfNode QFrontNodes;
	forThose(Index, 0, MaxIndexOf(Nodes))
		if (Nodes[Index]->IsOnFront()) QFrontNodes.EnQueue(Nodes[Index]);
	QFrontNodes.RetrieveTo(Nodes);

	TColMesh3d_HAry1dOfFacet Facets;
	Mesh3d_NodeTools::RetrieveFrontFacets(Nodes, Facets);

	theFacets_.Clear();
	Try_Exception_Handle_Exit(theFacets_.Insert(Facets));
}