#include <MetricMap_SurfaceMetricMap.hxx>

#include <Cad3d_SurfaceOnSolid.hxx>
#include <Geometry_Tools.hxx>
#include <Mesh2d_QualityMap.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace CadLib;

#include <Geom_Surface.hxx>
#include <BRep_Tool.hxx>
#include <Bnd_Box2d.hxx>
#include <BndLib_Add2dCurve.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>

Entity_Metric1 AutLib::MeshLib::MetricMap_SurfaceMetricMap::MetricAt(const M_GEO Geom_Pnt2d & Coord) const
{
	CloseProgram("It's not supossed to call this function");
	return Entity_Metric1();
}

Standard_Real AutLib::MeshLib::MetricMap_SurfaceMetricMap::ElementQuality
(
	const GeoLib::Geom_Pnt2d & theP0,
	const GeoLib::Geom_Pnt2d & theP1,
	const GeoLib::Geom_Pnt2d & theP2,
	const Mesh2d_QualityMap & theQualityMap
) const
{
	Geom_Pnt3d Q0 = theSurface_.Value(theP0);
	Geom_Pnt3d Q1 = theSurface_.Value(theP1);
	Geom_Pnt3d Q2 = theSurface_.Value(theP2);

	Geom_Pnt2d P0(0, 0), P1, P2;
	Geometry_Tools::ConvertTriangleTo2D(Q0, Q1, Q2, P1, P2);

	if (Geometry_Tools::AreaOfTriangleAdapt(P0, P1, P2) <= 0) return 0;
	return theQualityMap.CalcQuality(P0, P1, P2);
}

AutLib::MeshLib::MetricMap_SurfaceMetricMap::MetricMap_SurfaceMetricMap(const M_CAD Cad3d_SurfaceOnSolid & theSurface)
	: theSurface_(theSurface)
	, theSurfaceName_("Unknown")
{
}

Entity_Box2d AutLib::MeshLib::MetricMap_SurfaceMetricMap::CalcBoundingBox() const
{
	return theSurface_.ParametricBoundingBox();
}