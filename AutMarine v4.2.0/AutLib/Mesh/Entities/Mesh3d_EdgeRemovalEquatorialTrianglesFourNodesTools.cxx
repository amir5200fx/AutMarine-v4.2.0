#include <Mesh3d_EdgeRemovalEquatorialTrianglesFourNodesTools.hxx>

using namespace AutLib;
using namespace GeoLib;

TColEntity_Ary1dOfTriangleIndex AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesFourNodesTools::EquatorialTrianglesArrange1()
{
	TColEntity_Ary1dOfTriangleIndex Triangles(2);

	Triangles.SetValue(0, Entity_TriangleIndex(1, 2, 3));
	Triangles.SetValue(1, Entity_TriangleIndex(1, 3, 4));
	MOVE(Triangles);
}

TColEntity_Ary1dOfTriangleIndex AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesFourNodesTools::EquatorialTrianglesArrange2()
{
	TColEntity_Ary1dOfTriangleIndex Triangles(2);

	Triangles.SetValue(0, Entity_TriangleIndex(2, 3, 4));
	Triangles.SetValue(1, Entity_TriangleIndex(2, 4, 1));
	MOVE(Triangles);
}