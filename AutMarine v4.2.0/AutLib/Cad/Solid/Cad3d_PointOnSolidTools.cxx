#include <Cad3d_PointOnSolidTools.hxx>

#include <Cad3d_PointOnSolid.hxx>

using namespace AutLib;
using namespace CadLib;

TColGeom_Ary1dOfPnt3d AutLib::CadLib::Cad3d_PointOnSolidTools::GetStaticCoordsOf(const TColCad3d_HAry1dOfPointOnSolid & PointsOnSolid)
{
	TColGeom_Ary1dOfPnt3d Coords(PointsOnSolid.Size());
	forThose(Index, 0, MaxIndexOf(PointsOnSolid))
	{
		Coords.SetValue(Index, PointsOnSolid.Value(Index)->Coord());
	}
	MOVE(Coords);
}

void AutLib::CadLib::Cad3d_PointOnSolidTools::GetStaticCoordsOf
(
	const TColCad3d_HAry1dOfPointOnSolid & PointsOnSolid,
	TColGeom_Ary1dOfPnt3d & Coords
)
{
	Coords.Resize(PointsOnSolid.Size());
	forThose(Index, 0, MaxIndexOf(PointsOnSolid))
	{
		Coords.SetValue(Index, PointsOnSolid.Value(Index)->Coord());
	}
}