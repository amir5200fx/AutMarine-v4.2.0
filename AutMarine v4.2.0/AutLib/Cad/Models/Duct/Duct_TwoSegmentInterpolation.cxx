#include <Duct_TwoSegmentInterpolation.hxx>

#include <Duct_ConstParameters.hxx>

AutLib::CadLib::Duct_TwoSegmentInterpolation::Duct_TwoSegmentInterpolation()
{
}

void AutLib::CadLib::Duct_TwoSegmentInterpolation::SetMidOffset(const Standard_Real theValue)
{
	Set_DuctParameterValue(theValue, 0, 1, theMidOffset_);
}

void AutLib::CadLib::Duct_TwoSegmentInterpolation::SetMidWidth(const Standard_Real theValue)
{
	Set_DuctParameterValue(theValue, 0, 1, theMidWidth_);
}

void AutLib::CadLib::Duct_TwoSegmentInterpolation::SetInletOffset(const Standard_Real theValue)
{
	Set_DuctParameterValue(theValue, 0, 1, theInletOffset_);
}

void AutLib::CadLib::Duct_TwoSegmentInterpolation::SetOutletOffset(const Standard_Real theValue)
{
	Set_DuctParameterValue(theValue, 0, 1, theOutletOffset_);
}

void AutLib::CadLib::Duct_TwoSegmentInterpolation::SetLeftTurningPosition(const Standard_Real theValue)
{
	Set_DuctParameterValue(theValue, 0, 1, theLeftTurningPosition_);
}

void AutLib::CadLib::Duct_TwoSegmentInterpolation::SetLeftTurningWidth(const Standard_Real theValue)
{
	Set_DuctParameterValue(theValue, 0, 1, theLeftTurningWidth_);
}

void AutLib::CadLib::Duct_TwoSegmentInterpolation::SetRightTurningPosition(const Standard_Real theValue)
{
	Set_DuctParameterValue(theValue, 0, 1, theRightTurningPosition_);
}

void AutLib::CadLib::Duct_TwoSegmentInterpolation::SetRightTurningWidth(const Standard_Real theValue)
{
	Set_DuctParameterValue(theValue, 0, 1, theRightTurningWidth_);
}

void AutLib::CadLib::Duct_TwoSegmentInterpolation::SetInletRiseWeight(const Standard_Real theValue)
{
	Set_DuctParameterValue(theValue, 0, 1, theInletRiseWeight_);
}

void AutLib::CadLib::Duct_TwoSegmentInterpolation::SetOutletRiseWeight(const Standard_Real theValue)
{
	Set_DuctParameterValue(theValue, 0, 1, theOutletRiseWeight_);
}

void AutLib::CadLib::Duct_TwoSegmentInterpolation::SetInletWeight(const Standard_Real theValue)
{
	Set_DuctParameterValue(theValue, 0, 1, theInletWeight_);
}

void AutLib::CadLib::Duct_TwoSegmentInterpolation::SetOutletWeight(const Standard_Real theValue)
{
	Set_DuctParameterValue(theValue, 0, 1, theOutletWeight_);
}