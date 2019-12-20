#include <FvBCWall_Velocity.hxx>

AutLib::FvLib::FvBCWall_Velocity::FvBCWall_Velocity(const FvBCSpecification_TangentionalVelocity & theVelocity)
	: FvBC_Boundary(FvBC_Type_WALL)
	, theVelocity_(theVelocity)
{
}

AutLib::FvLib::FvBCWall_Velocity::~FvBCWall_Velocity()
{
}