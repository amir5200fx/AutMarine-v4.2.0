#pragma once
#ifndef _Entity_Node2dTools_Header
#define _Entity_Node2dTools_Header

#include <Entity_Node2d.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColEntity_HAry1dOfNode2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Node2dTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Entity_Node2d) const & Node0, Global_Handle(Entity_Node2d) const & Node1);

			static TColGeom_Ary1dOfPnt2d GetStaticOf(const TColEntity_HAry1dOfNode2d& Nodes);
		};
	}
}

#include <Entity_Node2dToolsI.hxx>

#endif // !_Entity_Node2dTools_Header
