#pragma once
inline 
const Standard_String & AutLib::MeshLib::MetricMap_SurfaceMetricMap::Name() const
{
	return theSurfaceName_;
}

inline 
void AutLib::MeshLib::MetricMap_SurfaceMetricMap::SetSurfaceName(const Standard_String& Name)
{
	theSurfaceName_ = Name;
}