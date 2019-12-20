#include <Mesh3d_CavityEntityEdgeMoreTwoFrontFacets.hxx>

AutLib::MeshLib::Mesh3d_CavityEntityEdgeMoreTwoFrontFacets::Mesh3d_CavityEntityEdgeMoreTwoFrontFacets()
	: Mesh3d_CavityEntity(0, 0)
	, theEdge_(0)
{
}

AutLib::MeshLib::Mesh3d_CavityEntityEdgeMoreTwoFrontFacets::Mesh3d_CavityEntityEdgeMoreTwoFrontFacets(const Global_Handle(Mesh3d_Edge) theEdge)
	: Mesh3d_CavityEntity(0, 0)
	, theEdge_(theEdge)
{
}

AutLib::MeshLib::Mesh3d_CavityEntityEdgeMoreTwoFrontFacets::Mesh3d_CavityEntityEdgeMoreTwoFrontFacets
(
	const Global_Handle(Mesh3d_Edge) theEdge,
	const Global_Handle(Mesh3d_CavityShell) theShell
)
	: Mesh3d_CavityEntity(0, theShell)
	, theEdge_(theEdge)
{
}

void AutLib::MeshLib::Mesh3d_CavityEntityEdgeMoreTwoFrontFacets::Init
(
	const Global_Handle(Mesh3d_Edge) theEdge, 
	const Global_Handle(Mesh3d_CavityShell) theShell
)
{
	theEdge_ = theEdge;
	theCavity_ = theShell;
}