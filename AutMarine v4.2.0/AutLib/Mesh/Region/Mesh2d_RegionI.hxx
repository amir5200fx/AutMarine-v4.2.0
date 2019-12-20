#pragma once
inline
const M_MESH Mesh2d_BoundarySizeMapControl & AutLib::MeshLib::Mesh2d_Region::Boundaries() const
{
	return theBoundaries_;
}

inline 
const M_MESH Mesh2d_FeatureSizeMapControl & AutLib::MeshLib::Mesh2d_Region::Features() const
{
	return theFeatures_;
}

inline 
const M_MESH Mesh2d_VolumetricSizeMapControl & AutLib::MeshLib::Mesh2d_Region::Volumetrics() const
{
	return theVolumetrics_;
}

inline 
M_MESH Mesh2d_BoundarySizeMapControl & AutLib::MeshLib::Mesh2d_Region::Boundaries()
{
	return theBoundaries_;
}

inline 
M_MESH Mesh2d_FeatureSizeMapControl & AutLib::MeshLib::Mesh2d_Region::Features()
{
	return theFeatures_;
}

inline 
M_MESH Mesh2d_VolumetricSizeMapControl & AutLib::MeshLib::Mesh2d_Region::Volumetrics()
{
	return theVolumetrics_;
}

inline 
M_MESH SizeMap2d_IsoBackSizeType & AutLib::MeshLib::Mesh2d_Region::Type()
{
	return theSizeMapType_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_Region::IsDone() const
{
	return IsDone_;
}

inline 
const Global_Handle(M_MESH Mesh2d_Plane) AutLib::MeshLib::Mesh2d_Region::Mesh() const
{
	return theMesh_;
}