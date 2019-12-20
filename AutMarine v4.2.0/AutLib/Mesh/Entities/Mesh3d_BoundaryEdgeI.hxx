#pragma once
inline
AutLib::MeshLib::Mesh3d_BoundaryEdge::Mesh3d_BoundaryEdge()
{
}

inline 
AutLib::MeshLib::Mesh3d_BoundaryEdge::Mesh3d_BoundaryEdge
(
	const Standard_Integer Index, 
	const Standard_Real Length, 
	Global_Handle(Mesh3d_Node) Node0,
	Global_Handle(Mesh3d_Node) Node1
)
	: Mesh3d_Edge(Index, Length, Node0, Node1)
{
}

inline 
AutLib::MeshLib::Mesh3d_BoundaryEdge::~Mesh3d_BoundaryEdge()
{
}