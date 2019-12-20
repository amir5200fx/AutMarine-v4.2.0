#pragma once
#ifndef _Entity_Edge2dTools_Header
#define _Entity_Edge2dTools_Header

#include <Entity_Edge2d.hxx>
#include <TColEntity_HAry1dOfEdge2d.hxx>
#include <TColEntity_Ary1dOfTriangleIndex.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Box2d;

		class Entity_Edge2dTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Entity_Edge2d) const &Edge0, Global_Handle(Entity_Edge2d) const &Edge1);

			static TColEntity_Ary1dOfTriangleIndex GetStaticOf(const TColEntity_HAry1dOfEdge2d& Edges);

			static Entity_Box2d BoundingBoxOf(const Entity_Edge2d& Edge);
		};
	}
}

#include <Entity_Edge2dToolsI.hxx>

#endif // !_Entity_Edge2dTools_Header
