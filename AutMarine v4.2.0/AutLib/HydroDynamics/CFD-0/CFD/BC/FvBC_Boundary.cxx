#include <FvBC_Boundary.hxx>

AutLib::FvLib::FvBC_Boundary::FvBC_Boundary(const FvBC_Type theType)
	: theType_(theType)
{
}

AutLib::FvLib::FvBC_Boundary::~FvBC_Boundary()
{
}

void AutLib::FvLib::FvBC_Boundary::SetPhysics(const FvBC_Physics thePhysics)
{
	thePhysics_ = thePhysics;
}