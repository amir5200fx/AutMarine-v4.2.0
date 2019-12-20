#pragma once
#ifndef _Entity_Box3dTools_Header
#define _Entity_Box3dTools_Header

#include <Global_Memory.hxx>
#include <TColEntity_HAry1dOfBox3d.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Box3d;
		class Entity_Tetrahedralization;

		class Entity_Box3dTools
		{

		public:

			static Standard_Boolean IsBoxInsideBox(const Entity_Box3d& theInner, const Entity_Box3d& theBox);

			static Entity_Box3d Union(const Entity_Box3d& Box1, const Entity_Box3d& Box2);

			static Entity_Box3d Intersect(const Entity_Box3d&, const Entity_Box3d&);

			static Entity_Box3d BoxOf(const TColGeom_Ary1dOfPnt3d& theCoords, const Standard_Real theOffset);

			static Entity_Box3d BoxOf(const Geom_Pnt3d& theCoord, const Standard_Real theRadius);

			static void Triangulation(const TColEntity_HAry1dOfBox3d& Boxes, Global_Handle(Entity_Tetrahedralization) Mesh);
		};
	}
}

#endif // !_Entity_Box3dTools_Header
