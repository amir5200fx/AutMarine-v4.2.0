#pragma once
inline
Vec2 AutLib::FvLib::FvBCSpecification_VelocityMethodConst::Value(const Geom_Pnt2d & theCoord) const
{
	return theField_;
}