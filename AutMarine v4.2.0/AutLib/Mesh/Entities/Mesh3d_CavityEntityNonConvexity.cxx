#include <Mesh3d_CavityEntityNonConvexity.hxx>

AutLib::MeshLib::Mesh3d_CavityEntityNonConvexity::Mesh3d_CavityEntityNonConvexity()
	: Mesh3d_CavityEntity(0, 0)
	, theEdge_(0)
	, theAngle_(0)
{
}

AutLib::MeshLib::Mesh3d_CavityEntityNonConvexity::Mesh3d_CavityEntityNonConvexity(const Global_Handle(Mesh3d_Edge) theEdge)
	: Mesh3d_CavityEntity(0, 0)
	, theEdge_(theEdge)
	, theAngle_(0)
{
}

AutLib::MeshLib::Mesh3d_CavityEntityNonConvexity::Mesh3d_CavityEntityNonConvexity
(
	const Global_Handle(Mesh3d_Edge) theEdge, 
	const Global_Handle(Mesh3d_CavityShell) theShell
)
	: Mesh3d_CavityEntity(0, theShell)
	, theEdge_(theEdge)
{
}

AutLib::MeshLib::Mesh3d_CavityEntityNonConvexity::~Mesh3d_CavityEntityNonConvexity()
{
}

void AutLib::MeshLib::Mesh3d_CavityEntityNonConvexity::Init
(
	const Global_Handle(Mesh3d_Edge) theEdge, 
	const Global_Handle(Mesh3d_CavityShell) theShell
)
{
	theCavity_ = theShell;
	theEdge_ = theEdge;
}

void AutLib::MeshLib::Mesh3d_CavityEntityNonConvexity::SetAngle(const Standard_Real theAngle)
{
	theAngle_ = theAngle;
}