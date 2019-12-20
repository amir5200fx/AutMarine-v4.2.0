#pragma once
inline
Standard_Real AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::BaseSize() const
{
	return theSizeMap_.BaseSize();
}

inline 
Standard_Real AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::ElementSize(const Geom_Pnt2d & Coord) const
{
	return theSizeMap_.ElementSize(theSurface_->Value(Coord.X(), Coord.Y()));
}

inline 
Standard_Real AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::ElementSize(const Mesh2d_Edge & Edge) const
{
	return ElementSize(Edge.Centre());
}