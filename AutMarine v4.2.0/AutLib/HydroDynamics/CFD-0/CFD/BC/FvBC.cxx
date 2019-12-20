#include <FvBC.hxx>

AutLib::FvLib::FvBC::FvBC()
{
}

void AutLib::FvLib::FvBC::InsertBoundary(const Global_Handle(FvBC_Boundary) theBoundary)
{
	theBoundaries_.EnQueue((Global_Handle(FvBC_Boundary))theBoundary);
}