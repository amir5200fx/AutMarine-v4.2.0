#include <Geometry_Tools.hxx>

#include "..\Shewchuk\predicates.h"

using namespace AutLib;

void AutLib::GeoLib::Geometry_Tools::CalcMinMax
(
	const TColGeom_Ary1dOfPnt3d & Points,
	Standard_Real & Xmin,
	Standard_Real & Xmax,
	Standard_Real & Ymin, 
	Standard_Real & Ymax, 
	Standard_Real & Zmin,
	Standard_Real & Zmax
)
{
	if (NOT Points.Size()) { THROW_STANDARD_EXCEPTION(" Empty List"); }

	Xmin = Xmax = Points[0].X();
	Ymin = Ymax = Points[0].Y();
	Zmin = Zmax = Points[0].Z();

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
		if (Point.Z() > Zmax) Zmax = Point.Z();
		if (Point.Z() < Zmin) Zmin = Point.Z();
	}
}

Standard_Real AutLib::GeoLib::Geometry_Tools::MachineEpsilon()
{
	return epsilon;
}

void AutLib::GeoLib::Geometry_Tools::InitExact(Standard_Real& theEpsilon)
{
	exactinit(0);

	theEpsilon = epsilon;
}

Standard_Real AutLib::GeoLib::Geometry_Tools::Oriented
(
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2, 
	const Geom_Pnt2d & P3
)
{
	static Standard_Real pa[2];
	static Standard_Real pb[2];
	static Standard_Real pc[2];

	pa[0] = P1.X();
	pa[1] = P1.Y();

	pb[0] = P2.X();
	pb[1] = P2.Y();

	pc[0] = P3.X();
	pc[1] = P3.Y();
	/*cout.precision(16);
	cout << epsilon << endl;
	PAUSE;*/
	return orient2d(pa, pb, pc);
}

Standard_Real AutLib::GeoLib::Geometry_Tools::Oriented
(
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3,
	const Geom_Pnt3d & P4
)
{
	static Standard_Real pa[3];
	static Standard_Real pb[3];
	static Standard_Real pc[3];
	static Standard_Real pd[3];

	pa[0] = P1.X();
	pa[1] = P1.Y();
	pa[2] = P1.Z();

	pb[0] = P2.X();
	pb[1] = P2.Y();
	pb[2] = P2.Z();

	pc[0] = P3.X();
	pc[1] = P3.Y();
	pc[2] = P3.Z();

	pd[0] = P4.X();
	pd[1] = P4.Y();
	pd[2] = P4.Z();

	return orient3d(pa, pb, pc, pd);
}

Standard_Real AutLib::GeoLib::Geometry_Tools::FastOriented
(
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2,
	const Geom_Pnt3d & P3,
	const Geom_Pnt3d & P4
)
{
	static Standard_Real pa[3];
	static Standard_Real pb[3];
	static Standard_Real pc[3];
	static Standard_Real pd[3];

	pa[0] = P1.X();
	pa[1] = P1.Y();
	pa[2] = P1.Z();

	pb[0] = P2.X();
	pb[1] = P2.Y();
	pb[2] = P2.Z();

	pc[0] = P3.X();
	pc[1] = P3.Y();
	pc[2] = P3.Z();

	pd[0] = P4.X();
	pd[1] = P4.Y();
	pd[2] = P4.Z();

	return orient3dfast(pa, pb, pc, pd);
}

Standard_Boolean AutLib::GeoLib::Geometry_Tools::IsCcwOrder(const TColGeom_Ary1dOfPnt2d & Points)
{
	Standard_Real Sum = 0;
	forThose(Index, 1, MaxIndexOf(Points))
	{
		Sum += CrossProduct(Points[Index - 1], Points[Index]);
	}
	Sum += CrossProduct(Points.Last(), Points.First());
	return Sum > 0;
}

void AutLib::GeoLib::Geometry_Tools::ConvertTriangleTo2D
(
	const Geom_Pnt3d & theQ1,
	const Geom_Pnt3d & theQ2, 
	const Geom_Pnt3d & theQ3, 
	Geom_Pnt2d & theP2,
	Geom_Pnt2d & theP3
)
{
	Geom_Pnt3d V1 = theQ2 - theQ1;
	Geom_Pnt3d V2 = theQ3 - theQ1;

	mat33 R = inv(CalcRotationMatrix(V1.UnitLength(), V2.UnitLength()));

	vec3 Q2, Q3;
	Q2(0) = V1.X();
	Q2(1) = V1.Y();
	Q2(2) = V1.Z();

	Q3(0) = V2.X();
	Q3(1) = V2.Y();
	Q3(2) = V2.Z();

	Q2 = R*Q2;
	Q3 = R*Q3;

	theP2.X() = Q2(0);
	theP2.Y() = Q2(1);

	theP3.X() = Q3(0);
	theP3.Y() = Q3(1);
}