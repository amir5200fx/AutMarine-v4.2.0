#include <Geom_Triangulation.hxx>

#include <TColStd_Array1OfInteger.hxx>
#include <Entity_Triangulation2d.hxx>
#include <Entity_Tetrahedralization.hxx>
#include <Merge_Pnt2d.hxx>
#include <Merge_Pnt3d.hxx>
#include <DelTri2d.hxx>
#include <DelTri3d.hxx>

static const Standard_Real MERGE_Radius = 1.0E-8;
static const Standard_Real MERGE_Resolution = 1.0E-5;

void AutLib::GeoLib::Geom_Triangulation::DelaunayTriangulation
(
	const TColGeom_Ary1dOfPnt2d & UnMerged_Coords,
	Global_Handle(Entity_Triangulation2d) Mesh
)
{
	Merge_Pnt2d Merge(MERGE_Resolution, MERGE_Radius);

	Merge.SetCoords(&UnMerged_Coords);

	Merge.Perform();
	
	TColGeom_Ary1dOfPnt2d Points = Merge.CompactPoints();

	DelTri2d Triangulation(Points);

	Triangulation.Perform();

	Mesh->Points() = Points;
	Mesh->Triangles() = Triangulation.Vertices();
}

void AutLib::GeoLib::Geom_Triangulation::DelaunayTriangulation
(
	const TColGeom_Ary1dOfPnt3d & UnMerged_Coords,
	Global_Handle(Entity_Tetrahedralization) Mesh
)
{
	//Merge_Pnt3d Merge(MERGE_Resolution, MERGE_Radius);

	//Merge.SetCoords(&UnMerged_Coords);
	//Merge.Perform();

	//TColGeom_Ary1dOfPnt3d Points = Merge.CompactPoints();

	DelTri3d Triangulation(UnMerged_Coords);
	Triangulation.Perform();

	Mesh->Points() = Triangulation.Coords();
	Mesh->Tetrahedrons() = Triangulation.Tetrahedrons();
}