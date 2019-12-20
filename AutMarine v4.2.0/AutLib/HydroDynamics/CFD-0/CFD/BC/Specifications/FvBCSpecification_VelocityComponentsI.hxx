#pragma once
inline
Geom_Pnt2d AutLib::FvLib::FvBCSpecification_VelocityComponents::Value(const Geom_Pnt2d & theCoord) const
{
	return theMethod_.Value(theCoord);
}