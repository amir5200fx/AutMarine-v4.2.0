#pragma once
#ifndef _Entity_Polygon2dTools_Header
#define _Entity_Polygon2dTools_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Polygon2d;
		class Entity_Box2d;
		class Entity_StaticChain2d;

		class Entity_Polygon2dTools
		{

		public:

			static Standard_Boolean SplitClosedPolygon(const Entity_Polygon2d& TheTarget, const Entity_Polygon2d& TheCutter, Entity_Polygon2d& Left, Entity_Polygon2d& Right);

			static Entity_Box2d BoundingBox(const Entity_Polygon2d& ThePolygon);

			static Entity_StaticChain2d GetChain(const Entity_Polygon2d& thePolygon);
		};
	}
}

#endif // !_Entity_Polygon2dTools_Header
