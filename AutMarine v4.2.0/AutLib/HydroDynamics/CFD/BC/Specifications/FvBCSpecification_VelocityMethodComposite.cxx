#include <FvBCSpecification_VelocityMethodComposite.hxx>

AutLib::FvLib::FvBCSpecification_VelocityMethodComposite::FvBCSpecification_VelocityMethodComposite
(
	const FvField2d_Scalar& theXComponent,
	const FvField2d_Scalar& theYComponent
)
	: theXComponent_(theXComponent)
	, theYComponent_(theYComponent)
{
}