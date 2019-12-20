#include <Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodesTools.hxx>

using namespace AutLib;
using namespace GeoLib;

TColEntity_Ary1dOfTriangleIndex AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodesTools::EquatorialTrianglesArrange(const Standard_Integer Index)
{
	if (Index < 0 OR Index > 4) { THROW_STANDARD_EXCEPTION("Bad subscription"); }

	Standard_Integer V1 = Index + 1;
	Standard_Integer V2 = V1 % 5 + 1;
	Standard_Integer V3 = V2 % 5 + 1;
	Standard_Integer V4 = V3 % 5 + 1;
	Standard_Integer V5 = V4 % 5 + 1;

	TColEntity_Ary1dOfTriangleIndex Triangles(3);
	Triangles.SetValue(0, Entity_TriangleIndex(V1, V2, V4));
	Triangles.SetValue(1, Entity_TriangleIndex(V2, V3, V4));
	Triangles.SetValue(2, Entity_TriangleIndex(V1, V4, V5));

	MOVE(Triangles);
}