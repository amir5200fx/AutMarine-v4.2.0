#include <Cad3d_RingOnSurfaceTools.hxx>

#include <Cad3d_RingOnSurface.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace CadLib;

Standard_Boolean AutLib::CadLib::Cad3d_RingOnSurfaceTools::AreCoincident
(
	const Cad3d_RingOnSurface & Ring1,
	const Cad3d_RingOnSurface & Ring2,
	const Standard_Real Tolerance
)
{
	Geom_Pnt3d P0 = Ring1.StartCoord();
	Geom_Pnt3d P1 = Ring1.Centre();

	Geom_Pnt3d Q0 = Ring2.StartCoord();
	Geom_Pnt3d Q1 = Ring2.Centre();

	if (Distance(P0, Q0) > Tolerance) { return Standard_False; }
	if (Distance(P1, Q1) > Tolerance) { return Standard_False; }

	return Standard_True;
}