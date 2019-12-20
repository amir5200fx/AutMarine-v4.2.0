#include <FvEntity_TriElement2d.hxx>

AutLib::FvLib::FvEntity_TriElement2d::FvEntity_TriElement2d()
{
}

AutLib::FvLib::FvEntity_TriElement2d::FvEntity_TriElement2d
(
	const Standard_Integer theIndex, 
	const Global_Handle(FvEntity_Node2d) theNode0, 
	const Global_Handle(FvEntity_Node2d) theNode1,
	const Global_Handle(FvEntity_Node2d) theNode2
)
	: FvEntity_Element2d(theIndex)
	, theNode0_(theNode0)
	, theNode1_(theNode1)
	, theNode2_(theNode2)
{
}

void AutLib::FvLib::FvEntity_TriElement2d::Init
(
	const Standard_Integer theIndex,
	const Global_Handle(FvEntity_Node2d) theNode0,
	const Global_Handle(FvEntity_Node2d) theNode1,
	const Global_Handle(FvEntity_Node2d) theNode2
)
{
	FvEntity_Element2d::SetIndex(theIndex);

	theNode0_ = theNode0;
	theNode1_ = theNode1;
	theNode2_ = theNode2;
}

void AutLib::FvLib::FvEntity_TriElement2d::SetNode
(
	const Standard_Integer theIndex, 
	const Global_Handle(FvEntity_Node2d) theNode
)
{
	(&theNode0_)[theIndex] = theNode;
}

void AutLib::FvLib::FvEntity_TriElement2d::SetFace
(
	const Standard_Integer theIndex, 
	const Global_Handle(FvEntity_Face2d) theFace
)
{
	(&theFace0_)[theIndex] = theFace;
}