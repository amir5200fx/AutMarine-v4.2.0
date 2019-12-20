#pragma once
#ifndef _Entity_Triangulation3dTools_Header
#define _Entity_Triangulation3dTools_Header

#include <Standard_Handle.hxx>

class Poly_Triangulation;

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Triangulation3d;

		class Entity_Triangulation3dTools
		{

		public:

			static void GetTriangulation(const Handle(Poly_Triangulation)& thePoly, Entity_Triangulation3d& theTriangulation);
		};
	}
}

#endif // !_Entity_Triangulation3dTools_Header
