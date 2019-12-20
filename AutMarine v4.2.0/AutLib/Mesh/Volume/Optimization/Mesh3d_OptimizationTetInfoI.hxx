#pragma once
#include <Global_Debug.hxx>
inline
Standard_Real AutLib::MeshLib::Mesh3d_OptimizationTetInfo::Volume() const
{
	return theVolume_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_OptimizationTetInfo::Quality() const
{
	return theQuality_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_OptimizationTetInfo::FaceArea(const Standard_Integer theIndex) const
{
	Debug_If_Condition(NOT INSIDE(theIndex, 0, 3));
	return theFaceArea_[theIndex];
}

inline 
const Geom_Pnt3d & AutLib::MeshLib::Mesh3d_OptimizationTetInfo::VolumeGradient() const
{
	return theVolumeGrad_;
}

inline 
const Geom_Pnt3d & AutLib::MeshLib::Mesh3d_OptimizationTetInfo::QualityGradient() const
{
	return theQualityGrad_;
}

inline 
const Geom_Pnt3d & AutLib::MeshLib::Mesh3d_OptimizationTetInfo::FaceAreaGradient(const Standard_Integer theIndex) const
{
	Debug_If_Condition(NOT INSIDE(theIndex, 0, 3));
	return theFaceAreaGrad_[theIndex];
}

inline 
const M_MESH Mesh3d_Element & AutLib::MeshLib::Mesh3d_OptimizationTetInfo::Element() const
{
	return theElement_;
}

inline 
void AutLib::MeshLib::Mesh3d_OptimizationTetInfo::SetVolume(const Standard_Real theVolume)
{
	theVolume_ = theVolume;
}

inline 
void AutLib::MeshLib::Mesh3d_OptimizationTetInfo::SetQuality(const Standard_Real theQuality)
{
	theQuality_ = theQuality;
}

inline 
void AutLib::MeshLib::Mesh3d_OptimizationTetInfo::SetFaceArea(const Standard_Integer theIndex, const Standard_Real theArea)
{
	Debug_If_Condition(NOT INSIDE(theIndex, 0, 3));
	theFaceArea_[theIndex] = theArea;
}

inline 
void AutLib::MeshLib::Mesh3d_OptimizationTetInfo::SetVolumeGradient(const Geom_Pnt3d & theVolumeGrad)
{
	theVolumeGrad_ = theVolumeGrad;
}

inline 
void AutLib::MeshLib::Mesh3d_OptimizationTetInfo::SetQualityGradient(const Geom_Pnt3d & theQualityGrad)
{
	theQualityGrad_ = theQualityGrad;
}

inline 
void AutLib::MeshLib::Mesh3d_OptimizationTetInfo::SetFaceAreaGradient(const Standard_Integer theIndex, const Geom_Pnt3d& theAreaGrad)
{
	Debug_If_Condition(NOT INSIDE(theIndex, 0, 3));
	theFaceAreaGrad_[theIndex] = theAreaGrad;
}