#pragma once
inline
Standard_Real AutLib::GeoLib::Geometry_Distance::InfNorm
(
	const Standard_Real X0,
	const Standard_Real Y0,
	const Standard_Real X1,
	const Standard_Real Y1
)
{
	return MAX(ABS(X1 - X0), ABS(Y1 - Y0));
}

inline
Standard_Real AutLib::GeoLib::Geometry_Distance::TwoNorm
(
	const Standard_Real X0,
	const Standard_Real Y0,
	const Standard_Real X1,
	const Standard_Real Y1
)
{
	Standard_Real Dx = X1 - X0;
	Standard_Real Dy = Y1 - Y0;

	return sqrt(Dx*Dx + Dy*Dy);
}

inline Standard_Real AutLib::GeoLib::Geometry_Distance::InfNorm
(
	const Standard_Real X0,
	const Standard_Real Y0,
	const Standard_Real Z0,
	const Standard_Real X1,
	const Standard_Real Y1,
	const Standard_Real Z1
)
{
	return MAX(MAX(ABS(X1 - X0), ABS(Y1 - Y0)), ABS(Z1 - Z0));
}

inline
Standard_Real AutLib::GeoLib::Geometry_Distance::TwoNorm
(
	const Standard_Real X0,
	const Standard_Real Y0,
	const Standard_Real Z0,
	const Standard_Real X1,
	const Standard_Real Y1,
	const Standard_Real Z1
)
{
	Standard_Real Dx = X1 - X0;
	Standard_Real Dy = Y1 - Y0;
	Standard_Real Dz = Z1 - Z0;

	return sqrt(Dx*Dx + Dy*Dy + Dz*Dz);
}

inline
Standard_Real AutLib::GeoLib::Geometry_Distance::Distance
(
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2,
	const Entity_Metric1 & Metric
)
{
	return sqrt(DistanceSQ(P1, P2, Metric));
}

inline
Standard_Real AutLib::GeoLib::Geometry_Distance::DistanceSQ
(
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2,
	const Entity_Metric1 & M
)
{
	Standard_Real Dx = P2.X() - P1.X();
	Standard_Real Dy = P2.Y() - P1.Y();

	return M.A()*Dx*Dx + 2.0*M.B()*Dx*Dy + M.C()*Dy*Dy;
}

inline
Standard_Real AutLib::GeoLib::Geometry_Distance::DistanceFromLineSegment
(
	const Geom_Pnt2d & thePoint,
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
)
{
	return sqrt(Geometry_Distance::DistanceFromLineSegmentSQ(thePoint, P1, P2));
}

inline 
Standard_Real AutLib::GeoLib::Geometry_Distance::DistanceFromLineSegment
(
	const Geom_Pnt3d & thePoint, 
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2
)
{
	return sqrt(Geometry_Distance::DistanceFromLineSegmentSQ(thePoint, P1, P2));
}

inline
Standard_Real AutLib::GeoLib::Geometry_Distance::DistanceFromLineSegmentSQ
(
	const Geom_Pnt2d & thePoint,
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
)
{
	Standard_Real bot = GeoLib::DistanceSQ(P1, P2);

	Geom_Pnt2d Pn;

	if (bot == 0.0)
		Pn = P1;
	else
	{
		Geom_Pnt2d V = P2 - P1;

		Standard_Real t = DotProduct(V, thePoint - P1) / bot;

		if (t < 0.0) t = 0.0;
		if (t > 1.0) t = 1.0;

		Pn = P1 + t*V;
	}

	return GeoLib::DistanceSQ(thePoint, Pn);
}

inline 
Standard_Real AutLib::GeoLib::Geometry_Distance::DistanceFromLineSegmentSQ
(
	const Geom_Pnt3d & thePoint,
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2
)
{
	Standard_Real bot = GeoLib::DistanceSQ(P1, P2);

	Geom_Pnt3d Pn;

	if (bot == 0.0)
		Pn = P1;
	else
	{
		Geom_Pnt3d V = P2 - P1;

		Standard_Real t = DotProduct(V, thePoint - P1) / bot;

		if (t < 0.0) t = 0.0;
		if (t > 1.0) t = 1.0;

		Pn = P1 + t*V;
	}

	return GeoLib::DistanceSQ(thePoint, Pn);
}

inline 
Standard_Real AutLib::GeoLib::Geometry_Distance::DistancePointFromTriangle
(
	const Geom_Pnt3d & thePoint,
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2, 
	const Geom_Pnt3d & P3
)
{
	return sqrt(Geometry_Distance::DistancePointFromTriangleSQ(thePoint, P1, P2, P3));
}

inline
Standard_Real AutLib::GeoLib::Geometry_Distance::DistancePointFromProjectedEdgesOfTriangle
(
	const Geom_Pnt3d & thePoint, 
	const Geom_Pnt3d & P1, 
	const Geom_Pnt3d & P2, 
	const Geom_Pnt3d & P3
)
{
	return sqrt(Geometry_Distance::DistancePointFromProjectedEdgesOfTriangleSQ(thePoint, P1, P2, P3));
}

inline
Standard_Real AutLib::GeoLib::Geometry_Distance::DistanceLineSegmentFromLineSegment
(
	const Geom_Pnt3d & P0, 
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & Q0,
	const Geom_Pnt3d & Q1
)
{
	return sqrt(Geometry_Distance::DistanceLineSegmentFromLineSegmentSQ(P0, P1, Q0, Q1));
}