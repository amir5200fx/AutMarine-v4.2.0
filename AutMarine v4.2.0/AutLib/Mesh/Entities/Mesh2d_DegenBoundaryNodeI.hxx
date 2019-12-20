#pragma once
inline
const Geom_Pnt2d & AutLib::MeshLib::Mesh2d_DegenBoundaryNode::Origin() const
{
	return theOrigin_;
}

inline 
void AutLib::MeshLib::Mesh2d_DegenBoundaryNode::SetOrigin(const Geom_Pnt2d & theOrigin)
{
	theOrigin_ = theOrigin;
}

inline 
void AutLib::MeshLib::Mesh2d_DegenBoundaryNode::TranslateToOrigin()
{
	Mesh2d_Node::SetCoord(theOrigin_);
}