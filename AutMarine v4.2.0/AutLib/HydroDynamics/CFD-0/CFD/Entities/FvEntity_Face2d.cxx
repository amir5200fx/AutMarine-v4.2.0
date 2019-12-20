#include <FvEntity_Face2d.hxx>

AutLib::FvLib::FvEntity_Face2d::FvEntity_Face2d()
{
}

AutLib::FvLib::FvEntity_Face2d::FvEntity_Face2d
(
	const Standard_Integer theIndex,
	const Global_Handle(FvEntity_Node2d) theNode0,
	const Global_Handle(FvEntity_Node2d) theNode1
)
	: theIndex_(theIndex)
	, theNode0_(theNode0)
	, theNode1_(theNode1)
{
}

AutLib::FvLib::FvEntity_Face2d::~FvEntity_Face2d()
{
}

void AutLib::FvLib::FvEntity_Face2d::SetIndex(const Standard_Integer theIndex)
{
	theIndex_ = theIndex;
}

void AutLib::FvLib::FvEntity_Face2d::SetNode
(
	const Standard_Integer theIndex, 
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

void AutLib::FvLib::FvEntity_Face2d::SetN(const Geom_Pnt2d & theN)
{
	theN_ = theN;
}

void AutLib::FvLib::FvEntity_Face2d::SetA(const Geom_Pnt2d & theA)
{
	theA_ = theA;
}

void AutLib::FvLib::FvEntity_Face2d::SetD(const Geom_Pnt2d & theD)
{
	theD_ = theD;
}

void AutLib::FvLib::FvEntity_Face2d::SetRpl(const Geom_Pnt2d & theRpl)
{
	theRpl_ = theRpl;
}

void AutLib::FvLib::FvEntity_Face2d::SetRnl(const Geom_Pnt2d & theRnl)
{
	theRnl_ = theRnl;
}

void AutLib::FvLib::FvEntity_Face2d::SetVolume(const Standard_Real theVolume)
{
	theVolume_ = theVolume;
}

void AutLib::FvLib::FvEntity_Face2d::Setd(const Standard_Real thed)
{
	thed_ = thed;
}

void AutLib::FvLib::FvEntity_Face2d::SetPhysics(const FvBC_Physics thePhysics)
{
	thePhysics_ = thePhysics;
}