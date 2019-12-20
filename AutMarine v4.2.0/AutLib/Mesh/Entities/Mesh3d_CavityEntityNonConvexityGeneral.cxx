#include <Mesh3d_CavityEntityNonConvexityGeneral.hxx>

AutLib::MeshLib::Mesh3d_CavityEntityNonConvexityGeneral::Mesh3d_CavityEntityNonConvexityGeneral()
	: Mesh3d_CavityEntityNonConvexity()
{
}

AutLib::MeshLib::Mesh3d_CavityEntityNonConvexityGeneral::Mesh3d_CavityEntityNonConvexityGeneral(const Global_Handle(Mesh3d_Edge) theEdge)
	: Mesh3d_CavityEntityNonConvexity(theEdge)
{
}

AutLib::MeshLib::Mesh3d_CavityEntityNonConvexityGeneral::Mesh3d_CavityEntityNonConvexityGeneral
(
	const Global_Handle(Mesh3d_Edge) theEdge, 
	const Global_Handle(Mesh3d_CavityShell) theShell
)
	: Mesh3d_CavityEntityNonConvexity(theEdge, theShell)
{
}

AutLib::MeshLib::Mesh3d_CavityEntityNonConvexityGeneral::~Mesh3d_CavityEntityNonConvexityGeneral()
{
}