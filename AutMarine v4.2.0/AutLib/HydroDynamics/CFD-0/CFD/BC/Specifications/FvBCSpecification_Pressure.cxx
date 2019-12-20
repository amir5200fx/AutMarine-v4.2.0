#include <FvBCSpecification_Pressure.hxx>

AutLib::FvLib::FvBCSpecification_Pressure::FvBCSpecification_Pressure(const FvField2d<Standard_Real>& theField)
	: theField_(theField)
{
}