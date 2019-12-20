#include <Mesh3d_CavityEntityPairedElements.hxx>

AutLib::MeshLib::Mesh3d_CavityEntityPairedElements::Mesh3d_CavityEntityPairedElements()
	: Mesh3d_CavityEntityNonConvexity()
{
}

AutLib::MeshLib::Mesh3d_CavityEntityPairedElements::Mesh3d_CavityEntityPairedElements(const Global_Handle(Mesh3d_Edge) thePairedEdge)
	: Mesh3d_CavityEntityNonConvexity(thePairedEdge)
{
}

AutLib::MeshLib::Mesh3d_CavityEntityPairedElements::Mesh3d_CavityEntityPairedElements
(
	const Global_Handle(Mesh3d_Edge) thePairedEdge, 
	const Global_Handle(Mesh3d_CavityShell) theShell
)
	: Mesh3d_CavityEntityNonConvexity(thePairedEdge, theShell)
{
}

AutLib::MeshLib::Mesh3d_CavityEntityPairedElements::~Mesh3d_CavityEntityPairedElements()
{
}