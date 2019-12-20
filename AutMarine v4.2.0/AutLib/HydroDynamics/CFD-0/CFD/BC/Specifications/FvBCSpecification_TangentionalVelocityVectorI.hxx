#pragma once
inline
const AutLib::FvLib::FvBCSpecification_VelocityMethod & AutLib::FvLib::FvBCSpecification_TangentionalVelocityVector::Method() const
{
	return theMethod_;
}

inline 
Geom_Pnt2d AutLib::FvLib::FvBCSpecification_TangentionalVelocityVector::Value(const Geom_Pnt2d & theCoord) const
{
	return theMethod_.Value(theCoord);
}