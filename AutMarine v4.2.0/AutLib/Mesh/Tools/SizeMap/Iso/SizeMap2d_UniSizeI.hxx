#pragma once
#include <Geometry_Tools.hxx>

inline
Standard_Real AutLib::MeshLib::SizeMap2d_UniSize::BaseSize() const
{
	return theSize_;
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_UniSize::ElementSize(const Geom_Pnt2d & Coord) const
{
	return theSize_;
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_UniSize::ElementSize(const Mesh2d_Edge & Edge) const
{
	return theSize_;
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_UniSize::Oriented
(
	const Geom_Pnt2d & P0, 
	const Geom_Pnt2d & P1, 
	const Geom_Pnt2d & P2
) const
{
	return M_GEO Geometry_Tools::Oriented(P0, P1, P2);
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_UniSize::CalcUnitDistance
(
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
) const
{
	return M_GEO Distance(P1, P2)*theInvSize_;
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_UniSize::CalcDistance
(
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
) const
{
	return M_GEO Distance(P1, P2);
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_UniSize::CalcDistanceSQ
(
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
) const
{
	return M_GEO DistanceSQ(P1, P2);
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_UniSize::CalcDistancePointFromLSeg
(
	const Geom_Pnt2d & thePoint, 
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
) const
{
	return M_GEO Geometry_Distance::DistanceFromLineSegment(thePoint, P1, P2);
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_UniSize::CalcDistancePointFromLSegSQ
(
	const Geom_Pnt2d & thePoint,
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
) const
{
	return M_GEO Geometry_Distance::DistanceFromLineSegmentSQ(thePoint, P1, P2);
}

inline 
Geom_Pnt2d AutLib::MeshLib::SizeMap2d_UniSize::CalcOptimumPoint
(
	const Standard_Real Size,
	const Mesh2d_Edge & Edge
) const
{
	Get_Const_Object(Middle) = Edge.Centre();

	Geom_Pnt2d Vector = (Edge.Node(1)->Coord() - Middle).UnitLength();

	Vector.Rotate90ccw();

	return Middle + Size*Vector;
}

inline 
Geom_Pnt2d AutLib::MeshLib::SizeMap2d_UniSize::CalcCentreOf(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2) const
{
	return MEAN(P1, P2);
}

inline 
M_GEO Entity_Box2d AutLib::MeshLib::SizeMap2d_UniSize::CalcSearchRegion(const Standard_Real Radius, const Geom_Pnt2d & Centre) const
{
	return M_GEO Entity_Box2d
	(
		Centre.X() - Radius,
		Centre.X() + Radius,
		Centre.Y() - Radius,
		Centre.Y() + Radius
	);
}

inline 
M_GEO Entity_Box2d AutLib::MeshLib::SizeMap2d_UniSize::CalcSearchRegion(const Standard_Real Radius, const Geom_Pnt2d& Centre, const Mesh2d_Edge & /*Edge*/) const
{
	return M_GEO Entity_Box2d
	(
		Centre.X() - Radius,
		Centre.X() + Radius,
		Centre.Y() - Radius,
		Centre.Y() + Radius
	);
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_UniSize::Integrand(const Geom_Pnt2d & Point, const Geom_Pnt2d & Vector) const
{
	return theInvSize_*sqrt(M_GEO DotProduct(Vector, Vector));
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_UniSize::MetricIntegrand(const Geom_Pnt2d & Point, const Geom_Pnt2d & Vector) const
{
	return sqrt(M_GEO DotProduct(Vector, Vector));
}