#include <Cad3d_PointOnSolid.hxx>

#include <Cad3d_EdgeOnSolidTools.hxx>
#include <Cad3d_SurfaceOnSolidTools.hxx>

AutLib::CadLib::Cad3d_PointOnSolid::Cad3d_PointOnSolid()
{
	theEdges_.SetComparable(Cad3d_EdgeOnSolidTools::IsLess);
	theSurfaces_.SetComparable(Cad3d_SurfaceOnSolidTools::IsLess);

	theEdges_.SetName("Cad3d_PointOnSolid the Edges tree");
	theSurfaces_.SetName("Cad3d_PointOnSolid the Surfaces tree");
}

AutLib::CadLib::Cad3d_PointOnSolid::Cad3d_PointOnSolid
(
	const Standard_Integer Index,
	const Geom_Pnt3d & Coord
)
	: Cad3d_EntityOnSolid(Index)
	, theCoord_(Coord)
{
	theEdges_.SetComparable(Cad3d_EdgeOnSolidTools::IsLess);
	theSurfaces_.SetComparable(Cad3d_SurfaceOnSolidTools::IsLess);

	theEdges_.SetName("Cad3d_PointOnSolid the Edges tree");
	theSurfaces_.SetName("Cad3d_PointOnSolid the Surfaces tree");
}

AutLib::CadLib::Cad3d_PointOnSolid::~Cad3d_PointOnSolid()
{
}

void AutLib::CadLib::Cad3d_PointOnSolid::SetCoord(const Geom_Pnt3d & Coord)
{
	theCoord_ = Coord;
}
