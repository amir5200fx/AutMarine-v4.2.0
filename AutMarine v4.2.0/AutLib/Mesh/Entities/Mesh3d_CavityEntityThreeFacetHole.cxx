#include <Mesh3d_CavityEntityThreeFacetHole.hxx>

AutLib::MeshLib::Mesh3d_CavityEntityThreeFacetHole::Mesh3d_CavityEntityThreeFacetHole()
{
}

AutLib::MeshLib::Mesh3d_CavityEntityThreeFacetHole::Mesh3d_CavityEntityThreeFacetHole
(
	const Global_Handle(Mesh3d_Node) theApex,
	const Global_Handle(Mesh3d_CavityShell) theShell
)
	: Mesh3d_CavityEntity(0, theShell)
	, theApex_(theApex)
{
}

void AutLib::MeshLib::Mesh3d_CavityEntityThreeFacetHole::Init
(
	const Global_Handle(Mesh3d_Node) theApex, 
	const Global_Handle(Mesh3d_CavityShell) theShell
)
{
	theCavity_ = theShell;
	theApex_ = theApex;
}