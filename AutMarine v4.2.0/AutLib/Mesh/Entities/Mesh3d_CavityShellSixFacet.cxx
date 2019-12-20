#include <Mesh3d_CavityShellSixFacet.hxx>

#include <Geometry_Tools.hxx>
#include <Mesh3d_FacetTools.hxx>
#include <TColMesh3d_HBasicQueueOfNode.hxx>

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

AutLib::MeshLib::Mesh3d_CavityShellSixFacet::Mesh3d_CavityShellSixFacet()
	: theVertex0_(NULL)
	, theVertex1_(NULL)
{
}

AutLib::MeshLib::Mesh3d_CavityShellSixFacet::Mesh3d_CavityShellSixFacet
(
	Global_Handle(Mesh3d_Facet) theFacet0,
	Global_Handle(Mesh3d_Facet) theFacet1,
	Global_Handle(Mesh3d_Facet) theFacet2,
	Global_Handle(Mesh3d_Facet) theFacet3, 
	Global_Handle(Mesh3d_Facet) theFacet4,
	Global_Handle(Mesh3d_Facet) theFacet5
)
{
	Mesh3d_CavityShell::ImportToFacets(theFacet0);
	Mesh3d_CavityShell::ImportToFacets(theFacet1);
	Mesh3d_CavityShell::ImportToFacets(theFacet2);
	Mesh3d_CavityShell::ImportToFacets(theFacet3);
	Mesh3d_CavityShell::ImportToFacets(theFacet4);
	Mesh3d_CavityShell::ImportToFacets(theFacet5);

	Try_Exception_Handle_Exit(FindApices());
}

AutLib::MeshLib::Mesh3d_CavityShellSixFacet::~Mesh3d_CavityShellSixFacet()
{
}

void AutLib::MeshLib::Mesh3d_CavityShellSixFacet::FindApices()
{
	TColMesh3d_HAry1dOfFacet Facets;
	RetrieveFacetsTo(Facets);

	TColMesh3d_HAry1dOfNode Nodes = Mesh3d_FacetTools::RetrieveNodesFrom(Facets);
	if (Nodes.Size() NOT_EQUAL 5) { THROW_STANDARD_EXCEPTION("Contradictory Data"); }

	TColMesh3d_HBasicQueueOfNode QApices;
	TColMesh3d_HBasicQueueOfNode QEquatorial;
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Nodes)
	)
	{
		Debug_Null_Pointer(Nodes[Index]);

		TColMesh3d_HAry1dOfFacet AllFrontFacets;
		Nodes[Index]->RetrieveFrontsTo(AllFrontFacets);

		TColMesh3d_HAry1dOfFacet FrontsOnShell = RetrieveFacetsOnShell(AllFrontFacets);

		if (FrontsOnShell.Size() > 4) { THROW_STANDARD_EXCEPTION("Contradictory Data"); }
		if (FrontsOnShell.Size() < 3) { THROW_STANDARD_EXCEPTION("Contradictory Data"); }

		if (FrontsOnShell.Size() EQUAL 3) QApices.EnQueue(Nodes[Index]);
		if (FrontsOnShell.Size() EQUAL 4) QEquatorial.EnQueue(Nodes[Index]);
	}

	if (QEquatorial.Size() NOT_EQUAL 3) { THROW_STANDARD_EXCEPTION("Contradictory Data"); }
	if (QApices.Size() NOT_EQUAL 2) { THROW_STANDARD_EXCEPTION("Contradictory Data"); }

	QEquatorial.RetrieveTo(theEquatorial_);

	QApices.RetrieveTo(Nodes);
	theVertex0_ = Nodes[0];
	theVertex1_ = Nodes[1];

	if (Geometry_Tools::VolumeOfTetrahedron(theEquatorial_[0]->Coord(), theEquatorial_[1]->Coord(), theEquatorial_[2]->Coord(), theVertex0_->Coord()) < 0)
	{
		SWAP(theVertex0_, theVertex1_);
	}
}