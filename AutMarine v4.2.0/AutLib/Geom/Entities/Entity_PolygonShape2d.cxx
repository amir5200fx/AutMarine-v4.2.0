#include <Entity_PolygonShape2d.hxx>

#include <gp_Ax22d.hxx>
#include <gp_Ax2d.hxx>

AutLib::GeoLib::Entity_PolygonShape2d::Entity_PolygonShape2d()
{
}

void AutLib::GeoLib::Entity_PolygonShape2d::MakeBox
(
	const gp_Ax22d & A,
	const Standard_Real Dx,
	const Standard_Real Dy
)
{
	Geom_Pnt2d P0;
	Geom_Pnt2d P1(Dx, 0);
	Geom_Pnt2d P2(Dx, Dy);
	Geom_Pnt2d P3(0, Dy);

	gp_Trsf2d T;
	T.SetTransformation(A.XAxis());
	T.Invert();
	
	P0.Transform(T);
	P1.Transform(T);
	P2.Transform(T);
	P3.Transform(T);

	thePoints_.Resize(5);
	thePoints_.SetValue(0, P0);
	thePoints_.SetValue(1, P1);
	thePoints_.SetValue(2, P2);
	thePoints_.SetValue(3, P3);
	thePoints_.SetValue(4, P0);
}

void AutLib::GeoLib::Entity_PolygonShape2d::MakeBox
(
	const gp_Ax2d & A,
	const Standard_Real Dx,
	const Standard_Real Dy,
	const Standard_Boolean Sense
)
{
	MakeBox(gp_Ax22d(A, Sense), Dx, Dy);
}

void AutLib::GeoLib::Entity_PolygonShape2d::MakeCircle
(
	const Geom_Pnt2d & theCentre, 
	const Standard_Real theRadius,
	const Standard_Integer theNbSegments
)
{
	thePoints_.Resize(theNbSegments + 1);

	Standard_Real Theta = 2 * PI / (Standard_Real)theNbSegments;

	forThose
	(
		Index,
		0, 
		MaxIndexOf(thePoints_)
	)
	{
		Standard_Real X = theCentre.X() + theRadius*cos(Index*Theta);
		Standard_Real Y = theCentre.Y() + theRadius*sin(Index*Theta);

		thePoints_[Index].SetCoord(X, Y);
	}
	thePoints_.SetLast(thePoints_.First());
}