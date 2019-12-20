#include <FvBCInlet_Velocity.hxx>

AutLib::FvLib::FvBCInlet_Velocity::FvBCInlet_Velocity(const FvBCSpecification_Velocity & theVelocity)
	: FvBC_Boundary(FvBC_Type_INLET)
	, theVelocity_(theVelocity)
{
}

AutLib::FvLib::FvBCInlet_Velocity::~FvBCInlet_Velocity()
{
}