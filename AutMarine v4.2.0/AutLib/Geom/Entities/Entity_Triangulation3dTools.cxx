#include <Entity_Triangulation3dTools.hxx>

#include <Entity_Triangulation3d.hxx>

using namespace AutLib;
using namespace GeoLib;

#include <Poly_Triangulation.hxx>

void AutLib::GeoLib::Entity_Triangulation3dTools::GetTriangulation
(
	const Handle(Poly_Triangulation)& thePoly,
	Entity_Triangulation3d & theTriangulation
)
{
	Get_Object(Coords) = theTriangulation.Points();
	Get_Object(Triangles) = theTriangulation.Triangles();

	Coords.Resize(thePoly->NbNodes());
	Triangles.Resize(thePoly->NbTriangles());

	forThose(Index, 0, MaxIndexOf(Coords))
		Coords.SetValue(Index, thePoly->Node(Index + 1));

	Standard_Integer V1, V2, V3;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Triangles)
	)
	{
		Get_Const_Object(Triangle) = thePoly->Triangle(Index + 1);
		Triangle.Get(V1, V2, V3);
		Triangles.SetValue(Index, Entity_TriangleIndex(V1, V2, V3));
	}
}