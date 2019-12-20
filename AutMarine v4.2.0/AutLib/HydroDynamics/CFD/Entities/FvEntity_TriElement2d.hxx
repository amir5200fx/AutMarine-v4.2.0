#pragma once
#ifndef _FvEntity_TriElement2d_Header
#define _FvEntity_TriElement2d_Header

#include <FvEntity_Element2d.hxx>
#include <FvEntity_Face2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvEntity_TriElement2d : public FvEntity_Element2d
		{

		private:

			const Global_Handle(FvEntity_Node2d) theNode0_;
			const Global_Handle(FvEntity_Node2d) theNode1_;
			const Global_Handle(FvEntity_Node2d) theNode2_;

			const Global_Handle(FvEntity_Face2d) theFace0_;
			const Global_Handle(FvEntity_Face2d) theFace1_;
			const Global_Handle(FvEntity_Face2d) theFace2_;

		public:

			FvEntity_TriElement2d();

			FvEntity_TriElement2d(const Label theIndex, const Global_Handle(FvEntity_Node2d) theNode0, const Global_Handle(FvEntity_Node2d) theNode1, const Global_Handle(FvEntity_Node2d) theNode2);

			void Init(const Label theIndex, const Global_Handle(FvEntity_Node2d) theNode0, const Global_Handle(FvEntity_Node2d) theNode1, const Global_Handle(FvEntity_Node2d) theNode2);

			void SetNode(const Label theIndex, const Global_Handle(FvEntity_Node2d) theNode);

			virtual void SetFace(const Label theIndex, const Global_Handle(FvEntity_Face2d) theFace);

			virtual Label NbNodes() const;

			virtual Label NbFaces() const;

			virtual const Global_Handle(FvEntity_Node2d) Node(const Label theIndex) const;

			virtual const Global_Handle(FvEntity_Face2d) Face(const Label theIndex) const;

			virtual const Global_Handle(FvEntity_Element2d) Neighbor(const Label theIndex) const;
		};
	}
}

#include <FvEntity_TriElement2dI.hxx>

#endif // !_FvEntity_TriElement2d_Header
