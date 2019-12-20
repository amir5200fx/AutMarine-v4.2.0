#include <Mesh3d_CavityShellFourFacet.hxx>

AutLib::MeshLib::Mesh3d_CavityShellFourFacet::Mesh3d_CavityShellFourFacet()
{
}

AutLib::MeshLib::Mesh3d_CavityShellFourFacet::Mesh3d_CavityShellFourFacet
(
	Global_Handle(Mesh3d_Facet) theFacet0,
	Global_Handle(Mesh3d_Facet) theFacet1,
	Global_Handle(Mesh3d_Facet) theFacet2,
	Global_Handle(Mesh3d_Facet) theFacet3
)
{
	Mesh3d_CavityShell::ImportToFacets(theFacet0);
	Mesh3d_CavityShell::ImportToFacets(theFacet1);
	Mesh3d_CavityShell::ImportToFacets(theFacet2);
	Mesh3d_CavityShell::ImportToFacets(theFacet3);
}

AutLib::MeshLib::Mesh3d_CavityShellFourFacet::~Mesh3d_CavityShellFourFacet()
{
}