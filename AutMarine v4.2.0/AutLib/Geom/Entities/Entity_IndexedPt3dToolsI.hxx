#pragma once
inline
const Geom_Pnt3d& AutLib::GeoLib::Entity_IndexedPt3dTools::CoordOf(Global_Handle(Entity_IndexedPt3d) thePoint)
{
	return thePoint->Coord();
}