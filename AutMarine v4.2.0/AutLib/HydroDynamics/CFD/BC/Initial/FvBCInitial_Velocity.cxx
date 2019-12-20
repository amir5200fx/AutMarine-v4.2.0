#include <FvBCInitial_Velocity.hxx>

AutLib::FvLib::FvBCInitial_Velocity::FvBCInitial_Velocity(const FvBCSpecification_VelocityMethod & theVelocity)
	: FvBC_Boundary(FvBC_Type_INITIAL_VELOCITY)
	, theVelocity_(theVelocity)
{
}

AutLib::FvLib::FvBCInitial_Velocity::~FvBCInitial_Velocity()
{
}