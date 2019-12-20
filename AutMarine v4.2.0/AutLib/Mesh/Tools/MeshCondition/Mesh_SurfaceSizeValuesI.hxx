#pragma once
inline
AutLib::MeshLib::Mesh_SizeMethodInfo & AutLib::MeshLib::Mesh_SurfaceSizeValues::SizeMethod()
{
	return theSizeMethod_;
}

inline 
AutLib::MeshLib::Mesh_RelativeAbsoluteInfo & AutLib::MeshLib::Mesh_SurfaceSizeValues::RelativeAbsolute()
{
	return theRelativeAbsolute_;
}

inline 
AutLib::MeshLib::Mesh_SizeMethodInfo AutLib::MeshLib::Mesh_SurfaceSizeValues::SizeMethod() const
{
	return theSizeMethod_;
}

inline 
AutLib::MeshLib::Mesh_RelativeAbsoluteInfo AutLib::MeshLib::Mesh_SurfaceSizeValues::RelativeAbsolute() const
{
	return theRelativeAbsolute_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh_SurfaceSizeValues::MinSize() const
{
	return theMinSize_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh_SurfaceSizeValues::TargetSize() const
{
	return theTargetSize_;
}