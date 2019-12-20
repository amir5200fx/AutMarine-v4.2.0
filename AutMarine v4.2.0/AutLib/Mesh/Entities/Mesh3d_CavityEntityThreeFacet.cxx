#include <Mesh3d_CavityEntityThreeFacet.hxx>

AutLib::MeshLib::Mesh3d_CavityEntityThreeFacet::Mesh3d_CavityEntityThreeFacet()
	: Mesh3d_CavityEntity(0, 0)
	, theElement_(0)
{
}

AutLib::MeshLib::Mesh3d_CavityEntityThreeFacet::Mesh3d_CavityEntityThreeFacet(const Global_Handle(Mesh3d_Element) theElement)
	: Mesh3d_CavityEntity(0, 0)
	, theElement_(theElement)
{
}

AutLib::MeshLib::Mesh3d_CavityEntityThreeFacet::Mesh3d_CavityEntityThreeFacet
(
	const Global_Handle(Mesh3d_Element) theElement,
	const Global_Handle(Mesh3d_CavityShell) theShell
)
	: Mesh3d_CavityEntity(0, theShell)
	, theElement_(theElement)
{
}

AutLib::MeshLib::Mesh3d_CavityEntityThreeFacet::~Mesh3d_CavityEntityThreeFacet()
{
}

void AutLib::MeshLib::Mesh3d_CavityEntityThreeFacet::Init(const Global_Handle(Mesh3d_Element) theElement)
{
	theElement_ = theElement;
}