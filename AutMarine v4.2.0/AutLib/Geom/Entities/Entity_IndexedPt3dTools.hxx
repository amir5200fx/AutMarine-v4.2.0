#pragma once
#ifndef _Entity_IndexedPt3dTools_Header
#define _Entity_IndexedPt3dTools_Header

#include <Entity_IndexedPt3d.hxx>
#include <Global_Memory.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_IndexedPt3dTools
		{

		public:

			static const Geom_Pnt3d& CoordOf(Global_Handle(Entity_IndexedPt3d) thePoint);
		};
	}
}

#include <Entity_IndexedPt3dToolsI.hxx>

#endif // !_Entity_IndexedPt3dTools_Header
