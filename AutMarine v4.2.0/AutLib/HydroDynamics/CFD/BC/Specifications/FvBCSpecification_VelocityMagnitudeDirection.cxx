#include <FvBCSpecification_VelocityMagnitudeDirection.hxx>

AutLib::FvLib::FvBCSpecification_VelocityMagnitudeDirection::FvBCSpecification_VelocityMagnitudeDirection
(
	const FvField2d_Scalar& theField,
	const FvBCSpecification_FlowDirection & theDirection
)
	: theField_(theField)
	, theDirection_(theDirection)
{
}

AutLib::FvLib::FvBCSpecification_VelocityMagnitudeDirection::~FvBCSpecification_VelocityMagnitudeDirection()
{
}