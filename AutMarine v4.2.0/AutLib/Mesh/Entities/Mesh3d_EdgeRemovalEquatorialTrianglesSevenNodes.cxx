#include <Mesh3d_EdgeRemovalEquatorialTrianglesSevenNodes.hxx>

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesSevenNodes::Mesh3d_EdgeRemovalEquatorialTrianglesSevenNodes()
{
}

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesSevenNodes::Mesh3d_EdgeRemovalEquatorialTrianglesSevenNodes
(
	const TColMesh3d_HAry1dOfNode & theNodes,
	const TColMesh3d_HAry1dOfEdge & theEdges,
	const TColEntity_Ary1dOfTriangleIndex & theTriangles
)
	: Mesh3d_EdgeRemovalEquatorialTriangles(theNodes, theEdges, theTriangles)
{
}

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesSevenNodes::~Mesh3d_EdgeRemovalEquatorialTrianglesSevenNodes()
{
}