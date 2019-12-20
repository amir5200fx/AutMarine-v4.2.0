#include <Entity_Node2dTools.hxx>

using namespace AutLib;
using namespace GeoLib;

TColGeom_Ary1dOfPnt2d AutLib::GeoLib::Entity_Node2dTools::GetStaticOf(const TColEntity_HAry1dOfNode2d & Nodes)
{
	TColGeom_Ary1dOfPnt2d Pts(Nodes.Size());

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