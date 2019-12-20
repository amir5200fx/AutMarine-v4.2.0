#include <Entity_Edge2dTools.hxx>

#include <Entity_Edge2d.hxx>
#include <Entity_Box2d.hxx>

using namespace AutLib;
using namespace GeoLib;

TColEntity_Ary1dOfTriangleIndex AutLib::GeoLib::Entity_Edge2dTools::GetStaticOf(const TColEntity_HAry1dOfEdge2d & Elements)
{
	TColEntity_Ary1dOfTriangleIndex Triangles(Elements.Size());

	forThose(Index, 0, MaxIndexOf(Elements))
	{
		Debug_Null_Pointer(Elements[Index]);

		Triangles[Index].SetValue(Elements[Index]->Node(0)->Index(), Elements[Index]->Node(1)->Index(), Elements[Index]->Node(0)->Index());
	}

	MOVE(Triangles);
}

Entity_Box2d AutLib::GeoLib::Entity_Edge2dTools::BoundingBoxOf(const Entity_Edge2d & Edge)
{
	Debug_Null_Pointer(Edge.Node(0));
	Debug_Null_Pointer(Edge.Node(1));

	Geom_Pnt2d P0 = Edge.Node(0)->Coord();
	Geom_Pnt2d P1 = Edge.Node(1)->Coord();

	return Entity_Box2d(MIN(P0.X(), P1.X()), MAX(P0.X(), P1.X()), MIN(P0.Y(), P1.Y()), MAX(P0.Y(), P1.Y()));
}