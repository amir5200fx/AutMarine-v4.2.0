#include <Mesh2d_SurfaceBoundaryNode.hxx>

AutLib::MeshLib::Mesh2d_SurfaceBoundaryNode::Mesh2d_SurfaceBoundaryNode()
{
}

AutLib::MeshLib::Mesh2d_SurfaceBoundaryNode::Mesh2d_SurfaceBoundaryNode
(
	const Standard_Integer Index,
	const Geom_Pnt2d & Coord
)
	: Mesh2d_BoundaryNode(Index, Coord)
{
}

AutLib::MeshLib::Mesh2d_SurfaceBoundaryNode::~Mesh2d_SurfaceBoundaryNode()
{
}