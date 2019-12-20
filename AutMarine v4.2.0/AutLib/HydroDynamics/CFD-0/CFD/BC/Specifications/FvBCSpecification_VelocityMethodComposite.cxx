#include <FvBCSpecification_VelocityMethodComposite.hxx>

AutLib::FvLib::FvBCSpecification_VelocityMethodComposite::FvBCSpecification_VelocityMethodComposite
(
	const FvField2d<Standard_Real>& theXComponent,
	const FvField2d<Standard_Real>& theYComponent
)
	: theXComponent_(theXComponent)
	, theYComponent_(theYComponent)
{
}