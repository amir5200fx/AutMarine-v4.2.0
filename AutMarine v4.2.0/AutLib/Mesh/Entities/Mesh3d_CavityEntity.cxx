#include <Mesh3d_CavityEntity.hxx>

AutLib::MeshLib::Mesh3d_CavityEntity::Mesh3d_CavityEntity()
{
}

AutLib::MeshLib::Mesh3d_CavityEntity::Mesh3d_CavityEntity
(
	const Standard_Integer theIndex,
	const Global_Handle(Mesh3d_CavityShell) theShell
)
	: theIndex_(theIndex)
	, theCavity_(theShell)
{
}

AutLib::MeshLib::Mesh3d_CavityEntity::~Mesh3d_CavityEntity()
{
}

void AutLib::MeshLib::Mesh3d_CavityEntity::Init
(
	const Standard_Integer theIndex, 
	const Global_Handle(Mesh3d_CavityShell) theShell
)
{
	theIndex_ = theIndex;
	theCavity_ = theShell;
}

void AutLib::MeshLib::Mesh3d_CavityEntity::SetIndex(const Standard_Integer theIndex)
{
	theIndex_ = theIndex;
}

void AutLib::MeshLib::Mesh3d_CavityEntity::SetShell(const Global_Handle(Mesh3d_CavityShell) theShell)
{
	theCavity_ = theShell;
}