#include <Mesh3d_CavityShellTenFacet.hxx>

AutLib::MeshLib::Mesh3d_CavityShellTenFacet::Mesh3d_CavityShellTenFacet()
{
}

AutLib::MeshLib::Mesh3d_CavityShellTenFacet::Mesh3d_CavityShellTenFacet
(
	Global_Handle(Mesh3d_Facet) theFacet0,
	Global_Handle(Mesh3d_Facet) theFacet1,
	Global_Handle(Mesh3d_Facet) theFacet2, 
	Global_Handle(Mesh3d_Facet) theFacet3, 
	Global_Handle(Mesh3d_Facet) theFacet4,
	Global_Handle(Mesh3d_Facet) theFacet5,
	Global_Handle(Mesh3d_Facet) theFacet6,
	Global_Handle(Mesh3d_Facet) theFacet7,
	Global_Handle(Mesh3d_Facet) theFacet8,
	Global_Handle(Mesh3d_Facet) theFacet9
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
	Mesh3d_CavityShell::ImportToFacets(theFacet8);
	Mesh3d_CavityShell::ImportToFacets(theFacet9);
}

AutLib::MeshLib::Mesh3d_CavityShellTenFacet::~Mesh3d_CavityShellTenFacet()
{
}