#include <Mesh2d_DegenBoundaryNode.hxx>

AutLib::MeshLib::Mesh2d_DegenBoundaryNode::Mesh2d_DegenBoundaryNode()
{
}

AutLib::MeshLib::Mesh2d_DegenBoundaryNode::Mesh2d_DegenBoundaryNode
(
	const Standard_Integer theIndex,
	const Geom_Pnt2d & theCoord
)
	: Mesh2d_SurfaceBoundaryNode(theIndex, theCoord)
{
}

AutLib::MeshLib::Mesh2d_DegenBoundaryNode::Mesh2d_DegenBoundaryNode
(
	const Standard_Integer theIndex, 
	const Geom_Pnt2d & theCoord, 
	const Geom_Pnt2d & theOrigin
)
	: Mesh2d_SurfaceBoundaryNode(theIndex, theCoord)
	, theOrigin_(theOrigin)
{
}

AutLib::MeshLib::Mesh2d_DegenBoundaryNode::~Mesh2d_DegenBoundaryNode()
{
}