#pragma once
#include <Geometry_Distance.hxx>
#include <Geometry_Tools.hxx>

inline
Standard_Real AutLib::MeshLib::SizeMap3d_UniSize::BaseSize() const
{
	return theSize_;
}

inline
Standard_Real AutLib::MeshLib::SizeMap3d_UniSize::ElementSize(const Mesh3d_Facet & Facet) const
{
	return theSize_;
}

inline
Standard_Real AutLib::MeshLib::SizeMap3d_UniSize::ElementSize(const Geom_Pnt3d & Coord) const
{
	return theSize_;
}

inline
Standard_Real AutLib::MeshLib::SizeMap3d_UniSize::CalcUnitDistance
(
	const Geom_Pnt3d & Coord1,
	const Geom_Pnt3d & Coord2
) const
{
	return Coord1.Distance(Coord2) * theInvSize_;
}

inline
Standard_Real AutLib::MeshLib::SizeMap3d_UniSize::CalcDistance
(
	const Geom_Pnt3d & Coord1,
	const Geom_Pnt3d & Coord2
) const
{
	return Coord1.Distance(Coord2);
}

inline
Standard_Real AutLib::MeshLib::SizeMap3d_UniSize::CalcDistanceSQ
(
	const Geom_Pnt3d & Coord1,
	const Geom_Pnt3d & Coord2
) const
{
	return Coord1.SquareDistance(Coord2);
}

inline
Standard_Real AutLib::MeshLib::SizeMap3d_UniSize::CalcDistanceFromTriangle
(
	const Geom_Pnt3d & thePoint,
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3
) const
{
	return M_GEO Geometry_Distance::DistancePointFromTriangle(thePoint, P1, P2, P3);
}

inline
Standard_Real AutLib::MeshLib::SizeMap3d_UniSize::CalcDistanceFromTriangleSQ
(
	const Geom_Pnt3d & thePoint,
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3
) const
{
	return M_GEO Geometry_Distance::DistancePointFromTriangleSQ(thePoint, P1, P2, P3);
}

inline
Standard_Real AutLib::MeshLib::SizeMap3d_UniSize::CalcDistanceFromProjectedEdgesOfTriangle
(
	const Geom_Pnt3d & thePoint,
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3
) const
{
	return M_GEO Geometry_Distance::DistancePointFromProjectedEdgesOfTriangle(thePoint, P1, P2, P3);
}

inline
Standard_Real AutLib::MeshLib::SizeMap3d_UniSize::CalcDistanceFromProjectedEdgesOfTriangleSQ
(
	const Geom_Pnt3d & thePoint,
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3
) const
{
	return M_GEO Geometry_Distance::DistancePointFromProjectedEdgesOfTriangleSQ(thePoint, P1, P2, P3);
}

inline
Standard_Real AutLib::MeshLib::SizeMap3d_UniSize::CalcDistanceEdgeFromEdge
(
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & Q1,
	const Geom_Pnt3d & Q2
) const
{
	return M_GEO Geometry_Distance::DistanceLineSegmentFromLineSegment(P1, P2, Q1, Q2);
}

inline
Standard_Real AutLib::MeshLib::SizeMap3d_UniSize::CalcDistanceEdgeFromEdgeSQ
(
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & Q1,
	const Geom_Pnt3d & Q2
) const
{
	return M_GEO Geometry_Distance::DistanceLineSegmentFromLineSegmentSQ(P1, P2, Q1, Q2);
}

inline
Standard_Real AutLib::MeshLib::SizeMap3d_UniSize::CalcArea
(
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3
) const
{
	return M_GEO Geometry_Tools::AreaOfTriangle(P1, P2, P3);
}

inline
Geom_Pnt3d AutLib::MeshLib::SizeMap3d_UniSize::CalcOptimumCoord
(
	const Standard_Real Size,
	const Mesh3d_Facet & Facet
) const
{
	return Facet.Centre() + Size*Facet.Normal();
}

inline
M_GEO Entity_Box3d AutLib::MeshLib::SizeMap3d_UniSize::CalcSearchingRegion
(
	const Standard_Real Radius,
	const Geom_Pnt3d & theCentre
) const
{
	return M_GEO Entity_Box3d
	(
		theCentre.X() - Radius,
		theCentre.X() + Radius,
		theCentre.Y() - Radius,
		theCentre.Y() + Radius,
		theCentre.Z() - Radius,
		theCentre.Z() + Radius
	);
}

inline
Standard_Real AutLib::MeshLib::SizeMap3d_UniSize::Integrand
(
	const Geom_Pnt3d & Point,
	const Geom_Pnt3d & Vector
) const
{
	return theInvSize_*sqrt(M_GEO DotProduct(Vector, Vector));
}

inline
Standard_Real AutLib::MeshLib::SizeMap3d_UniSize::MetricIntegrand
(
	const Geom_Pnt3d & /*Point*/,
	const Geom_Pnt3d & Vector
) const
{
	return sqrt(M_GEO DotProduct(Vector, Vector));
}