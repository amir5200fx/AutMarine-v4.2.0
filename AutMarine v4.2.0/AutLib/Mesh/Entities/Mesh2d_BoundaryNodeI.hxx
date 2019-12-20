#pragma once
inline
AutLib::MeshLib::Mesh2d_BoundaryNode::Mesh2d_BoundaryNode()
{
}

inline 
AutLib::MeshLib::Mesh2d_BoundaryNode::Mesh2d_BoundaryNode
(
	const Standard_Integer Index, 
	const Geom_Pnt2d & Coord
)
	: Mesh2d_Node(Index, Coord)
{
}

inline 
AutLib::MeshLib::Mesh2d_BoundaryNode::~Mesh2d_BoundaryNode()
{
}

inline
Standard_Real AutLib::MeshLib::Mesh2d_BoundaryNode::Parameter() const
{
	return theParameter_;
}

inline
void AutLib::MeshLib::Mesh2d_BoundaryNode::SetParameter(const Standard_Real theParameter)
{
	theParameter_ = theParameter;
}