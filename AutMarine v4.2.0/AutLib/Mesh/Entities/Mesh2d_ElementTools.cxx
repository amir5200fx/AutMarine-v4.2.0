#include <Mesh2d_ElementTools.hxx>

using namespace AutLib;

TColEntity_Ary1dOfTriangleIndex AutLib::MeshLib::Mesh2d_ElementTools::StaticOf(const TColMesh2d_HAry1dOfElement & Elements)
{
	TColEntity_Ary1dOfTriangleIndex Statics(Elements.Size());
	forThose
	(
		Index,
		0,
		MaxIndexOf(Statics)
	)
	{
		Debug_Null_Pointer(Elements[Index]);

		Get_Const_Object(Element) = *Elements[Index];

		Statics[Index].SetValue
		(
			Element.Node(0)->Index(),
			Element.Node(1)->Index(),
			Element.Node(2)->Index()
		);
	}
	MOVE(Statics);
}