#include <Geometry_Distance.hxx>

#include <Geometry_Tools.hxx>
#include "EberlyAlg.h"
 
Standard_Real AutLib::GeoLib::Geometry_Distance::DistancePointFromTriangleSQ
(
	const Geom_Pnt3d & thePoint,
	const Geom_Pnt3d & P1, 
	const Geom_Pnt3d & P2, 
	const Geom_Pnt3d & P3
)
{
	Geom_Pnt3d V1 = P2 - P1;
	Geom_Pnt3d V2 = P3 - P1;

	mat33 R = Geometry_Tools::CalcRotationMatrix(V1.UnitLength(), V2.UnitLength());

	vec3 Q1, Q2, Qt;

	Q1(0) = V1.X();
	Q1(1) = V1.Y();
	Q1(2) = V1.Z();

	Q2(0) = V2.X();
	Q2(1) = V2.Y();
	Q2(2) = V2.Z();

	Qt(0) = thePoint.X() - P1.X();
	Qt(1) = thePoint.Y() - P1.Y();
	Qt(2) = thePoint.Z() - P1.Z();

	R = inv(R);

	Q1 = R*Q1;
	Q2 = R*Q2;
	Qt = R*Qt;

	Geom_Pnt2d p1;
	Geom_Pnt2d p2(Q1(0), Q1(1));
	Geom_Pnt2d p3(Q2(0), Q2(1));
	Geom_Pnt2d pt(Qt(0), Qt(1));

	if (Geometry_Tools::IsPointRightEdge(pt, p1, p2))
	{
		Standard_Real D2 = Geometry_Distance::DistanceFromLineSegmentSQ(pt, p1, p2);
		return (D2 + Qt(2)*Qt(2));
	}
	else if (Geometry_Tools::IsPointRightEdge(pt, p2, p3))
	{
		Standard_Real D2 = Geometry_Distance::DistanceFromLineSegmentSQ(pt, p2, p3);
		return (D2 + Qt(2)*Qt(2));
	}
	else if (Geometry_Tools::IsPointRightEdge(pt, p3, p1))
	{
		Standard_Real D2 = Geometry_Distance::DistanceFromLineSegmentSQ(pt, p3, p1);
		return (D2 + Qt(2)*Qt(2));
	}
	else
	{
		return Qt(2)*Qt(2);
	}
}

Standard_Real AutLib::GeoLib::Geometry_Distance::DistancePointFromProjectedEdgesOfTriangleSQ
(
	const Geom_Pnt3d & thePoint, 
	const Geom_Pnt3d & P1, 
	const Geom_Pnt3d & P2, 
	const Geom_Pnt3d & P3
)
{
	Geom_Pnt3d V1 = P2 - P1;
	Geom_Pnt3d V2 = P3 - P1;

	mat33 R = Geometry_Tools::CalcRotationMatrix(V1.UnitLength(), V2.UnitLength());

	vec3 Q1, Q2, Qt;

	Q1(0) = V1.X();
	Q1(1) = V1.Y();
	Q1(2) = V1.Z();

	Q2(0) = V2.X();
	Q2(1) = V2.Y();
	Q2(2) = V2.Z();

	Qt(0) = thePoint.X() - P1.X();
	Qt(1) = thePoint.Y() - P1.Y();
	Qt(2) = thePoint.Z() - P1.Z();

	R = inv(R);

	Q1 = R*Q1;
	Q2 = R*Q2;
	Qt = R*Qt;

	Geom_Pnt2d p1;
	Geom_Pnt2d p2(Q1(0), Q1(1));
	Geom_Pnt2d p3(Q2(0), Q2(1));
	Geom_Pnt2d pt(Qt(0), Qt(1));

	Standard_Real D1 = Geometry_Distance::DistanceFromLineSegmentSQ(pt, p1, p2);
	Standard_Real D2 = Geometry_Distance::DistanceFromLineSegmentSQ(pt, p2, p3);
	Standard_Real D3 = Geometry_Distance::DistanceFromLineSegmentSQ(pt, p3, p1);

	return MIN(D1, MIN(D2, D3));
}

Standard_Real AutLib::GeoLib::Geometry_Distance::DistanceLineSegmentFromLineSegmentSQ
(
	const Geom_Pnt3d & P0,
	const Geom_Pnt3d & P1, 
	const Geom_Pnt3d & Q0, 
	const Geom_Pnt3d & Q1
)
{
	Segment S1, S2;

	S1.end0 = P0;
	S1.end1 = P1;

	S2.end0 = Q0;
	S2.end1 = Q1;

	Result Result;

	CSMain
	(
		S1,
		S2,
		Result
	);

	return Result.sqrDistance;
}