#include <FvEntity_Face2d.hxx>

AutLib::FvLib::FvEntity_Face2d::FvEntity_Face2d()
	: theNode0_(NULL)
	, theNode1_(NULL)
	, theElement_(NULL)
	, thePair_(NULL)
	, theArea_((Scalar)0.0)
{
}

AutLib::FvLib::FvEntity_Face2d::FvEntity_Face2d
(
	const Label theIndex,
	const Global_Handle(FvEntity_Node2d) theNode0,
	const Global_Handle(FvEntity_Node2d) theNode1
)
	: theIndex_(theIndex)
	, theNode0_(theNode0)
	, theNode1_(theNode1)
	, theElement_(NULL)
	, thePair_(NULL)
	, theArea_((Scalar)0.0)
{
}

AutLib::FvLib::FvEntity_Face2d::~FvEntity_Face2d()
{
}

void AutLib::FvLib::FvEntity_Face2d::SetIndex(const Label theIndex)
{
	theIndex_ = theIndex;
}

void AutLib::FvLib::FvEntity_Face2d::SetNode
(
	const Label theIndex,
	const Global_Handle(FvEntity_Node2d) theNode
)
{
	(&theNode0_)[theIndex] = theNode;
}

void AutLib::FvLib::FvEntity_Face2d::SetElement(const Global_Handle(FvEntity_Element2d) theElement)
{
	theElement_ = theElement;
}

void AutLib::FvLib::FvEntity_Face2d::SetPair(const Global_Handle(FvEntity_Face2d) thePair)
{
	thePair_ = thePair;
}

void AutLib::FvLib::FvEntity_Face2d::SetCentre(const Geom_Pnt2d & theCoord)
{
	theCentre_ = theCoord;
}

void AutLib::FvLib::FvEntity_Face2d::SetNormal(const Vec2 & theVector)
{
	theNormal_ = theVector;
}

void AutLib::FvLib::FvEntity_Face2d::SetSf(const Vec2 & theVector)
{
	theSf_ = theVector;
}

void AutLib::FvLib::FvEntity_Face2d::SetLength(const Scalar theLength)
{
	theArea_ = theLength;
}

void AutLib::FvLib::FvEntity_Face2d::Setgc(const Scalar thegc)
{
	thegc_ = thegc;
}

void AutLib::FvLib::FvEntity_Face2d::SetPhysics(const FvBC_Physics thePhysics)
{
	thePhysics_ = thePhysics;
}