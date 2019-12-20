#include <FvParameters_ConstTimeStep.hxx>

#include <FvParameters_TimeConfigInfo.hxx>

AutLib::FvLib::FvParameters_ConstTimeStep::FvParameters_ConstTimeStep()
	: theStep_(FvParameters_TimeConfigInfo::Step())
{
}

AutLib::FvLib::FvParameters_ConstTimeStep::~FvParameters_ConstTimeStep()
{
}

void AutLib::FvLib::FvParameters_ConstTimeStep::SetStep(const Scalar theValue)
{
	theStep_ = theValue;
}