#pragma once
#ifndef _Entity_Element3dTools_Header
#define _Entity_Element3dTools_Header

#include <Entity_Element3d.hxx>

#include <TColEntity_Ary1dOfTetrahedronIndex.hxx>
#include <TColEntity_HAry1dOfElement3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Element3dTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Entity_Element3d) const &Element0, Global_Handle(Entity_Element3d) const &Element1);

			static TColEntity_Ary1dOfTetrahedronIndex GetStaticOf(const TColEntity_HAry1dOfElement3d& Elements);

			static void EdgeIndices(const Standard_Integer Index, Standard_Integer& V1, Standard_Integer& V2);

			static void FacetIndices(const Standard_Integer Index, Standard_Integer& V1, Standard_Integer& V2, Standard_Integer& V3);
		};
	}
}

#include <Entity_Element3dToolsI.hxx>

#endif // !_Entity_Element3dTools_Header
