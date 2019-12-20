#include <Mesh3d_QualityMapIsotropicMinSine.hxx>

#include <Tetrahedra_QualityMeasure.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::MeshLib::Mesh3d_QualityMapIsotropicMinSine::Mesh3d_QualityMapIsotropicMinSine()
{
}

Standard_Real AutLib::MeshLib::Mesh3d_QualityMapIsotropicMinSine::CalcQuality
(
	const Geom_Pnt3d & theP0,
	const Geom_Pnt3d & theP1, 
	const Geom_Pnt3d & theP2, 
	const Geom_Pnt3d & theP3
) const
{
	Tetrahedra_QualityMeasure Quality;
	return Quality.CalcMinSineQuality(theP0, theP1, theP2, theP3);
}