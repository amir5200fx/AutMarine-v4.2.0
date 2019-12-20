#pragma once
inline
const Geom_Pnt3d & AutLib::MeshLib::Mesh2d_SurfaceBoundaryNode::Coord3d() const
{
	return theCoord3d_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_SurfaceBoundaryNode::IsDone() const
{
	return IsDone_;
}

inline 
void AutLib::MeshLib::Mesh2d_SurfaceBoundaryNode::SetCondition(const Standard_Boolean theCondition)
{
	IsDone_ = theCondition;
}

inline 
void AutLib::MeshLib::Mesh2d_SurfaceBoundaryNode::SetCoord3d(const Geom_Pnt3d & theCoord)
{
	theCoord3d_ = theCoord;
}