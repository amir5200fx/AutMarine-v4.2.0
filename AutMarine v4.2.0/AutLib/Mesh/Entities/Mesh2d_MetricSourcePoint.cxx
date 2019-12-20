#include <Mesh2d_MetricSourcePoint.hxx>

AutLib::MeshLib::Mesh2d_MetricSourcePoint::Mesh2d_MetricSourcePoint()
{
}

AutLib::MeshLib::Mesh2d_MetricSourcePoint::Mesh2d_MetricSourcePoint
(
	const Geom_Pnt2d & theCoord,
	const M_GEO Entity_Metric1 & theMetric
)
	: Mesh2d_SourcePoint(theCoord, 0)
	, theMetric_(theMetric)
{
}

void AutLib::MeshLib::Mesh2d_MetricSourcePoint::Init
(
	const Geom_Pnt2d & theCoord,
	const M_GEO Entity_Metric1 & theMetric
)
{
	theCoord_ = theCoord;
	theMetric_ = theMetric;
	theValue_ = 0;
}

void AutLib::MeshLib::Mesh2d_MetricSourcePoint::SetMetric(const M_GEO Entity_Metric1 & theMetric)
{
	theMetric_ = theMetric;
}