#pragma once
inline
Vec2 AutLib::FvLib::FvBCSpecification_VelocityComponents::Value(const Geom_Pnt2d & theCoord) const
{
	return theMethod_.Value(theCoord);
}