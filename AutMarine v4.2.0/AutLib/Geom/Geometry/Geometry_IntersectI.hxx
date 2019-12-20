#pragma once
#include <MollerAlg.h>

inline
Geom_Pnt2d AutLib::GeoLib::Geometry_Intersect::IntersectionTwoLines(const Geom_Pnt2d & P0, const Geom_Pnt2d & Vec0, const Geom_Pnt2d & P1, const Geom_Pnt2d & Vec1)
{
	if (areParallel(Vec0, Vec1, 1.0E-12))
	{
		THROW_STANDARD_EXCEPTION(" Two Vectors are parallel");
	}

	Geom_Pnt2d vcr = P1 - P0;

	Standard_Real denom = CrossProduct
	(
		Vec0,
		Vec1
	);

	Standard_Real nume = CrossProduct
	(
		vcr,
		Vec1
	);

	Standard_Real alf = nume / denom;

	Geom_Pnt2d IntPoint = P0 + alf*Vec0;

	MOVE(IntPoint);
}

inline
Geom_Pnt2d AutLib::GeoLib::Geometry_Intersect::IntersectionTwoLines
(
	const Geom_Pnt2d & P0,
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & Q0,
	const Geom_Pnt2d & Q1,
	Standard_Real & t1,
	Standard_Real & t2
)
{
	Geom_Pnt2d p2p0 = Q0 - P0;

	Standard_Real nume = CrossProduct
	(
		p2p0,
		Q1 - Q0
	);

	Standard_Real denom = CrossProduct
	(
		P1 - P0,
		Q1 - Q0
	);

	t1 = nume / denom;

	nume = CrossProduct
	(
		p2p0,
		P1 - P0
	);

	t2 = nume / denom;

	return P0 + t1*(P1 - P0);
}

inline 
Standard_Boolean AutLib::GeoLib::Geometry_Intersect::IsIntersectLineSegmentTriangle
(
	const Geom_Pnt3d & theQ0,
	const Geom_Pnt3d & theQ1,
	const Geom_Pnt3d & theP0,
	const Geom_Pnt3d & theP1, 
	const Geom_Pnt3d & theP2
)
{
	Standard_Real orig[3], dir[3], p0[3], p1[3], p2[3];

	p0[0] = theP0.X();
	p0[1] = theP0.Y();
	p0[2] = theP0.Z();

	p1[0] = theP1.X();
	p1[1] = theP1.Y();
	p1[2] = theP1.Z();

	p2[0] = theP2.X();
	p2[1] = theP2.Y();
	p2[2] = theP2.Z();

	orig[0] = theQ0.X();
	orig[1] = theQ0.Y();
	orig[2] = theQ0.Z();

	dir[0] = theQ1.X() - theQ0.X();
	dir[1] = theQ1.Y() - theQ0.Y();
	dir[2] = theQ1.Z() - theQ0.Z();

	Standard_Real t, u, v;

	if (!Moller::intersect_triangle(orig, dir, p0, p1, p2, &t, &u, &v))
	{
		return Standard_False;
	}
	else
	{
		if (t > 0 && t < 1)
			return Standard_True;
		else
			return Standard_False;
	}
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Intersect::IsIntersect
(
	const Standard_Real U0,
	const Standard_Real U1,
	const Standard_Real V0,
	const Standard_Real V1
)
{
	if (U1 < V0)
		return Standard_False;
	else if (V1 < U0)
		return Standard_False;
	else
		return Standard_True;
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Intersect::IsIntersect
(
	const Entity_Box2d & b1,
	const Entity_Box2d & b2
)
{
	if (NOT IsIntersect(b1.Xmin(), b1.Xmax(), b2.Xmin(), b2.Xmax()))
		return Standard_False;
	else if (NOT IsIntersect(b1.Ymin(), b1.Ymax(), b2.Ymin(), b2.Ymax()))
		return Standard_False;
	else
		return Standard_True;
}

inline 
Standard_Boolean AutLib::GeoLib::Geometry_Intersect::IsIntersect
(
	const Entity_Box3d & b1,
	const Entity_Box3d & b2
)
{
	if (NOT IsIntersect(b1.Xmin(), b1.Xmax(), b2.Xmin(), b2.Xmax()))
		return Standard_False;
	else if (NOT IsIntersect(b1.Ymin(), b1.Ymax(), b2.Ymin(), b2.Ymax()))
		return Standard_False;
	else if (NOT IsIntersect(b1.Zmin(), b1.Zmax(), b2.Zmin(), b2.Zmax()))
		return Standard_False;
	else
		return Standard_True;
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Intersect::IsIntersect
(
	const Geom_Pnt2d & P0,
	const Geom_Pnt2d & t0,
	const Geom_Pnt2d & P2,
	const Geom_Pnt2d & t2,
	Standard_Real & s0,
	Standard_Real & s2,
	Geom_Pnt2d & Point
)
{
	if (areParallel(t0, t2, 1.0E-12))
		return Standard_False;
	else
	{
		Geom_Pnt2d vcr = P2 - P0;

		Standard_Real nume = CrossProduct
		(
			vcr,
			t0
		);

		Standard_Real denom = CrossProduct
		(
			t0,
			t2
		);

		s2 = nume / denom;

		nume = CrossProduct
		(
			vcr,
			t2
		);

		s0 = nume / denom;

		Point = P0 + s0 * t0;

		return Standard_True;
	}
}

inline 
Standard_Boolean AutLib::GeoLib::Geometry_Intersect::IsIntersect
(
	const Geom_Pnt2d & P0,
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & Q0, 
	const Geom_Pnt2d & Q1,
	Geom_Pnt2d & Point
)
{
	Standard_Real dum1, dum2;

	return 
		IsIntersect
		(
			P0, 
			(P1 - P0).UnitLength(),
			Q0,
			(Q1 - Q0).UnitLength(),
			dum1,
			dum2,
			Point
		);
}

inline
Standard_Boolean AutLib::GeoLib::Geometry_Intersect::IsIntersect
(
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2,
	const Geom_Pnt2d & Q1,
	const Geom_Pnt2d & Q2
)
{
	Geom_Pnt2d DP = P2 - P1;
	Geom_Pnt2d DQ = Q1 - Q2;

	Standard_Real Delta = CrossProduct
	(
		DP,
		DQ
	);

	if (ABS(Delta) <= 1.0E-12) { return Standard_False; }
	else
	{
		Geom_Pnt2d DQP = Q1 - P1;

		Standard_Real InvDelta = ONE / Delta;

		Standard_Real s = InvDelta*CrossProduct
		(
			DQP,
			DQ
		);

		if (NOT INSIDE(s, 0.0, 1.0)) return Standard_False;

		Standard_Real t = InvDelta*CrossProduct
		(
			DP,
			DQP
		);

		if (NOT INSIDE(t, 0.0, 1.0)) return Standard_False;
	}

	return Standard_True;
}

//inline
//Standard_Boolean AutLib::GeoLib::Geometry_Intersect::IsIntersect
//(
//	const Geom_Pnt2d & P1,
//	const Geom_Pnt2d & P2,
//	const Geom_Pnt2d & Q1,
//	const Geom_Pnt2d & Q2
//)
//{
//	Geom_Pnt2d A = P2 - P1;
//	Geom_Pnt2d B = Q1 - Q2;
//	Geom_Pnt2d C = P1 - Q1;
//	
//	Standard_Real alphaNumerator = B.Y()*C.X() - B.X()*C.Y();
//	Standard_Real alphaDenominator = A.Y()*B.X() - A.X()*B.Y();
//	Standard_Real betaNumerator = A.X()*C.Y() - A.Y()*C.X();
//	Standard_Real betaDenominator = alphaDenominator;
//	
//	Standard_Boolean doIntersect = Standard_True;
//
//	if (alphaDenominator == 0 || betaDenominator == 0) {
//		doIntersect = Standard_False;
//	}
//	else {
//
//		if (alphaDenominator > 0) {
//			if (alphaNumerator < 0 || alphaNumerator > alphaDenominator) {
//				doIntersect = Standard_False;
//			}
//		}
//		else if (alphaNumerator > 0 || alphaNumerator < alphaDenominator) {
//			doIntersect = Standard_False;
//		}
//
//		if (doIntersect && betaDenominator > 0) {
//			if (betaNumerator < 0 || betaNumerator > betaDenominator) {
//				doIntersect = Standard_False;
//			}
//		}
//		else if (betaNumerator > 0 || betaNumerator < betaDenominator) {
//			doIntersect = Standard_False;
//		}
//	}
//
//	return doIntersect;
//}