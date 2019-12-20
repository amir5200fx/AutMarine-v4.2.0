#include <Mesh3d_CavityEntityAllThreeFronts.hxx>

AutLib::MeshLib::Mesh3d_CavityEntityAllThreeFronts::Mesh3d_CavityEntityAllThreeFronts()
	: Mesh3d_CavityEntity(0, 0)
	, theApex_(0)
{
}

AutLib::MeshLib::Mesh3d_CavityEntityAllThreeFronts::Mesh3d_CavityEntityAllThreeFronts(const Global_Handle(Mesh3d_Node) theApex)
	: Mesh3d_CavityEntity(0, 0)
	, theApex_(theApex)
{
}

AutLib::MeshLib::Mesh3d_CavityEntityAllThreeFronts::Mesh3d_CavityEntityAllThreeFronts
(
	const Global_Handle(Mesh3d_Node) theApex,
	const Global_Handle(Mesh3d_CavityShell) theShell
)
	: Mesh3d_CavityEntity(0, theShell)
	, theApex_(theApex)
{
}

AutLib::MeshLib::Mesh3d_CavityEntityAllThreeFronts::~Mesh3d_CavityEntityAllThreeFronts()
{
}

void AutLib::MeshLib::Mesh3d_CavityEntityAllThreeFronts::Init(const Global_Handle(Mesh3d_Node) theApex, const Global_Handle(Mesh3d_CavityShell) theShell)
{
	theCavity_ = theShell;
	theApex_ = theApex;
}