#pragma once
#ifndef _Mesh3d_ElementTools_Header
#define _Mesh3d_ElementTools_Header

#include <Mesh3d_Element.hxx>
#include <TColEntity_Ary1dOfTetrahedronIndex.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		
		class Mesh3d_Facet;

		class Mesh3d_ElementTools
		{

		public:

			//! Throw an exception if found an error
			static Global_Handle(Mesh3d_Facet) CommonFacet(const Mesh3d_Element& theElement0, const Mesh3d_Element& theElement1);

			static M_GEO Entity_TetrahedronIndex StaticOf(const Mesh3d_Element &Element);

			static TColEntity_Ary1dOfTetrahedronIndex StaticOf(const TColMesh3d_HAry1dOfElement &Elements);

			static Standard_Boolean IsLess(Global_Handle(Mesh3d_Element) const &Element1, Global_Handle(Mesh3d_Element) const &Element2);
		};
	}
}

#include <Mesh3d_ElementToolsI.hxx>

#endif // !_Mesh3d_ElementTools_Header
