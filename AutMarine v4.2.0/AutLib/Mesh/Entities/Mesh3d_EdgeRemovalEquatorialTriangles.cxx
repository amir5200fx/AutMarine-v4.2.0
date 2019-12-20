#include <Mesh3d_EdgeRemovalEquatorialTriangles.hxx>

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTriangles::Mesh3d_EdgeRemovalEquatorialTriangles()
	: theWorstQuality_(0)
{
}

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTriangles::Mesh3d_EdgeRemovalEquatorialTriangles
(
	const TColMesh3d_HAry1dOfNode & theNodes, 
	const TColMesh3d_HAry1dOfEdge& theEdges,
	const TColEntity_Ary1dOfTriangleIndex & theTriangles
)
	: theNodes_(theNodes)
	, theEdges_(theEdges)
	, theTriangles_(theTriangles)
	, theWorstQuality_(0)
{
}

AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTriangles::~Mesh3d_EdgeRemovalEquatorialTriangles()
{
}

void AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTriangles::Init
(
	const TColMesh3d_HAry1dOfNode & theNodes, 
	const TColMesh3d_HAry1dOfEdge& theEdges,
	const TColEntity_Ary1dOfTriangleIndex & theTriangles
)
{
	theNodes_ = theNodes;
	theEdges_ = theEdges;
	theTriangles_ = theTriangles;
}

void AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTriangles::SetWorstQuality(const Standard_Real theWorstQuality)
{
	theWorstQuality_ = theWorstQuality;
}