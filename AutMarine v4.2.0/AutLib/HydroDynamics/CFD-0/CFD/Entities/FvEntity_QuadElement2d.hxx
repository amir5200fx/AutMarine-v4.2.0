#pragma once
#ifndef _FvEntity_QuadElement2d_Header
#define _FvEntity_QuadElement2d_Header

#include <FvEntity_Element2d.hxx>
#include <FvEntity_Face2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvEntity_QuadElement2d : public FvEntity_Element2d
		{

		private:

			const Global_Handle(FvEntity_Node2d) theNode0_;
			const Global_Handle(FvEntity_Node2d) theNode1_;
			const Global_Handle(FvEntity_Node2d) theNode2_;
			const Global_Handle(FvEntity_Node2d) theNode3_;

			const Global_Handle(FvEntity_Face2d) theFace0_;
			const Global_Handle(FvEntity_Face2d) theFace1_;
			const Global_Handle(FvEntity_Face2d) theFace2_;
			const Global_Handle(FvEntity_Face2d) theFace3_;

		public:

			FvEntity_QuadElement2d();

			FvEntity_QuadElement2d(const Standard_Integer theIndex, const Global_Handle(FvEntity_Node2d) theNode0, const Global_Handle(FvEntity_Node2d) theNode1, const Global_Handle(FvEntity_Node2d) theNode2, const Global_Handle(FvEntity_Node2d) theNode3);

			void Init(const Standard_Integer theIndex, const Global_Handle(FvEntity_Node2d) theNode0, const Global_Handle(FvEntity_Node2d) theNode1, const Global_Handle(FvEntity_Node2d) theNode2, const Global_Handle(FvEntity_Node2d) theNode3);

			void SetNode(const Standard_Integer theIndex, const Global_Handle(FvEntity_Node2d) theNode);

			virtual void SetFace(const Standard_Integer theIndex, const Global_Handle(FvEntity_Face2d) theFace);

			virtual Standard_Integer NbNodes() const;

			virtual Standard_Integer NbFaces() const;

			virtual const Global_Handle(FvEntity_Node2d) Node(const Standard_Integer theIndex) const;

			virtual const Global_Handle(FvEntity_Face2d) Face(const Standard_Integer theIndex) const;

			virtual const Global_Handle(FvEntity_Element2d) Neighbor(const Standard_Integer theIndex) const;
		};
	}
}

#include <FvEntity_QuadElement2dI.hxx>

#endif // !_FvEntity_QuadElement2d_Header
