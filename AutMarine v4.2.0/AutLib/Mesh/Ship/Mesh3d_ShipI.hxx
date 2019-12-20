#pragma once
inline
Global_Handle(M_CAD Compound_Ship) AutLib::MeshLib::Mesh3d_Ship::Ship() const
{
	return theShip_;
}

inline 
Global_Handle(M_MESH Mesh3d_Region) AutLib::MeshLib::Mesh3d_Ship::Region() const
{
	return theRegion_;
}

inline 
Global_Handle(M_MESH Mesh_ReferenceValues) AutLib::MeshLib::Mesh3d_Ship::Reference() const
{
	return theReference_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Ship::IsDone() const
{
	return IsDone_;
}