#pragma once
inline
Standard_Integer AutLib::GeoLib::Geometry_Tools::Round(const Standard_Real X)
{
	return (Standard_Integer)floor(X + 0.5);
}

inline 
Standard_Real AutLib::GeoLib::Geometry_Tools::DegToRadian(const Standard_Real Degree)
{
	return Degree*M_PI / 180.0;
}

inline 
Standard_Real AutLib::GeoLib::Geometry_Tools::RadianToDegree(const Standard_Real Radian)
{
	return Radian*180.0 / M_PI;
}

inline 
void AutLib::GeoLib::Geometry_Tools::CalcMinMax
(
	const TColGeom_Ary1dOfPnt2d & Points,
	Standard_Real & Xmin,
	Standard_Real & Xmax, 
	Standard_Real & Ymin,
	Standard_Real & Ymax
)
{
	if (NOT Points.Size()) { THROW_STANDARD_EXCEPTION(" Empty List"); }

	Xmin = Xmax = Points[0].X();
	Ymin = Ymax = Points[0].Y();

	forThose
	(
		Index,
		1,
		MaxIndexOf(Points)
	)
	{
		Get_Const_Object(Point) = Points[Index];

		if (Point.X() > Xmax) Xmax = Point.X();
		if (Point.X() < Xmin) Xmin = Point.X();
		if (Point.Y() > Ymax) Ymax = Point.Y();
		if (Point.Y() < Ymin) Ymin = Point.Y();
	}
}

inline 
void AutLib::GeoLib::Geometry_Tools::TriangleInterpolate
(
	const Geom_Pnt2d & thePoint, 
	const Geom_Pnt2d & P1, 
	const Geom_Pnt2d & P2,
	const Geom_Pnt2d & P3, 
	Standard_Real & c1,
	Standard_Real & c2, 
	Standard_Real & c3
)
{
	Geom_Pnt2d V1, V2;
	Standard_Real a = 0.5*CrossProduct(P2 - P1, P3 - P1);
	a = 1.0 / a;

	V1 = P2 - thePoint;
	V2 = P3 - thePoint;

	c1 = 0.5*CrossProduct(V1, V2)*a;

	V1 = P3 - thePoint;
	V2 = P1 - thePoint;

	c2 = 0.5*CrossProduct(V1, V2)*a;

	V1 = P1 - thePoint;
	V2 = P2 - thePoint;

	c3 = 0.5*CrossProduct(V1, V2)*a;
}

inline
Geom_Pnt2d AutLib::GeoLib::Geometry_Tools::Mul
(
	const Geom_Pnt2d & Vec,
	const Entity_Metric1 & M
)
{
	return Geom_Pnt2d(Vec.X()*M.A() + Vec.Y()*M.B(), Vec.X()*M.B() + Vec.Y()*M.C());
}

inline
Geom_Pnt2d AutLib::GeoLib::Geometry_Tools::Mul
(
	const Entity_Metric1 & M,
	const Geom_Pnt2d & Vec
)
{
	return Geom_Pnt2d(Vec.X()*M.A() + Vec.Y()*M.B(), Vec.X()*M.B() + Vec.Y()*M.C());
}

inline 
Geom_Pnt3d AutLib::GeoLib::Geometry_Tools::ProjectPointonEdge
(
	const Geom_Pnt3d & thePoint,
	const Geom_Pnt3d & P1, 
	const Geom_Pnt3d & P2, 
	Standard_Real & t
)
{
	Geom_Pnt3d V = P2 - P1;

	t = DotProduct(V, thePoint - P1) / DotProduct(V, V);

	return P1 + t*V;
}

inline 
Geom_Pnt3d AutLib::GeoLib::Geometry_Tools::NormalOfTriangle
(
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2, 
	const Geom_Pnt3d & P3
)
{
	return CrossProduct(P2 - P1, P3 - P1);
}

inline
Geom_Pnt3d AutLib::GeoLib::Geometry_Tools::CentreOfTetrahedron
(
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3,
	const Geom_Pnt3d & P4
)
{
	return 0.25*(P1 + P2 + P3 + P4);
}

inline
Standard_Real AutLib::GeoLib::Geometry_Tools::AreaOfTriangle
(
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2,
	const Geom_Pnt2d & P3
)
{
	return 0.5*ABS(CrossProduct(P2 - P1, P3 - P1));
}

inline 
Standard_Real AutLib::GeoLib::Geometry_Tools::AreaOfTriangleAdapt
(
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2, 
	const Geom_Pnt2d & P3
)
{
	return 0.5*ABS(Oriented(P1, P2, P3));
}

inline 
Standard_Real AutLib::GeoLib::Geometry_Tools::AreaOfTriangle
(
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2, 
	const Geom_Pnt3d & P3
)
{
	return 0.5*ABS(CrossProduct(P2 - P1, P3 - P1).TwoNorm());
}

inline 
Standard_Real AutLib::GeoLib::Geometry_Tools::VolumeOfTetrahedron
(
	const Geom_Pnt3d & P1, 
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3, 
	const Geom_Pnt3d & P4
)
{
	Geom_Pnt3d A = P2 - P1;
	Geom_Pnt3d B = P3 - P1;
	Geom_Pnt3d C = P4 - P1;

	return DotProduct(CrossProduct(B, C), A) / (Standard_Real)6;
}

inline 
Standard_Real AutLib::GeoLib::Geometry_Tools::SignedAreaOfTriangle
(
	const Geom_Pnt2d & P1, 
	const Geom_Pnt2d & P2, 
	const Geom_Pnt2d & P3
)
{
	return 0.5*CrossProduct(P2 - P1, P3 - P1);
}

inline
Standard_Real AutLib::GeoLib::Geometry_Tools::FastOriented
(
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2,
	const Geom_Pnt2d & P3
)
{
	return CrossProduct(P2 - P1, P3 - P1);
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointRightEdge
(
	const Geom_Pnt2d & Point,
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
)
{
	return CrossProduct(P1 - Point, P2 - Point) < -EPS12;
}

inline 
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointRightEdgeAdapt
(
	const Geom_Pnt2d & Point,
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
)
{
	return Oriented(Point, P1, P2) < 0;
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointRightOnEdge
(
	const Geom_Pnt2d & Point,
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
)
{
	return CrossProduct(P1 - Point, P2 - Point) <= 0.0;
}

inline 
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointRightOnEdgeAdapt
(
	const Geom_Pnt2d & Point,
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2,
	const Standard_Real theEpsilon
)
{
	Standard_Real Orient = Oriented(Point, P1, P2);

	if (ABS(Orient) <= theEpsilon)
	{
		Standard_Real bot = GeoLib::DistanceSQ(P1, P2);
		Geom_Pnt2d V = P2 - P1;

		Standard_Real t = DotProduct(V, Point - P1) / bot;

		if (INSIDE(t, 0, 1)) return Standard_True;
		else return Standard_False;
	}
	else
	{
		return Orient < 0;
	}
}

inline 
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointLeftOnEdgeAdapt
(
	const Geom_Pnt2d & Point,
	const Geom_Pnt2d & P1, 
	const Geom_Pnt2d & P2
)
{
	Standard_Real Orient = Oriented(Point, P1, P2);

	if (Orient EQUAL 0)
	{
		Standard_Real bot = GeoLib::DistanceSQ(P1, P2);
		Geom_Pnt2d V = P2 - P1;

		Standard_Real t = DotProduct(V, Point - P1) / bot;

		if (INSIDE(t, 0, 1)) return Standard_True;
		else return Standard_False;
	}
	else
	{
		return Orient > 0;
	}
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointLeftEdge
(
	const Geom_Pnt2d & Point,
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
)
{
	return CrossProduct(P1 - Point, P2 - Point) > EPS12;  // Debug 13 April 2018
}

inline 
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointLeftEdgeAdapt
(
	const Geom_Pnt2d & Point,
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
)
{
	return Oriented(Point, P1, P2) > 0;
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointLeftOnEdge
(
	const Geom_Pnt2d & Point,
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
)
{
	return CrossProduct(P1 - Point, P2 - Point) >= 0.0;
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointRightTriangle
(
	const Geom_Pnt3d & Point,
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3
)
{
	Geom_Pnt3d Normal = NormalOfTriangle(P1, P2, P3);

	if (DotProduct((Point - P1).UnitLength(), Normal.UnitLength()) < 0)
	{
		return Standard_True;
	}
	else
	{
		return Standard_False;
	}
}

inline 
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointRightTriangle_1
(
	const Geom_Pnt3d & Point,
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3, 
	const Standard_Real Tolerance, 
	Standard_Boolean & Undefiend
)
{
	Geom_Pnt3d Normal = NormalOfTriangle(P1, P2, P3).UnitLength();

	Standard_Real Dot = DotProduct((Point - P1).UnitLength(), Normal);

	if (ABS(Dot) > Tolerance)
	{
		Undefiend = Standard_False;

		if (Dot < 0) return Standard_True;
		else return Standard_False;
	}

	if (IsPointOnTriangle(Point, P1, P2, P3, Tolerance))
	{
		Undefiend = Standard_False;

		return Standard_False;
	}

	Undefiend = Standard_True;
	return Standard_False;
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointRightOnTriangle
(
	const Geom_Pnt3d & Point,
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3
)
{
	Geom_Pnt3d Normal = NormalOfTriangle(P1, P2, P3);

	if (DotProduct(Point - P1, Normal) <= 0.0)
	{
		return Standard_True;
	}
	else
	{
		return Standard_False;
	}
}

inline Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointLeftTriangle
(
	const Geom_Pnt3d & Point,
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3
)
{
	Geom_Pnt3d Normal = NormalOfTriangle(P1, P2, P3);

	if (DotProduct(Point - P1, Normal) > 0.0)
	{
		return Standard_True;
	}
	else
	{
		return Standard_False;
	}
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointLeftOnTriangle
(
	const Geom_Pnt3d & Point,
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3
)
{
	Geom_Pnt3d Normal = NormalOfTriangle(P1, P2, P3);

	if (DotProduct(Point - P1, Normal) >= 0.0)
	{
		return Standard_True;
	}
	else
	{
		return Standard_False;
	}
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointInsideOnTriangle
(
	const Geom_Pnt2d & Point,
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2,
	const Geom_Pnt2d & P3
)
{
	if (IsPointRightEdge(Point, P1, P2))
	{
		return Standard_False;
	}
	else if (IsPointRightEdge(Point, P2, P3))
	{
		return Standard_False;
	}
	else if (IsPointRightEdge(Point, P3, P1))
	{
		return Standard_False;
	}

	return Standard_True;
}

inline 
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointInsideOnTriangleAdapt
(
	const Geom_Pnt2d & Point, 
	const Geom_Pnt2d & P1, 
	const Geom_Pnt2d & P2,
	const Geom_Pnt2d & P3,
	const Standard_Real theEpsilon
)
{
	if (IsPointRightOnEdgeAdapt(Point, P1, P2, theEpsilon))
	{
		return Standard_False;
	}
	else if (IsPointRightOnEdgeAdapt(Point, P2, P3, theEpsilon))
	{
		return Standard_False;
	}
	else if (IsPointRightOnEdgeAdapt(Point, P3, P1, theEpsilon))
	{
		return Standard_False;
	}

	return Standard_True;
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointInsideOnTriangleCW
(
	const Geom_Pnt2d & Point,
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2,
	const Geom_Pnt2d & P3
)
{
	if (IsPointLeftEdge(Point, P1, P2))
	{
		return Standard_False;
	}
	else if (IsPointLeftEdge(Point, P2, P3))
	{
		return Standard_False;
	}
	else if (IsPointLeftEdge(Point, P3, P1))
	{
		return Standard_False;
	}

	return Standard_True;
}

inline 
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointInsideOnTriangleCWAdapt
(
	const Geom_Pnt2d & Point,
	const Geom_Pnt2d & P1, 
	const Geom_Pnt2d & P2, 
	const Geom_Pnt2d & P3
)
{
	if (IsPointLeftEdgeAdapt(Point, P1, P2))
	{
		return Standard_False;
	}
	else if (IsPointLeftEdgeAdapt(Point, P2, P3))
	{
		return Standard_False;
	}
	else if (IsPointLeftEdgeAdapt(Point, P3, P1))
	{
		return Standard_False;
	}

	return Standard_True;
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointInsideOnTetrahedron
(
	const Geom_Pnt3d & Point,
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3,
	const Geom_Pnt3d & P4
)
{
	if (IsPointRightTriangle(Point, P1, P2, P3))
	{
		return Standard_False;
	}
	else
		if (IsPointRightTriangle(Point, P4, P2, P1))
		{
			return Standard_False;
		}
		else
			if (IsPointRightTriangle(Point, P4, P3, P2))
			{
				return Standard_False;
			}
			else
				if (IsPointRightTriangle(Point, P4, P1, P3))
				{
					return Standard_False;
				}

	return Standard_True;
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointInsideOnInterval
(
	const Standard_Real Point,
	const Standard_Real x0,
	const Standard_Real x1
)
{
	if (Point < x0)
		return Standard_False;
	else if (Point > x1)
		return Standard_False;

	return Standard_True;
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointInsideOnBox
(
	const Geom_Pnt2d & Point,
	const Standard_Real x0,
	const Standard_Real x1,
	const Standard_Real y0,
	const Standard_Real y1
)
{
	if (NOT IsPointInsideOnInterval(Point.X(), x0, x1))
	{
		return Standard_False;
	}
	else if (NOT IsPointInsideOnInterval(Point.Y(), y0, y1))
	{
		return Standard_False;
	}

	return Standard_True;
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointInsideOnBox
(
	const Geom_Pnt3d & Point,
	const Standard_Real x0,
	const Standard_Real x1,
	const Standard_Real y0,
	const Standard_Real y1,
	const Standard_Real z0,
	const Standard_Real z1
)
{
	if (!IsPointInsideOnInterval(Point.X(), x0, x1))
	{
		return Standard_False;
	}
	else if (!IsPointInsideOnInterval(Point.Y(), y0, y1))
	{
		return Standard_False;
	}
	else if (!IsPointInsideOnInterval(Point.Z(), z0, z1))
	{
		return Standard_False;
	}

	return Standard_True;
}

inline 
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPointOnTriangle
(
	const Geom_Pnt3d & thePoint,
	const Geom_Pnt3d & P1, 
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3, 
	const Standard_Real Tolerance
)
{
	Geom_Pnt3d V1 = P2 - P1;
	Geom_Pnt3d V2 = P3 - P1;
	Geom_Pnt3d Vp = thePoint - P1;

	mat33 R = CalcRotationMatrix(V1.UnitLength(), V2.UnitLength());

	R = inv(R);

	vec3 Q1, Q2, Qp;

	Q1(0) = V1.X();
	Q1(1) = V1.Y();
	Q1(2) = V1.Z();

	Q2(0) = V2.X();
	Q2(1) = V2.Y();
	Q2(2) = V2.Z();

	Qp(0) = Vp.X();
	Qp(1) = Vp.Y();
	Qp(2) = Vp.Z();

	Q1 = R*Q1;
	Q2 = R*Q2;
	Qp = R*Qp;

	if (ABS(Qp(2)) > Tolerance) { return Standard_False; }

	Geom_Pnt2d q1(Q1(0), Q1(1));
	Geom_Pnt2d q2(Q2(0), Q2(1));
	Geom_Pnt2d qp(Qp(0), Qp(1));

	if (CrossProduct(q1, q2) > 0)
	{
		return IsPointInsideOnTriangle(qp, Geom_Pnt2d(), q1, q2);
	}
	else
	{
		return IsPointInsideOnTriangle(qp, Geom_Pnt2d(), q2, q1);
	}
	
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsOneCommonPointTwoLineSegment
(
	const Standard_Integer v1,
	const Standard_Integer v2,
	const Standard_Integer q1,
	const Standard_Integer q2
)
{
	if (v1 == q1)
	{
		return Standard_True;
	}
	else if (v1 == q2)
	{
		return Standard_True;
	}
	else if (v2 == q1)
	{
		return Standard_True;
	}
	else if (v2 == q2)
	{
		return Standard_True;
	}

	return Standard_False;
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPairedTwoLineSegment
(
	const Standard_Integer v1,
	const Standard_Integer v2,
	const Standard_Integer q1,
	const Standard_Integer q2
)
{
	if (v1 == q1)
	{
		if (v2 == q2)
			return Standard_True;
		else
			return Standard_False;
	}
	else if (v2 == q1)
	{
		if (v1 == q2)
			return Standard_True;
		else
			return Standard_False;
	}

	return Standard_False;
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsOneCommonPointLineSegmentTriangle
(
	const Standard_Integer v1,
	const Standard_Integer v2,
	const Standard_Integer q1,
	const Standard_Integer q2,
	const Standard_Integer q3
)
{
	if (v1 == q1)
		return Standard_True;
	else
		if (v1 == q2)
			return Standard_True;
		else
			if (v1 == q3)
				return Standard_True;
			else
				if (v2 == q1)
					return Standard_True;
				else
					if (v2 == q2)
						return Standard_True;
					else
						if (v2 == q3)
							return Standard_True;
						else
							return Standard_False;
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsOneCommonTwoTriangle
(
	const Standard_Integer v1,
	const Standard_Integer v2,
	const Standard_Integer v3,
	const Standard_Integer q1,
	const Standard_Integer q2,
	const Standard_Integer q3
)
{
	if (v1 == q1)
		return Standard_True;
	else
		if (v1 == q2)
			return Standard_True;
		else
			if (v1 == q3)
				return Standard_True;
			else
				if (v2 == q1)
					return Standard_True;
				else
					if (v2 == q2)
						return Standard_True;
					else
						if (v2 == q3)
							return Standard_True;
						else
							if (v3 == q1)
								return Standard_True;
							else
								if (v3 == q2)
									return Standard_True;
								else
									if (v3 == q3)
										return Standard_True;
									else
										return Standard_False;
}

inline 
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsThreeCommonTwoTriangle
(
	const Standard_Integer v1,
	const Standard_Integer v2, 
	const Standard_Integer v3, 
	const Standard_Integer q1, 
	const Standard_Integer q2, 
	const Standard_Integer q3
)
{
	if (v1 EQUAL q1)
	{
		if (v2 EQUAL q2)
		{
			if (v3 EQUAL q3) return Standard_True;
		}
		else if (v2 EQUAL q3)
		{
			if (v3 EQUAL q2) return Standard_True;
		}
	}
	else if (v1 EQUAL q2)
	{
		if (v2 EQUAL q1)
		{
			if (v3 EQUAL q3) return Standard_True;
		}
		else if (v2 EQUAL q3)
		{
			if (v3 EQUAL q1) return Standard_True;
		}
	}
	else if (v1 EQUAL q3)
	{
		if (v2 EQUAL q1)
		{
			if (v3 EQUAL q2) return Standard_True;
		}
		else if (v2 EQUAL q2)
		{
			if (v3 EQUAL q1) return Standard_True;
		}
	}

	return Standard_False;
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsPairedTwoTriangle
(
	const Standard_Integer v1,
	const Standard_Integer v2,
	const Standard_Integer v3,
	const Standard_Integer q1,
	const Standard_Integer q2,
	const Standard_Integer q3
)
{
	if (v1 == q1)
	{
		if (IsPairedTwoLineSegment(v2, v3, q2, q3))
			return Standard_True;
		else
			return Standard_False;
	}
	else if (v2 == q1)
	{
		if (IsPairedTwoLineSegment(v1, v3, q2, q3))
			return Standard_True;
		else
			return Standard_False;
	}
	else if (v3 == q1)
	{
		if (IsPairedTwoLineSegment(v1, v2, q2, q3))
			return Standard_True;
		else
			return Standard_False;
	}
	else
		return Standard_False;
}

inline 
mat33 AutLib::GeoLib::Geometry_Tools::CalcRotationMatrix
(
	const Geom_Pnt3d & Vec1,
	const Geom_Pnt3d & Vec2
)
{
	Geom_Pnt3d V3 = CrossProduct(Vec1, Vec2).UnitLength();
	Geom_Pnt3d V2 = CrossProduct(V3, Vec1).UnitLength();

	Geom_Pnt3d E1(1, 0, 0);
	Geom_Pnt3d E2(0, 1, 0);
	Geom_Pnt3d E3(0, 0, 1);

	mat33 R;

	R(0, 0) = DotProduct(E1, Vec1);
	R(0, 1) = DotProduct(E1, V2);
	R(0, 2) = DotProduct(E1, V3);
	R(1, 0) = DotProduct(E2, Vec1);
	R(1, 1) = DotProduct(E2, V2);
	R(1, 2) = DotProduct(E2, V3);
	R(2, 0) = DotProduct(E3, Vec1);
	R(2, 1) = DotProduct(E3, V2);
	R(2, 2) = DotProduct(E3, V3);

	MOVE(R);
}

template<typename T>
inline M_AUT ADT_Ary1d<T> AutLib::GeoLib::Geometry_Tools::RemoveMults(const ADT_Ary1d<T>& Objects)
{
	ADT_AvlTree<T> Tree;
	
	Set_Numbering(Tree, IsLess);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Objects)
	)
	{
		Try_Exception_Handle_Exit(Tree.InsertIgnoreDup(Objects[Index]));
	}

	return Tree.Retrieve();
}