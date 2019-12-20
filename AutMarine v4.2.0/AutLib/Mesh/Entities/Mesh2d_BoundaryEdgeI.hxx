#pragma once
inline
AutLib::MeshLib::Mesh2d_BoundaryEdge::Mesh2d_BoundaryEdge()
{
}

inline 
AutLib::MeshLib::Mesh2d_BoundaryEdge::Mesh2d_BoundaryEdge
(
	const Standard_Integer Index,
	const Standard_Real Length,
	const Geom_Pnt2d & Centre,
	Global_Handle(Mesh2d_Node) Node0,
	Global_Handle(Mesh2d_Node) Node1
)
	: Mesh2d_Edge(Index, Length, Centre, Node0, Node1)
{
}

inline 
AutLib::MeshLib::Mesh2d_BoundaryEdge::~Mesh2d_BoundaryEdge()
{
}