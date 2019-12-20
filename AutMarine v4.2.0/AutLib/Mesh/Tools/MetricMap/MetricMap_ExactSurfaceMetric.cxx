#include <MetricMap_ExactSurfaceMetric.hxx>

#include <Cad3d_SurfaceOnSolid.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;

#include <BRep_Tool.hxx>

AutLib::MeshLib::MetricMap_ExactSurfaceMetric::MetricMap_ExactSurfaceMetric(const M_CAD Cad3d_SurfaceOnSolid& theSurface)
	: MetricMap_SurfaceMetricMap(theSurface)
{
	thePatch_ = theSurface_.Geometry();
}

Entity_Metric1 AutLib::MeshLib::MetricMap_ExactSurfaceMetric::MetricAt(const M_GEO Geom_Pnt2d & Coord) const
{
	gp_Vec D1U, D1V;
	gp_Pnt Pt;

	thePatch_->D1(Coord.X(), Coord.Y(), Pt, D1U, D1V);

	Standard_Real A = D1U.Dot(D1U);
	Standard_Real B = D1U.Dot(D1V);
	Standard_Real C = D1V.Dot(D1V);

	return Entity_Metric1(A, B, C);
}