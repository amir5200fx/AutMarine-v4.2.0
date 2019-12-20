#include <FvBCSpecification_VelocityMethodFieldFunction.hxx>

AutLib::FvLib::FvBCSpecification_VelocityMethodFieldFunction::FvBCSpecification_VelocityMethodFieldFunction(const FvField2d<Geom_Pnt2d>& theField)
	: theField_(theField)
{
}