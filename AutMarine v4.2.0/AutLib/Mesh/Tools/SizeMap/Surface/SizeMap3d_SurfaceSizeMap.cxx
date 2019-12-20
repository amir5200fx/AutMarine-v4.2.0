#include <SizeMap3d_SurfaceSizeMap.hxx>

AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::SizeMap3d_SurfaceSizeMap
(
	const Mesh3d_SizeMap & SizeMap,
	const Handle(Geom_Surface)& Surface
)
	: theSizeMap_(SizeMap)
	, theSurface_(Surface)
{
}

Standard_Real AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::Oriented(const Geom_Pnt2d & P0, const Geom_Pnt2d & P1, const Geom_Pnt2d & P2) const
{
	CloseProgram(" This is a virtual function of Mesh3d_SurfaceSizeMap: Oriented()");

	return 0;
}

Standard_Real AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::CalcUnitDistance(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2) const
{
	CloseProgram(" This is a virtual function of Mesh3d_SurfaceSizeMap: CalcUnitDistance()");

	return 0;
}

Standard_Real AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::CalcDistance(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2) const
{
	CloseProgram(" This is a virtual function of Mesh3d_SurfaceSizeMap: CalcDistance()");

	return 0;
}

Standard_Real AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::CalcDistanceSQ(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2) const
{
	CloseProgram(" This is a virtual function of Mesh3d_SurfaceSizeMap: CalcDistanceSQ()");

	return 0;
}

Standard_Real AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::CalcDistancePointFromLSeg(const Geom_Pnt2d & thePoint, const Geom_Pnt2d & P1, const Geom_Pnt2d & P2) const
{
	CloseProgram(" This is a virtual function of Mesh3d_SurfaceSizeMap: CalcDistancePointFromLSeg()");

	return 0;
}

Standard_Real AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::CalcDistancePointFromLSegSQ(const Geom_Pnt2d & thePoint, const Geom_Pnt2d & P1, const Geom_Pnt2d & P2) const
{
	CloseProgram(" This is a virtual function of Mesh3d_SurfaceSizeMap: CalcDistancePointFromLSegSQ()");

	return 0;
}

Geom_Pnt2d AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::CalcOptimumPoint(const Standard_Real Size, const Mesh2d_Edge & Edge) const
{
	CloseProgram(" This is a virtual function of Mesh3d_SurfaceSizeMap: CalcOptimumPoint()");

	return Geom_Pnt2d();
}

Geom_Pnt2d AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::CalcCentreOf(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2) const
{
	CloseProgram(" This is a virtual function of Mesh3d_SurfaceSizeMap: CalcCentreOf()");

	return Geom_Pnt2d();
}

M_GEO Entity_Box2d AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::CalcSearchRegion(const Standard_Real Radius, const Geom_Pnt2d & Centre) const
{
	CloseProgram(" This is a virtual function of Mesh3d_SurfaceSizeMap: CalcSearchRegion()");

	return M_GEO Entity_Box2d();
}

M_GEO Entity_Box2d AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::CalcSearchRegion(const Standard_Real Radius, const Geom_Pnt2d & Centre, const Mesh2d_Edge & Edge) const
{
	CloseProgram(" This is a virtual function of Mesh3d_SurfaceSizeMap: CalcSearchRegion()");

	return M_GEO Entity_Box2d();
}

Standard_Real AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::Integrand(const Geom_Pnt2d & Point, const Geom_Pnt2d & Vector) const
{
	CloseProgram(" This is a virtual function of Mesh3d_SurfaceSizeMap: Integrand()");

	return 0;
}

Standard_Real AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::MetricIntegrand(const Geom_Pnt2d & Point, const Geom_Pnt2d & Vector) const
{
	CloseProgram(" This is a virtual function of Mesh3d_SurfaceSizeMap: MetricIntegrand()");

	return 0;
}

Standard_Real AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::ElementQuality(const Geom_Pnt2d & theP0, const Geom_Pnt2d & theP1, const Geom_Pnt2d & theP2, const Mesh2d_QualityMap & theQualityMap) const
{
	CloseProgram(" This is a virtual function of Mesh3d_SurfaceSizeMap: ElementQuality()");

	return 0;
}

void AutLib::MeshLib::SizeMap3d_SurfaceSizeMap::ExportSearchingAreaToPlt(const Standard_Real Size, const Geom_Pnt2d & Point, fstream & File) const
{
	cout << " Empty ExportSearchingAreaToPlt" << endl;
}