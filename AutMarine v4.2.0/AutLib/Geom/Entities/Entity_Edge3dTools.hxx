#pragma once
#ifndef _Entity_Edge3dTools_Header
#define _Entity_Edge3dTools_Header

#include <Entity_Edge3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Edge3dTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Entity_Edge3d) const &Edge0, Global_Handle(Entity_Edge3d) const &Edge1);
		};
	}
}

#include <Entity_Edge3dToolsI.hxx>

#endif // !_Entity_Edge3dTools_Header
