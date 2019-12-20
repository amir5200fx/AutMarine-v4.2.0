#pragma once
inline
AutLib::MeshLib::Mesh3d_BoundaryNode::Mesh3d_BoundaryNode()
{
}

inline
AutLib::MeshLib::Mesh3d_BoundaryNode::Mesh3d_BoundaryNode
(
	const Standard_Integer Index, 
	const Geom_Pnt3d & Coord
)
	: Mesh3d_Node(Index, Coord)
{
}

inline 
AutLib::MeshLib::Mesh3d_BoundaryNode::~Mesh3d_BoundaryNode()
{
}