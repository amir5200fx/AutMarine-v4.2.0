#pragma once
#ifndef _Geom_Triangulation_Header
#define _Geom_Triangulation_Header

#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <Global_Memory.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Triangulation2d;
		class Entity_Tetrahedralization;

		class Geom_Triangulation
		{

		public:

			static void DelaunayTriangulation(const TColGeom_Ary1dOfPnt2d& UnMerged_Coords, Global_Handle(Entity_Triangulation2d) Mesh);

			static void DelaunayTriangulation(const TColGeom_Ary1dOfPnt3d& UnMerged_Coords, Global_Handle(Entity_Tetrahedralization) Mesh);
		};
	}
}

#endif // !_Geom_Triangulation_Header
