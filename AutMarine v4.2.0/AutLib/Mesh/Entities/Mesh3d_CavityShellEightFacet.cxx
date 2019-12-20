#include <Mesh3d_CavityShellEightFacet.hxx>

#include <Mesh3d_Node.hxx>
#include <TColMesh3d_HAry1dOfNode.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;

AutLib::MeshLib::Mesh3d_CavityShellEightFacet::Mesh3d_CavityShellEightFacet()
{
}

AutLib::MeshLib::Mesh3d_CavityShellEightFacet::Mesh3d_CavityShellEightFacet
(
	Global_Handle(Mesh3d_Facet) theFacet0, 
	Global_Handle(Mesh3d_Facet) theFacet1, 
	Global_Handle(Mesh3d_Facet) theFacet2, 
	Global_Handle(Mesh3d_Facet) theFacet3, 
	Global_Handle(Mesh3d_Facet) theFacet4, 
	Global_Handle(Mesh3d_Facet) theFacet5, 
	Global_Handle(Mesh3d_Facet) theFacet6, 
	Global_Handle(Mesh3d_Facet) theFacet7
)
{
	Mesh3d_CavityShell::ImportToFacets(theFacet0);
	Mesh3d_CavityShell::ImportToFacets(theFacet1);
	Mesh3d_CavityShell::ImportToFacets(theFacet2);
	Mesh3d_CavityShell::ImportToFacets(theFacet3);
	Mesh3d_CavityShell::ImportToFacets(theFacet4);
	Mesh3d_CavityShell::ImportToFacets(theFacet5);
	Mesh3d_CavityShell::ImportToFacets(theFacet6);
	Mesh3d_CavityShell::ImportToFacets(theFacet7);
}

AutLib::MeshLib::Mesh3d_CavityShellEightFacet::~Mesh3d_CavityShellEightFacet()
{
}
