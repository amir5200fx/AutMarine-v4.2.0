#include <Entity_Element3dTools.hxx>

using namespace AutLib;
using namespace GeoLib;

TColEntity_Ary1dOfTetrahedronIndex AutLib::GeoLib::Entity_Element3dTools::GetStaticOf(const TColEntity_HAry1dOfElement3d & Elements)
{
	TColEntity_Ary1dOfTetrahedronIndex Triangles(Elements.Size());

	forThose(Index, 0, MaxIndexOf(Elements))
	{
		Debug_Null_Pointer(Elements[Index]);

		Triangles[Index].SetValue
		(
			Elements[Index]->Node0()->Index(),
			Elements[Index]->Node1()->Index(),
			Elements[Index]->Node2()->Index(),
			Elements[Index]->Node3()->Index()
		);
	}

	MOVE(Triangles);
}