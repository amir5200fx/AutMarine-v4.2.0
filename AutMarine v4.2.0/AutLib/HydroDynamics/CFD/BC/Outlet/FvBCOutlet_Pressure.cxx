#include <FvBCOutlet_Pressure.hxx>

AutLib::FvLib::FvBCOutlet_Pressure::FvBCOutlet_Pressure(const FvBCSpecification_Pressure & thePressure)
	: FvBC_Boundary(FvBC_Type_OUTLET)
	, thePressure_(thePressure)
{
}

AutLib::FvLib::FvBCOutlet_Pressure::~FvBCOutlet_Pressure()
{
}