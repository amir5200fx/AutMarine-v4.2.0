#include <FvEntity_BoundaryFace2d.hxx>

AutLib::FvLib::FvEntity_BoundaryFace2d::FvEntity_BoundaryFace2d()
{
}

AutLib::FvLib::FvEntity_BoundaryFace2d::FvEntity_BoundaryFace2d
(
	const Standard_Integer theIndex,
	const Global_Handle(FvEntity_Node2d) theNode0,
	const Global_Handle(FvEntity_Node2d) theNode1
)
	: FvEntity_Face2d(theIndex, theNode0, theNode1)
{
}

AutLib::FvLib::FvEntity_BoundaryFace2d::~FvEntity_BoundaryFace2d()
{
}

void AutLib::FvLib::FvEntity_BoundaryFace2d::SetType(const FvBC_Type theType)
{
	theType_ = theType;
}