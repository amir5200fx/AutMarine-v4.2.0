#pragma once
#ifndef _FvEntity_PolyElement2d_Header
#define _FvEntity_PolyElement2d_Header

#include <FvEntity_Element2d.hxx>
#include <TColFvEntity_HAry1dOfNode2d.hxx>
#include <TColFvEntity_HAry1dOfFace2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvEntity_PolyElement2d : public FvEntity_Element2d
		{

		private:

			TColFvEntity_HAry1dOfNode2d theNodes_;

			TColFvEntity_HAry1dOfFace2d theFaces_;

		public:

			FvEntity_PolyElement2d();

			FvEntity_PolyElement2d(const Standard_Integer theIndex, const TColFvEntity_HAry1dOfNode2d& theNodes);

			void Init(const Standard_Integer theIndex, const TColFvEntity_HAry1dOfNode2d& theNodes);

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

#include <FvEntity_PolyElement2dI.hxx>

#endif // !_FvEntity_PolyElement2d_Header
