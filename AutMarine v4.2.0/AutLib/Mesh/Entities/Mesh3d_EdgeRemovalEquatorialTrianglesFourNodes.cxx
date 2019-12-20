#include <Mesh3d_EdgeRemovalEquatorialTrianglesFourNodes.hxx>

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesFourNodes::Mesh3d_EdgeRemovalEquatorialTrianglesFourNodes()
{
}

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesFourNodes::Mesh3d_EdgeRemovalEquatorialTrianglesFourNodes
(
	const TColMesh3d_HAry1dOfNode & theNodes, 
	const TColMesh3d_HAry1dOfEdge& theEdges,
	const TColEntity_Ary1dOfTriangleIndex & theTriangles
)
	: Mesh3d_EdgeRemovalEquatorialTriangles(theNodes, theEdges, theTriangles)
{
}

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesFourNodes::~Mesh3d_EdgeRemovalEquatorialTrianglesFourNodes()
{
}