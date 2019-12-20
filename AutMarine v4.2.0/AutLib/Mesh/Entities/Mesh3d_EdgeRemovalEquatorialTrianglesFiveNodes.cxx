#include <Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodes.hxx>

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodes::Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodes()
{
}

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodes::Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodes
(
	const TColMesh3d_HAry1dOfNode & theNodes, 
	const TColMesh3d_HAry1dOfEdge& theEdges,
	const TColEntity_Ary1dOfTriangleIndex & theTriangles
)
	: Mesh3d_EdgeRemovalEquatorialTriangles(theNodes, theEdges, theTriangles)
{
}

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodes::~Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodes()
{
}