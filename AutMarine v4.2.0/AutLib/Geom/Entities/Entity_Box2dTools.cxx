#include <Entity_Box2dTools.hxx>

#include <Entity_Triangulation2d.hxx>
#include <Geom_Triangulation.hxx>
#include <Geometry_Intersect.hxx>
#include <Geometry_Tools.hxx>
#include <TColGeom_BasicQueueOfPnt2d.hxx>

using namespace AutLib;
using namespace GeoLib;

Standard_Boolean AutLib::GeoLib::Entity_Box2dTools::IsBoxInsideBox
(
	const Entity_Box2d & theInner,
	const Entity_Box2d & theBox
)
{
	Standard_Real Xmin = theBox.Xmin();
	Standard_Real Xmax = theBox.Xmax();

	if (NOT INSIDE(theInner.Xmin(), Xmin, Xmax)) return Standard_False;
	if (NOT INSIDE(theInner.Xmax(), Xmin, Xmax)) return Standard_False;

	Standard_Real Ymin = theBox.Ymin();
	Standard_Real Ymax = theBox.Ymax();

	if (NOT INSIDE(theInner.Ymin(), Ymin, Ymax)) return Standard_False;
	if (NOT INSIDE(theInner.Ymax(), Ymin, Ymax)) return Standard_False;

	return Standard_True;
}

Standard_Boolean AutLib::GeoLib::Entity_Box2dTools::IsIntersect
(
	const Entity_Box2d & theBox1,
	const Entity_Box2d & theBox2
)
{
	return Geometry_Intersect::IsIntersect(theBox1, theBox2);
}

Entity_Box2d AutLib::GeoLib::Entity_Box2dTools::Union
(
	const Entity_Box2d & Box1,
	const Entity_Box2d & Box2
)
{
	Standard_Real xmin = MIN(Box1.Xmin(), Box2.Xmin());
	Standard_Real xmax = MAX(Box1.Xmax(), Box2.Xmax());
	Standard_Real ymin = MIN(Box1.Ymin(), Box2.Ymin());
	Standard_Real ymax = MAX(Box1.Ymax(), Box2.Ymax());

	Entity_Box2d newBox
	(
		xmin,
		xmax,
		ymin,
		ymax
	);

	MOVE(newBox);
}

Entity_Box2d AutLib::GeoLib::Entity_Box2dTools::Intersect
(
	const Entity_Box2d & Box1,
	const Entity_Box2d & Box2
)
{
	Standard_Real xmin = MAX(Box1.Xmin(), Box2.Xmin());
	Standard_Real xmax = MIN(Box1.Xmax(), Box2.Xmax());
	Standard_Real ymin = MAX(Box1.Ymin(), Box2.Ymin());
	Standard_Real ymax = MIN(Box1.Ymax(), Box2.Ymax());

	if (xmin > xmax)
	{
		xmin = 0;
		xmax = 0;
	}

	if (ymin > ymax)
	{
		ymin = 0;
		ymax = 0;
	}

	Entity_Box2d newBox
	(
		xmin,
		xmax,
		ymin,
		ymax
	);

	MOVE(newBox);
}

Entity_Box2d AutLib::GeoLib::Entity_Box2dTools::BoxOf
(
	const Geom_Pnt2d & theCoord,
	const Standard_Real theOffset
)
{
	return Entity_Box2d(theCoord.X() - theOffset, theCoord.X() + theOffset, theCoord.Y() - theOffset, theCoord.Y() + theOffset);
}

Entity_Box2d AutLib::GeoLib::Entity_Box2dTools::BoxOf
(
	const TColGeom_Ary1dOfPnt2d & theCoords, 
	const Standard_Real theOffset
)
{
	Standard_Real Xmin, Xmax, Ymin, Ymax;
	Geometry_Tools::CalcMinMax(theCoords, Xmin, Xmax, Ymin, Ymax);

	return Entity_Box2d(Xmin - theOffset, Xmax + theOffset, Ymin - theOffset, Ymax + theOffset);
}

void AutLib::GeoLib::Entity_Box2dTools::Triangulation
(
	const TColEntity_HAry1dOfBox2d & Boxes,
	Global_Handle(Entity_Triangulation2d) Mesh
)
{
	TColGeom_Ary1dOfPnt2d Points(4 * Boxes.Size());

	Standard_Integer k = 0;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Boxes)
	)
	{
		Debug_Null_Pointer(Boxes[Index]);

		Get_Const_Object(Box) = *Boxes[Index];

		Try_Exception_Handle_Exit(Points[k++] = Box.GetSwPoint());
		Try_Exception_Handle_Exit(Points[k++] = Box.GetSePoint());
		Try_Exception_Handle_Exit(Points[k++] = Box.GetNwPoint());
		Try_Exception_Handle_Exit(Points[k++] = Box.GetNePoint());
	}

	Geom_Triangulation::DelaunayTriangulation(Points, Mesh);
}

void AutLib::GeoLib::Entity_Box2dTools::TessellatedTriangulation
(
	const TColEntity_HAry1dOfBox2d & Boxes,
	Global_Handle(Entity_Triangulation2d) Mesh
)
{
	TColGeom_Ary1dOfPnt2d Points(5 * Boxes.Size());

	Standard_Integer k = 0;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Boxes)
	)
	{
		Debug_Null_Pointer(Boxes[Index]);

		Get_Const_Object(Box) = *Boxes[Index];

		Geom_Pnt2d P1 = Box.GetSwPoint();
		Geom_Pnt2d P2 = Box.GetSePoint();
		Geom_Pnt2d P3 = Box.GetNwPoint();
		Geom_Pnt2d P4 = Box.GetNePoint();

		Try_Exception_Handle_Exit(Points[k++] = P1);
		Try_Exception_Handle_Exit(Points[k++] = P2);
		Try_Exception_Handle_Exit(Points[k++] = P3);
		Try_Exception_Handle_Exit(Points[k++] = P4);

		Try_Exception_Handle_Exit(Points[k++] = (P1 + P2 + P3 + P4) / 4);
	}

	Geom_Triangulation::DelaunayTriangulation(Points, Mesh);
}