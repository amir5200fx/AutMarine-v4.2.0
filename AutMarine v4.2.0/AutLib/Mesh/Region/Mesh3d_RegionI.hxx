#pragma once
inline
const M_MESH Mesh3d_BoundarySizeMapControl & AutLib::MeshLib::Mesh3d_Region::Boundaries() const
{
	return theBoundaries_;
}

inline 
const M_MESH Mesh3d_VolumetricSizeMapControl & AutLib::MeshLib::Mesh3d_Region::Volumetric() const
{
	return theVolumetric_;
}

inline 
M_MESH Mesh3d_BoundarySizeMapControl & AutLib::MeshLib::Mesh3d_Region::Boundaries()
{
	return theBoundaries_;
}

inline 
M_MESH Mesh3d_VolumetricSizeMapControl& AutLib::MeshLib::Mesh3d_Region::Volumetric()
{
	return theVolumetric_;
}

inline 
M_MESH SizeMap3d_IsoBackSizeType & AutLib::MeshLib::Mesh3d_Region::BackSizeType()
{
	return theSizeMapType_;
}

inline 
M_MESH QualityMap3d_TypesInfo & AutLib::MeshLib::Mesh3d_Region::QualityType()
{
	return theQualityType_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Region::IsDone() const
{
	return IsDone_;
}

inline 
const Global_Handle(M_MESH Mesh3d_Volume) AutLib::MeshLib::Mesh3d_Region::Mesh() const
{
	return theMesh_;
}