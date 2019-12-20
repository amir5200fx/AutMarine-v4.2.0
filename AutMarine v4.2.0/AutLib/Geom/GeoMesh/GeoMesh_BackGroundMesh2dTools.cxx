#include <GeoMesh_BackGroundMesh2dTools.hxx>

#include <Entity_Triangulation2d.hxx>
#include <GeoMesh_TriangleMesh2d.hxx>
#include <GeoMesh_BackGroundMesh2d.hxx>
#include <Mesh2d_SourcePoint.hxx>

using namespace AutLib;
using namespace GeoLib;

Global_Handle(GeoMesh_BackGroundMesh2d) AutLib::GeoLib::GeoMesh_BackGroundMesh2dTools::ReadBackMeshFrom
(
	fstream & File, 
	GeoMesh_TriangleMesh2d & theTriangleMesh
)
{
	Standard_String String;

	Standard_Integer NbPoints, NbElements;
	Standard_Integer K;

	File
		>> String
		>> NbPoints;

	File
		>> String
		>> NbElements;

	Entity_Triangulation2d Triangulation;
	Get_Object(Coords) = Triangulation.Points();
	Get_Object(Triangles) = Triangulation.Triangles();

	Coords.Resize(NbPoints);
	Triangles.Resize(NbElements);

	TColStd_Ary1dOfReal Sources(NbPoints);
	Sources.Init(0);

	forThose(Index, 0, MaxIndexOf(Coords))
		File >> K >> Coords[Index] >> Sources[Index];

	forThose(Index, 0, MaxIndexOf(Triangles))
		File >> K >> Triangles[Index];

	theTriangleMesh.Construct(Triangulation);

	Global_Handle(GeoMesh_BackGroundMesh2d) BackGround = new GeoMesh_BackGroundMesh2d(theTriangleMesh);
	BackGround->Sources() = Sources;

	return BackGround;
}

Global_Handle(GeoMesh_BackGroundMesh2d) AutLib::GeoLib::GeoMesh_BackGroundMesh2dTools::ReadBackMeshFrom(fstream & File)
{
	Standard_String String;

	Standard_Integer NbPoints, NbElements;
	Standard_Integer K;
	Standard_Real BaseSize;

	File
		>> String
		>> NbPoints;

	File
		>> String
		>> NbElements;

	File
		>> String
		>> BaseSize;

	Entity_Triangulation2d Triangulation;
	Get_Object(Coords) = Triangulation.Points();
	Get_Object(Triangles) = Triangulation.Triangles();

	Coords.Resize(NbPoints);
	Triangles.Resize(NbElements);

	TColStd_Ary1dOfReal Sources(NbPoints);
	Sources.Init(0);

	forThose(Index, 0, MaxIndexOf(Coords))
		File >> K >> Coords[Index] >> Sources[Index];

	forThose(Index, 0, MaxIndexOf(Triangles))
		File >> K >> Triangles[Index];

	Global_Handle(GeoMesh_BackGroundMesh2d) BackGround = new GeoMesh_BackGroundMesh2d;

	BackGround->Mesh().Construct(Triangulation);
	BackGround->Sources() = Sources*BaseSize;
	BackGround->InitiateCurrentElement();

	return BackGround;
}

void AutLib::GeoLib::GeoMesh_BackGroundMesh2dTools::SetSourcesToMesh
(
	const TColMesh2d_HAry1dOfSourcePoint & theSources,
	const Standard_Real theBaseSize,
	GeoMesh_BackGroundMesh2d & theMesh
)
{
	Get_Const_Object(Mesh) = theMesh.Mesh();

	if (NOT Mesh.NbElements())
	{
		THROW_STANDARD_EXCEPTION(" Not found any background mesh");
		return;
	}

	Get_Object(Sources) = theMesh.Sources();

	Sources.Resize(Mesh.NbNodes());
	Sources.Init(theBaseSize);

	Get_Const_Object(Elements) = Mesh.ElementsSequence();
	const Global_Handle(Entity_Element2d) Start = Elements.First();

	forThose
	(
		Index,
		0,
		MaxIndexOf(theSources)
	)
	{
		Get_Const_Object(Coord) = theSources[Index]->Coord();

		const Global_Handle(Entity_Element2d) Current = Mesh.TriangleLocation((Global_Handle(Entity_Element2d))Start, Coord);

		if (NOT Current)
		{
			THROW_STANDARD_EXCEPTION(" the Point is not inside the Mesh");
			return;
		}

		Start = Current;

		Get_Const_Object(Element) = *Current;

		Sources[Index_Of(Element.Node0()->Index())] = MIN(Sources[Index_Of(Element.Node0()->Index())], theSources[Index]->Value());
		Sources[Index_Of(Element.Node1()->Index())] = MIN(Sources[Index_Of(Element.Node1()->Index())], theSources[Index]->Value());
		Sources[Index_Of(Element.Node2()->Index())] = MIN(Sources[Index_Of(Element.Node2()->Index())], theSources[Index]->Value());
	}
}