#include <Mesh3d_EdgeRemovalEquatorialTrianglesSixNodes.hxx>

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesSixNodes::Mesh3d_EdgeRemovalEquatorialTrianglesSixNodes()
{
}

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesSixNodes::Mesh3d_EdgeRemovalEquatorialTrianglesSixNodes
(
	const TColMesh3d_HAry1dOfNode & theNodes,
	const TColMesh3d_HAry1dOfEdge & theEdges,
	const TColEntity_Ary1dOfTriangleIndex & theTriangles
)
	: Mesh3d_EdgeRemovalEquatorialTriangles(theNodes, theEdges, theTriangles)
{
}

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesSixNodes::~Mesh3d_EdgeRemovalEquatorialTrianglesSixNodes()
{
}