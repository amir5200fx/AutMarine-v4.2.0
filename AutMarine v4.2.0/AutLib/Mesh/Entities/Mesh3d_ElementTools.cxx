#include <Mesh3d_ElementTools.hxx>

M_AUT TColEntity_Ary1dOfTetrahedronIndex AutLib::MeshLib::Mesh3d_ElementTools::StaticOf(const TColMesh3d_HAry1dOfElement & Elements)
{
	TColEntity_Ary1dOfTetrahedronIndex Statics(Elements.Size());

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
			Element.Node(2)->Index(),
			Element.Node(3)->Index()
		);
	}

	MOVE(Statics);
}