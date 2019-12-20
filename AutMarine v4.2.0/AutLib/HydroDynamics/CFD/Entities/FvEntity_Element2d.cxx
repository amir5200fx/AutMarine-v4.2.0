#include <FvEntity_Element2d.hxx>

AutLib::FvLib::FvEntity_Element2d::FvEntity_Element2d()
{
}

AutLib::FvLib::FvEntity_Element2d::FvEntity_Element2d(const Label theIndex)
	: theIndex_(theIndex)
{
}

void AutLib::FvLib::FvEntity_Element2d::SetIndex(const Label theIndex)
{
	theIndex_ = theIndex;
}

void AutLib::FvLib::FvEntity_Element2d::SetVolume(const Scalar theValue)
{
	theVolume_ = theValue;
}

void AutLib::FvLib::FvEntity_Element2d::SetPhysics(const FvBC_Physics thePhysics)
{
	thePhysics_ = thePhysics;
}

void AutLib::FvLib::FvEntity_Element2d::SetCentre(const Geom_Pnt2d & theCoord)
{
	theCentre_ = theCoord;
}