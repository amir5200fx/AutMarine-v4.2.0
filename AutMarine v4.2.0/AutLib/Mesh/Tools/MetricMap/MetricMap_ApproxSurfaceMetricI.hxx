#pragma once
inline
Standard_Real AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::MaxMetricDeterminant() const
{
	return theMaxMetricDet_;
}

inline
Standard_Integer AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::NbSingularityHorizons() const
{
	return theSingularityHorizons_.Size();
}

inline 
Standard_Boolean AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::IsDone() const
{
	return IsDone_;
}

inline 
Global_Handle(M_GEO Entity_Polygon2d) AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::SingularityHorizon(const Standard_Integer Index) const
{
	Debug_Bad_Index_Array1(Index, theSingularityHorizons_);
	return theSingularityHorizons_[Index];
}

inline 
const M_GEO GeoMesh_BackGroundMetric2d & AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::Metric() const
{
	return theMetric_;
}

inline
M_GEO Entity_Metric1 AutLib::MeshLib::MetricMap_ApproxSurfaceMetric::MetricAt(const M_GEO Geom_Pnt2d & theCoord) const
{
	return theMetric_.MetricAt(theCoord);
}
