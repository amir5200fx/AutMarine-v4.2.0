#pragma once
#ifndef _Entity_Element2dTools_Header
#define _Entity_Element2dTools_Header

#include <Entity_Element2d.hxx>

#include <TColEntity_Ary1dOfTriangleIndex.hxx>
#include <TColEntity_HAry1dOfElement2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Element2dTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Entity_Element2d) const &Element0, Global_Handle(Entity_Element2d) const &Element1);

			static TColEntity_Ary1dOfTriangleIndex GetStaticOf(const TColEntity_HAry1dOfElement2d& Elements);
		};
	}
}

#include <Entity_Element2dToolsI.hxx>

#endif // !_Entity_Element2dTools_Header
