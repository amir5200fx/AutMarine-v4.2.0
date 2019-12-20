#pragma once
inline
Vec2 AutLib::FvLib::FvBCSpecification_FlowDirectionComponents::Direction(const Geom_Pnt2d & theCoord) const
{
	return theField_.Value(theCoord);
}