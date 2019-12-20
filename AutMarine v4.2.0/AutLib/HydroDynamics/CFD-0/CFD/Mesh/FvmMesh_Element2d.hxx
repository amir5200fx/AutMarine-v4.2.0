#pragma once
#ifndef _FvmMesh_Element2d_Header
#define _FvmMesh_Element2d_Header

#include <Standard_TypeDef.hxx>
#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace FvmLib
	{
		class FvmMesh_Node2d;
		class FvmMesh_Face2d;

		class FvmMesh_Element2d
		{

		private:

			Standard_Integer theIndex_;

			Standard_Real theArea_;

			Geom_Pnt2d theCentre_;

		public:

			FvmMesh_Element2d();

			FvmMesh_Element2d(const Standard_Integer theIndex);

			Standard_Integer Index() const;

			Standard_Real Area() const;

			const Geom_Pnt2d& Centre() const;

		};
	}
}

#endif // !_FvmMesh_Element2d_Header
