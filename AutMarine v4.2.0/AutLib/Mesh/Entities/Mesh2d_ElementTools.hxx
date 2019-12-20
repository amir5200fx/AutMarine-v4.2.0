#pragma once
#ifndef _Mesh2d_ElementTools_Header
#define _Mesh2d_ElementTools_Header

#include <Mesh2d_Element.hxx>
#include <TColEntity_Ary1dOfTriangleIndex.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_ElementTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Mesh2d_Element) const &theElement1, Global_Handle(Mesh2d_Element) const &theElement2);

			static M_GEO Entity_TriangleIndex StaticOf(const Mesh2d_Element & Element);

			static TColEntity_Ary1dOfTriangleIndex StaticOf(const TColMesh2d_HAry1dOfElement& Elements);
		};
	}
}

#include <Mesh2d_ElementToolsI.hxx>

#endif // !_Mesh2d_ElementTools_Header
