#include <Entity_IndexedPt3d.hxx>

AutLib::GeoLib::Entity_IndexedPt3d::Entity_IndexedPt3d()
	: theIndex_(0)
{
}

AutLib::GeoLib::Entity_IndexedPt3d::Entity_IndexedPt3d
(
	const Standard_Integer theIndex,
	const Geom_Pnt3d & theCoord
)
	: theIndex_(theIndex)
	, theCoord_(theCoord)
{
}