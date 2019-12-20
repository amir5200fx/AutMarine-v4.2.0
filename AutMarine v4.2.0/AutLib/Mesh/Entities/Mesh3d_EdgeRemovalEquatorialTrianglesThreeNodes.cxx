#include <Mesh3d_EdgeRemovalEquatorialTrianglesThreeNodes.hxx>

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesThreeNodes::Mesh3d_EdgeRemovalEquatorialTrianglesThreeNodes()
{
}

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesThreeNodes::Mesh3d_EdgeRemovalEquatorialTrianglesThreeNodes
(
	const TColMesh3d_HAry1dOfNode & theNodes,
	const TColMesh3d_HAry1dOfEdge& theEdges,
	const TColEntity_Ary1dOfTriangleIndex & theTriangles
)
	: Mesh3d_EdgeRemovalEquatorialTriangles(theNodes, theEdges, theTriangles)
{
}

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesThreeNodes::~Mesh3d_EdgeRemovalEquatorialTrianglesThreeNodes()
{
}