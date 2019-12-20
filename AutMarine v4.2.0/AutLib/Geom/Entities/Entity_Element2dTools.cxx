#include <Entity_Element2dTools.hxx>

using namespace AutLib;
using namespace GeoLib;

TColEntity_Ary1dOfTriangleIndex AutLib::GeoLib::Entity_Element2dTools::GetStaticOf(const TColEntity_HAry1dOfElement2d & Elements)
{
	TColEntity_Ary1dOfTriangleIndex Triangles(Elements.Size());

	forThose(Index, 0, MaxIndexOf(Elements))
	{
		Debug_Null_Pointer(Elements[Index]);

		Triangles[Index].SetValue(Elements[Index]->Node0()->Index(), Elements[Index]->Node1()->Index(), Elements[Index]->Node2()->Index());
	}

	MOVE(Triangles);
}