#include <Cad2d_PointOnPlaneTools.hxx>

using namespace AutLib;

TColGeom_Ary1dOfPnt2d AutLib::CadLib::Cad2d_PointOnPlaneTools::GetCoordsOf(const TColCad2d_HAry1dOfPointOnPlane & thePoints)
{
	TColGeom_Ary1dOfPnt2d Coords(thePoints.Size());
	forThose
	(
		Index, 
		0,
		MaxIndexOf(thePoints)
	)
	{
		Debug_Null_Pointer(thePoints[Index]);
		Coords[Index] = thePoints[Index]->Coord();
	}
	MOVE(Coords);
}