#pragma once
inline
const AutLib::FvLib::FvBCSpecification_FlowDirection & AutLib::FvLib::FvBCSpecification_VelocityMagnitudeDirection::Direction() const
{
	return theDirection_;
}

inline 
Scalar AutLib::FvLib::FvBCSpecification_VelocityMagnitudeDirection::Magnitude(const Geom_Pnt2d & theCoord) const
{
	return theField_.Value(theCoord);
}