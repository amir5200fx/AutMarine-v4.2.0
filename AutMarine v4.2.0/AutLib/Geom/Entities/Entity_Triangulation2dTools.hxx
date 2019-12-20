#pragma once
#ifndef _Entity_Triangulation2dTools_Header
#define _Entity_Triangulation2dTools_Header

#include <Standard_TypeDef.hxx>

class Poly_Triangulation;

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Triangulation2d;

		class Entity_Triangulation2dTools
		{

		public:

			static Standard_Boolean GetTriangulation(const Poly_Triangulation& thePoly, Entity_Triangulation2d& theTriangulation);
		};
	}
}

#endif // !_Entity_Triangulation2dTools_Header
