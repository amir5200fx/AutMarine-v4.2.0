#include <Mesh2d_MetricMap.hxx>

AutLib::MeshLib::Mesh2d_MetricMap::Mesh2d_MetricMap()
{
}

void AutLib::MeshLib::Mesh2d_MetricMap::SetBoundingBox(const M_GEO Entity_Box2d & theBox)
{
	theBoundingBox_ = theBox;
}