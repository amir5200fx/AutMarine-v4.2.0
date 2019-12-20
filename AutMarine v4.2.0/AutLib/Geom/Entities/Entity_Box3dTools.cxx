#include <Entity_Box3dTools.hxx>

#include <Geometry_Tools.hxx>
#include <Geom_Triangulation.hxx>
#include <Entity_Box3d.hxx>
#include <Entity_Tetrahedralization.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>

using namespace AutLib;
using namespace GeoLib;

Standard_Boolean AutLib::GeoLib::Entity_Box3dTools::IsBoxInsideBox
(
	const Entity_Box3d & theInner,
	const Entity_Box3d & theBox
)
{
	const Standard_Real Xmin = theBox.Xmin();
	const Standard_Real Xmax = theBox.Xmax();

	if (NOT INSIDE(theInner.Xmin(), Xmin, Xmax)) return Standard_False;
	if (NOT INSIDE(theInner.Xmax(), Xmin, Xmax)) return Standard_False;

	const Standard_Real Ymin = theBox.Ymin();
	const Standard_Real Ymax = theBox.Ymax();

	if (NOT INSIDE(theInner.Ymin(), Ymin, Ymax)) return Standard_False;
	if (NOT INSIDE(theInner.Ymax(), Ymin, Ymax)) return Standard_False;

	const Standard_Real Zmin = theBox.Zmin();
	const Standard_Real Zmax = theBox.Zmax();

	if (NOT INSIDE(theInner.Zmin(), Zmin, Zmax)) return Standard_False;
	if (NOT INSIDE(theInner.Zmax(), Zmin, Zmax)) return Standard_False;

	return Standard_True;
}

Entity_Box3d AutLib::GeoLib::Entity_Box3dTools::Union(const Entity_Box3d & Box1, const Entity_Box3d & Box2)
{
	const Standard_Real xmin = MIN(Box1.Xmin(), Box2.Xmin());
	const Standard_Real xmax = MAX(Box1.Xmax(), Box2.Xmax());
	const Standard_Real ymin = MIN(Box1.Ymin(), Box2.Ymin());
	const Standard_Real ymax = MAX(Box1.Ymax(), Box2.Ymax());
	const Standard_Real zmin = MIN(Box1.Zmin(), Box2.Zmin());
	const Standard_Real zmax = MAX(Box1.Zmax(), Box2.Zmax());

	return Entity_Box3d(xmin, xmax, ymin, ymax, zmin, zmax);
}

Entity_Box3d AutLib::GeoLib::Entity_Box3dTools::Intersect
(
	const Entity_Box3d & Box1, 
	const Entity_Box3d & Box2
)
{
	Standard_Real xmin = MAX(Box1.Xmin(), Box2.Xmin());
	Standard_Real xmax = MIN(Box1.Xmax(), Box2.Xmax());
	Standard_Real ymin = MAX(Box1.Ymin(), Box2.Ymin());
	Standard_Real ymax = MIN(Box1.Ymax(), Box2.Ymax());
	Standard_Real zmin = MAX(Box1.Zmin(), Box2.Zmin());
	Standard_Real zmax = MIN(Box1.Zmax(), Box2.Zmax());

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

	if (zmin > zmax)
	{
		zmin = 0;
		zmax = 0;
	}

	Entity_Box3d newBox
	(
		xmin,
		xmax,
		ymin,
		ymax,
		zmin,
		zmax
	);

	MOVE(newBox);
}

Entity_Box3d AutLib::GeoLib::Entity_Box3dTools::BoxOf
(
	const TColGeom_Ary1dOfPnt3d & theCoords,
	const Standard_Real theOffset
)
{
	Standard_Real Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
	Geometry_Tools::CalcMinMax(theCoords, Xmin, Xmax, Ymin, Ymax, Zmin, Zmax);
	return Entity_Box3d
	(
		Xmin - theOffset, 
		Xmax + theOffset, 
		Ymin - theOffset, 
		Ymax + theOffset, 
		Zmin - theOffset, 
		Zmax + theOffset
	);
}

Entity_Box3d AutLib::GeoLib::Entity_Box3dTools::BoxOf
(
	const Geom_Pnt3d & theCoord,
	const Standard_Real theRadius
)
{
	return Entity_Box3d
	(
		theCoord.X() - theRadius,
		theCoord.X() + theRadius, 
		theCoord.Y() - theRadius, 
		theCoord.Y() + theRadius,
		theCoord.Z() - theRadius,
		theCoord.Z() + theRadius
	);
}

void AutLib::GeoLib::Entity_Box3dTools::Triangulation
(
	const TColEntity_HAry1dOfBox3d & Boxes,
	Global_Handle(Entity_Tetrahedralization) Mesh
)
{
	TColGeom_Ary1dOfPnt3d Points(8 * Boxes.Size());

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

		Try_Exception_Handle_Exit(Points[k++] = Box.Fwd_SwCorner());
		Try_Exception_Handle_Exit(Points[k++] = Box.Fwd_SeCorner());
		Try_Exception_Handle_Exit(Points[k++] = Box.Fwd_NwCorner());
		Try_Exception_Handle_Exit(Points[k++] = Box.Fwd_NeCorner());

		Try_Exception_Handle_Exit(Points[k++] = Box.Bwd_SwCorner());
		Try_Exception_Handle_Exit(Points[k++] = Box.Bwd_SeCorner());
		Try_Exception_Handle_Exit(Points[k++] = Box.Bwd_NwCorner());
		Try_Exception_Handle_Exit(Points[k++] = Box.Bwd_NeCorner());
	}

	Geom_Triangulation::DelaunayTriangulation(Points, Mesh);
}