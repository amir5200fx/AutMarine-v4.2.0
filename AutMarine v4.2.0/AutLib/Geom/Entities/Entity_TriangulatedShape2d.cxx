#include <Entity_TriangulatedShape2d.hxx>

#include <Entity_PolygonShape2d.hxx>

#include <gp_Ax22d.hxx>

AutLib::GeoLib::Entity_TriangulatedShape2d::Entity_TriangulatedShape2d()
{
}

void AutLib::GeoLib::Entity_TriangulatedShape2d::MakeBox
(
	const gp_Ax22d & A,
	const Standard_Real Dx, 
	const Standard_Real Dy
)
{
	Entity_PolygonShape2d Box;
	Box.MakeBox(A, Dx, Dy);

	Get_Const_Object(Points) = Box.Points();

	thePoints_.Resize(4);
	forThose(Index, 0, MaxIndexOf(thePoints_))
		thePoints_[Index] = Points[Index];

	theTriangles_.Resize(2);
	theTriangles_[0].SetValue(1, 2, 3);
	theTriangles_[1].SetValue(3, 4, 1);
}

void AutLib::GeoLib::Entity_TriangulatedShape2d::MakeBox
(
	const gp_Ax2d & A,
	const Standard_Real Dx, 
	const Standard_Real Dy, 
	const Standard_Boolean Sense
)
{
	MakeBox(gp_Ax22d(A, Sense), Dx, Dy);
}

void AutLib::GeoLib::Entity_TriangulatedShape2d::MakeCircle
(
	const Geom_Pnt2d & theCentre,
	const Standard_Real theRadius,
	const Standard_Integer theNbSegments
)
{
	Entity_PolygonShape2d Circle;
	Circle.MakeCircle(theCentre, theRadius, theNbSegments);

	Get_Const_Object(Points) = Circle.Points();

	thePoints_.Resize(Points.Size());
	thePoints_.SetFirst(theCentre);
	forThose(Index, 0, MaxIndexOf(thePoints_) - 1)
		thePoints_[Index + 1] = Points[Index];

	theTriangles_.Resize(theNbSegments);
	forThose(Index, 0, MaxIndexOf(theTriangles_))
		theTriangles_[Index].SetValue(1, Index + 2, Index + 3);
	theTriangles_.Last().SetV2(2);
}