#include <MetricMap2d_StdBackMetric.hxx>

#include <Entity_Metric1.hxx>
#include <Mesh2d_QualityMap.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::MeshLib::MetricMap2d_StdBackMetric::MetricMap2d_StdBackMetric(const M_GEO GeoMesh_BackGroundMetric2d & theMetric)
	: theMetric_(theMetric)
{
	SetBoundingBox(*theMetric.BoundingBox());
}

Standard_Real AutLib::MeshLib::MetricMap2d_StdBackMetric::ElementQuality
(
	const GeoLib::Geom_Pnt2d & theP0,
	const GeoLib::Geom_Pnt2d & theP1,
	const GeoLib::Geom_Pnt2d & theP2,
	const Mesh2d_QualityMap & theQualityMap
) const
{
	Geom_Pnt2d Pm = (theP0 + theP1 + theP2) / (Standard_Real)3.0;

	Entity_Metric1 M = theMetric_.MetricAt(Pm).SQRT();

	Geom_Pnt2d U1 = theP1 - theP0;
	Geom_Pnt2d U2 = theP2 - theP0;

	U1 = M.Multiplied(U1);
	U2 = M.Multiplied(U2);

	Geom_Pnt2d P1 = theP0 + U1;
	Geom_Pnt2d P2 = theP0 + U2;

	return theQualityMap.CalcQuality(theP0, P1, P2);
}