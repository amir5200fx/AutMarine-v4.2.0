#pragma once
inline
Scalar AutLib::FvLib::FvBCSpecification_Pressure::Value(const Geom_Pnt2d & theCoord) const
{
	return theField_.Value(theCoord);
}