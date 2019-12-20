#pragma once
#include <Global_DefineException.hxx>
inline
M_GEO Entity_Metric1 AutLib::MeshLib::MetricMap2d_StdBackMetric::MetricAt(const GeoLib::Geom_Pnt2d & theCoord) const
{
	M_GEO Entity_Metric1 Metric;

	Metric = theMetric_.MetricAt(theCoord);
	//cout << "Metric = ";
	//Metric.Print();
	//Metric.RemoveDegeneracy(1.0E-6);
	MOVE(Metric);
}