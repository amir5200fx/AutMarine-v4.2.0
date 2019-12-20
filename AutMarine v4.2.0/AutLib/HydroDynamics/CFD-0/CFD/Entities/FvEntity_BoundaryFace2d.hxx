#pragma once
#ifndef _FvEntity_BoundaryFace2d_Header
#define _FvEntity_BoundaryFace2d_Header

#include <FvEntity_Face2d.hxx>
#include <FvBC_Type.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvEntity_BoundaryFace2d : public FvEntity_Face2d
		{

		private:

			FvBC_Type theType_;

		public:

			FvEntity_BoundaryFace2d();

			FvEntity_BoundaryFace2d(const Standard_Integer theIndex, const Global_Handle(FvEntity_Node2d) theNode0, const Global_Handle(FvEntity_Node2d) theNode1);

			virtual ~FvEntity_BoundaryFace2d();

			void SetType(const FvBC_Type theType);

			FvBC_Type Type() const;
		};
	}

}

#include <FvEntity_BoundaryFace2dI.hxx>

#endif // !_FvEntity_BoundaryFace2d_Header
