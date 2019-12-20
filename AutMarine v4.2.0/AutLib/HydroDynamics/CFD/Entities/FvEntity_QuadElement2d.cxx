#include <FvEntity_QuadElement2d.hxx>

AutLib::FvLib::FvEntity_QuadElement2d::FvEntity_QuadElement2d()
{
}

AutLib::FvLib::FvEntity_QuadElement2d::FvEntity_QuadElement2d
(
	const Label theIndex,
	const Global_Handle(FvEntity_Node2d) theNode0, 
	const Global_Handle(FvEntity_Node2d) theNode1,
	const Global_Handle(FvEntity_Node2d) theNode2,
	const Global_Handle(FvEntity_Node2d) theNode3
)
	: FvEntity_Element2d(theIndex)
	, theNode0_(theNode0)
	, theNode1_(theNode1)
	, theNode2_(theNode2)
	, theNode3_(theNode3)
{
}

void AutLib::FvLib::FvEntity_QuadElement2d::Init
(
	const Label theIndex,
	const Global_Handle(FvEntity_Node2d) theNode0,
	const Global_Handle(FvEntity_Node2d) theNode1, 
	const Global_Handle(FvEntity_Node2d) theNode2, 
	const Global_Handle(FvEntity_Node2d) theNode3
)
{
	FvEntity_Element2d::SetIndex(theIndex);

	theNode0_ = theNode0;
	theNode1_ = theNode1;
	theNode2_ = theNode2;
	theNode3_ = theNode3;
}

void AutLib::FvLib::FvEntity_QuadElement2d::SetNode
(
	const Label theIndex,
	const Global_Handle(FvEntity_Node2d) theNode
)
{
	(&theNode0_)[theIndex] = theNode;
}

void AutLib::FvLib::FvEntity_QuadElement2d::SetFace
(
	const Label theIndex, 
	const Global_Handle(FvEntity_Face2d) theFace
)
{
	(&theFace0_)[theIndex] = theFace;
}