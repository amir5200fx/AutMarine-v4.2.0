#include <FvBCInitial_Pressure.hxx>

AutLib::FvLib::FvBCInitial_Pressure::FvBCInitial_Pressure(const FvBCSpecification_Pressure & thePressure)
	: FvBC_Boundary(FvBC_Type_INITIAL_PRESSURE)
	, thePressure_(thePressure)
{
}

AutLib::FvLib::FvBCInitial_Pressure::~FvBCInitial_Pressure()
{
}