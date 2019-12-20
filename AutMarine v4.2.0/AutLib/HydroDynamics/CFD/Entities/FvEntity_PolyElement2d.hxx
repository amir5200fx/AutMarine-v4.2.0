#pragma once
#ifndef _FvEntity_PolyElement2d_Header
#define _FvEntity_PolyElement2d_Header

#include <FvEntity_Element2d.hxx>
#include <FvList_Node2d.hxx>
#include <FvList_Face2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvEntity_PolyElement2d : public FvEntity_Element2d
		{

		private:

			FvList_Node2d theNodes_;

			FvList_Face2d theFaces_;

		public:

			FvEntity_PolyElement2d();

			FvEntity_PolyElement2d(const Label theIndex, const FvList_Node2d& theNodes);

			void Init(const Label theIndex, const FvList_Node2d& theNodes);

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

#include <FvEntity_PolyElement2dI.hxx>

#endif // !_FvEntity_PolyElement2d_Header
