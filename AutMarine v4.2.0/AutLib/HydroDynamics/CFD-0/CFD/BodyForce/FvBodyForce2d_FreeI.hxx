#pragma once
inline
Geom_Pnt2d AutLib::FvLib::FvBodyForce2d_Free::Value(const Geom_Pnt2d & theCoord) const
{
	return Geom_Pnt2d(0, 0);
}