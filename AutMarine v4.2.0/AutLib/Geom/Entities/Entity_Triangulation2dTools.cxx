#include <Entity_Triangulation2dTools.hxx>

#include <Poly_Triangulation.hxx>
#include <Poly_Triangle.hxx>

#include <Entity_Triangulation2d.hxx>

Standard_Boolean AutLib::GeoLib::Entity_Triangulation2dTools::GetTriangulation
(
	const Poly_Triangulation & thePoly,
	Entity_Triangulation2d & theTriangulation
)
{
	if (NOT thePoly.HasUVNodes()) { return Standard_False; }

	Get_Object(Coords) = theTriangulation.Points();
	Get_Object(Triangles) = theTriangulation.Triangles();

	Coords.Resize(thePoly.NbNodes());
	Triangles.Resize(thePoly.NbTriangles());

	forThose(Index, 0, MaxIndexOf(Coords))
		Coords[Index] = thePoly.UVNode(Index + 1);

	forThose
	(
		Index,
		0, 
		MaxIndexOf(Triangles)
	)
	{
		Standard_Integer V1, V2, V3;
		
		Get_Const_Object(Triangle) = thePoly.Triangle(Index + 1);
		Triangle.Get(V1, V2, V3);

		Triangles[Index].SetValue(V1, V2, V3);
	}

	return Standard_True;
}