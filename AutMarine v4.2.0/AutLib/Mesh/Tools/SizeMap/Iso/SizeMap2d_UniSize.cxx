#include <SizeMap2d_UniSize.hxx>

#include <Mesh2d_QualityMap.hxx>

AutLib::MeshLib::SizeMap2d_UniSize::SizeMap2d_UniSize(const Standard_Real Size)
	: theSize_(Size)
{
	theInvSize_ = 1.0 / theSize_;
}

Standard_Real AutLib::MeshLib::SizeMap2d_UniSize::ElementQuality
(
	const Geom_Pnt2d & theP0,
	const Geom_Pnt2d & theP1,
	const Geom_Pnt2d & theP2,
	const Mesh2d_QualityMap & theQualityMap
) const
{
	return theQualityMap.CalcQuality(theP0, theP1, theP2);
}