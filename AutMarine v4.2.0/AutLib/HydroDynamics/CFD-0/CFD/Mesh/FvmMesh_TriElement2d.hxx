#pragma once
#ifndef _FvmMesh_TriElement2d_Header
#define _FvmMesh_TriElement2d_Header

#include <Global_Memory.hxx>
#include <Global_Debug.hxx>
#include <FvmMesh_Element2d.hxx>

namespace AutLib
{
	namespace FvmLib
	{

		class FvmMesh_TriElement2d : public FvmMesh_Element2d
		{

		private:

			const Global_Handle(FvmMesh_Node2d) theNode0_;
			const Global_Handle(FvmMesh_Node2d) theNode1_;
			const Global_Handle(FvmMesh_Node2d) theNode2_;

			const Global_Handle(FvmMesh_Face2d) theFace0_;
			const Global_Handle(FvmMesh_Face2d) theFace1_;
			const Global_Handle(FvmMesh_Face2d) theFace2_;

		public:

			FvmMesh_TriElement2d();

			FvmMesh_TriElement2d(const Global_Handle(FvmMesh_Node2d) theNode0, const Global_Handle(FvmMesh_Node2d) theNode1, const Global_Handle(FvmMesh_Node2d) theNode2, const Global_Handle(FvmMesh_Face2d) theFace0, const Global_Handle(FvmMesh_Face2d) theFace1, const Global_Handle(FvmMesh_Face2d) theFace2);

			void Init(const Global_Handle(FvmMesh_Node2d) theNode0, const Global_Handle(FvmMesh_Node2d) theNode1, const Global_Handle(FvmMesh_Node2d) theNode2, const Global_Handle(FvmMesh_Face2d) theFace0, const Global_Handle(FvmMesh_Face2d) theFace1, const Global_Handle(FvmMesh_Face2d) theFace2);

			const Global_Handle(FvmMesh_Node2d) Node0() const;

			const Global_Handle(FvmMesh_Node2d) Node1() const;

			const Global_Handle(FvmMesh_Node2d) Node2() const;

			const Global_Handle(FvmMesh_Face2d) Face0() const;

			const Global_Handle(FvmMesh_Face2d) Face1() const;

			const Global_Handle(FvmMesh_Face2d) Face2() const;
		};
	}
}

#include <FvmMesh_TriElement2dI.hxx>

#endif // !_FvmMesh_TriElement2d_Header
