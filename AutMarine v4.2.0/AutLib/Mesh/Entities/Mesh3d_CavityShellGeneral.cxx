#include <Mesh3d_CavityShellGeneral.hxx>

AutLib::MeshLib::Mesh3d_CavityShellGeneral::Mesh3d_CavityShellGeneral()
{
}

AutLib::MeshLib::Mesh3d_CavityShellGeneral::Mesh3d_CavityShellGeneral(const TColMesh3d_HAry1dOfFacet & theFacets)
{
	forThose(Index, 0, MaxIndexOf(theFacets))
	{
		Debug_Null_Pointer(theFacets[Index]);

		Mesh3d_CavityShell::ImportToFacets(theFacets[Index]);
	}
}

AutLib::MeshLib::Mesh3d_CavityShellGeneral::~Mesh3d_CavityShellGeneral()
{
}