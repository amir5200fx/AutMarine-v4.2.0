#pragma once
#ifndef _Entity_Box2dTools_Header
#define _Entity_Box2dTools_Header

#include <Entity_Box2d.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColEntity_HAry1dOfBox2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Box2d;
		class Entity_Triangulation2d;

		class Entity_Box2dTools
		{

		public:

			static Standard_Boolean IsPointInsideBox(const Geom_Pnt2d& Point, const Entity_Box2d& Box);

			static Standard_Boolean IsBoxInsideBox(const Entity_Box2d& theInner, const Entity_Box2d& theBox);

			static Standard_Boolean IsIntersect(const Entity_Box2d& theBox1, const Entity_Box2d& theBox2);

			static Entity_Box2d Union(const Entity_Box2d&, const Entity_Box2d&);

			static Entity_Box2d Intersect(const Entity_Box2d&, const Entity_Box2d&);

			static Entity_Box2d BoxOf(const Geom_Pnt2d& theCoord, const Standard_Real theOffset);

			static Entity_Box2d BoxOf(const TColGeom_Ary1dOfPnt2d& theCoords, const Standard_Real theOffset);

			static void Triangulation(const TColEntity_HAry1dOfBox2d& Boxes, Global_Handle(Entity_Triangulation2d) Mesh);

			static void TessellatedTriangulation(const TColEntity_HAry1dOfBox2d& Boxes, Global_Handle(Entity_Triangulation2d) Mesh);
		};
	}
}

#include <Entity_Box2dToolsI.hxx>

#endif // !_Entity_Box2dTools_Header
