#pragma once
#ifndef _FvmMesh_Face2d_Header
#define _FvmMesh_Face2d_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <gp_Dir2d.hxx>
#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace FvmLib
	{

		class FvmMesh_Node2d;
		class FvmMesh_Element2d;

		class FvmMesh_Face2d
		{

		private:

			const Global_Handle(FvmMesh_Node2d) theNode0_;
			const Global_Handle(FvmMesh_Node2d) theNode1_;

			const Global_Handle(FvmMesh_Element2d) theElement_;

			const Global_Handle(FvmMesh_Face2d) thePair_;

			Geom_Pnt2d theCentre_;

			gp_Dir2d theVector_;
			gp_Dir2d theNormal_;

			Standard_Real theLength_;

			Standard_Integer theIndex_;

		public:

			FvmMesh_Face2d();

			FvmMesh_Face2d(const Standard_Integer theIndex, const Global_Handle(FvmMesh_Node2d) theNode0, const Global_Handle(FvmMesh_Node2d) theNode1);

			void Init(const Standard_Integer theIndex, const Global_Handle(FvmMesh_Node2d) theNode0, const Global_Handle(FvmMesh_Node2d) theNode1);

			void SetElement(const Global_Handle(FvmMesh_Element2d) theElement);

			void SetPair(const Global_Handle(FvmMesh_Face2d) thePair);

			const Global_Handle(FvmMesh_Node2d) Node0() const;

			const Global_Handle(FvmMesh_Node2d) Node1() const;

			const Global_Handle(FvmMesh_Element2d) Element() const;

			const Global_Handle(FvmMesh_Face2d) Pair() const;

			const Geom_Pnt2d& Centre() const;

			const gp_Dir2d& Vector() const;

			const gp_Dir2d& Normal() const;

			Standard_Real Length() const;

			Standard_Integer Index() const;
		};
	}
}

#include <FvmMesh_Face2dI.hxx>

#endif // !_FvmMesh_Face2d_Header
