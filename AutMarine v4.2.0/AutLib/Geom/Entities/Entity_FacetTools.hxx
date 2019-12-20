#pragma once
#ifndef _Entity_FacetTools_Header
#define _Entity_FacetTools_Header

#include <Entity_Facet.hxx>
#include <TColEntity_Ary1dOfTriangleIndex.hxx>
#include <TColEntity_HAry1dOfFacet.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_TiangleIndex;
		class Entity_FacetTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Entity_Facet) const &Element0, Global_Handle(Entity_Facet) const &Element1);

			static TColEntity_Ary1dOfTriangleIndex StaticOf(const TColEntity_HAry1dOfFacet& Facets);
		};
	}
}

#include <Entity_FacetToolsI.hxx>

#endif // !_Entity_FacetTools_Header
