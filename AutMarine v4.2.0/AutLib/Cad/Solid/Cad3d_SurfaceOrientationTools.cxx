#include <Cad3d_SurfaceOrientationTools.hxx>

using namespace AutLib;
using namespace CadLib;

Cad3d_SurfaceOrientationInfo AutLib::CadLib::Cad3d_SurfaceOrientationTools::ReverseOf(const Cad3d_SurfaceOrientationInfo theOrientation)
{
	if (theOrientation == Cad3d_SurfaceOrientation_UNKNOWN) return Cad3d_SurfaceOrientation_UNKNOWN;
	if (theOrientation == Cad3d_SurfaceOrientation_OUTWARD) return Cad3d_SurfaceOrientation_INWARD;
	if (theOrientation == Cad3d_SurfaceOrientation_INWARD) return Cad3d_SurfaceOrientation_OUTWARD;

	return Cad3d_SurfaceOrientation_UNKNOWN;  // prevent compiler warning
}