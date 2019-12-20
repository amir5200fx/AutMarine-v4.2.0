#pragma once
#ifndef _Entity_Node3dTools_Header
#define _Entity_Node3dTools_Header

#include <Entity_Node3d.hxx>
#include <TColEntity_HAry1dOfNode3d.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Node3dTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Entity_Node3d) const & Node0, Global_Handle(Entity_Node3d) const & Node1);

			static TColGeom_Ary1dOfPnt3d GetStaticOf(const TColEntity_HAry1dOfNode3d& Nodes);
		};
	}
}

#include <Entity_Node3dToolsI.hxx>

#endif // !_Entity_Node3dTools_Header
