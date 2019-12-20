#pragma once
inline
Vec2 AutLib::FvLib::FvBodyForce2d_Free::Value(const Geom_Pnt2d & theCoord) const
{
	return Vec2(0, 0);
}