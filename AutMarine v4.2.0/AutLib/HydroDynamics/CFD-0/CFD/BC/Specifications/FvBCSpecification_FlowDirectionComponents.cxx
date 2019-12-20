#include <FvBCSpecification_FlowDirectionComponents.hxx>

AutLib::FvLib::FvBCSpecification_FlowDirectionComponents::FvBCSpecification_FlowDirectionComponents(const FvField2d<Geom_Pnt2d>& theField)
	: theField_(theField)
{
}

AutLib::FvLib::FvBCSpecification_FlowDirectionComponents::~FvBCSpecification_FlowDirectionComponents()
{
}