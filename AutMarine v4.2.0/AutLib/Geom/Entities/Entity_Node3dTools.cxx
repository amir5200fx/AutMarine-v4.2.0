#include <Entity_Node3dTools.hxx>

using namespace AutLib;
using namespace GeoLib;

TColGeom_Ary1dOfPnt3d AutLib::GeoLib::Entity_Node3dTools::GetStaticOf(const TColEntity_HAry1dOfNode3d & Nodes)
{
	TColGeom_Ary1dOfPnt3d Pts(Nodes.Size());

	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		Debug_Null_Pointer(Nodes[Index]);

		Pts[Index] = Nodes[Index]->Coord();
	}

	MOVE(Pts);
}