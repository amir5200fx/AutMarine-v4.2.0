#include <QualityMap2d_Vlrms2Ratio.hxx>

#include <Geom\Quality\Burkardt.h>

using namespace AutLib;
using namespace GeoLib;

AutLib::MeshLib::QualityMap2d_Vlrms2Ratio::QualityMap2d_Vlrms2Ratio()
{
}

Standard_Real AutLib::MeshLib::QualityMap2d_Vlrms2Ratio::CalcQuality
(
	const Geom_Pnt2d & theP0,
	const Geom_Pnt2d & theP1,
	const Geom_Pnt2d & theP2
) const
{
	Standard_Real xy[6];

	xy[0] = theP0.X();
	xy[1] = theP0.Y();
	xy[2] = theP1.X();
	xy[3] = theP1.Y();
	xy[4] = theP2.X();
	xy[5] = theP2.Y();

	return triangle_quality_2d(xy);
}