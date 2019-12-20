#include <FvEntity_PolyElement2d.hxx>

AutLib::FvLib::FvEntity_PolyElement2d::FvEntity_PolyElement2d()
{
}

AutLib::FvLib::FvEntity_PolyElement2d::FvEntity_PolyElement2d
(
	const Label theIndex,
	const FvList_Node2d & theNodes
)
	: FvEntity_Element2d(theIndex)
	, theNodes_(theNodes)
{
}

void AutLib::FvLib::FvEntity_PolyElement2d::Init
(
	const Label theIndex, 
	const FvList_Node2d & theNodes
)
{
	FvEntity_Element2d::SetIndex(theIndex);

	theNodes_ = theNodes;
}

void AutLib::FvLib::FvEntity_PolyElement2d::SetNode
(
	const Label theIndex,
	const Global_Handle(FvEntity_Node2d) theNode
)
{
	Debug_Bad_Index_Array1(theIndex, theNodes_);
	theNodes_.SetValue(theIndex, (Global_Handle(FvEntity_Node2d))theNode);
}

void AutLib::FvLib::FvEntity_PolyElement2d::SetFace
(
	const Label theIndex,
	const Global_Handle(FvEntity_Face2d) theFace
)
{
	Debug_Bad_Index_Array1(theIndex, theFaces_);
	theFaces_.SetValue(theIndex, (Global_Handle(FvEntity_Face2d))theFace);
}