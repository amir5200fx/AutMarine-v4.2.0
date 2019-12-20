#pragma once
inline
void AutLib::MeshLib::SizeMap2d_UnionMetricMaps::ImportSizeMap(const Global_Handle(M_GEO GeoMesh_BackGroundMetric2d)theBack)
{
	theMetricMaps_.EnQueue((Global_Handle(M_GEO GeoMesh_BackGroundMetric2d))theBack);
}

inline
Standard_Boolean AutLib::MeshLib::SizeMap2d_UnionMetricMaps::IsDone() const
{
	return IsDone_;
}

inline 
Global_Handle(M_GEO GeoMesh_BackGroundMetric2d) AutLib::MeshLib::SizeMap2d_UnionMetricMaps::BackGroundMetric() const
{
	return theBackMetric_;
}