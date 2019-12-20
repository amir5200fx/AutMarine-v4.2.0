#include <GeoMesh_BackGroundMesh3dTools.hxx>

#include <Mesh3d_SourcePoint.hxx>
#include <GeoMesh_BackGroundMesh3d.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;

void AutLib::GeoLib::GeoMesh_BackGroundMesh3dTools::SetSourcesToMesh(const TColMesh3d_HAry1dOfSourcePoint & theSources, const Standard_Real theBaseSize, GeoMesh_BackGroundMesh3d & theMesh)
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
	const Global_Handle(Entity_Element3d) Start = Elements.First();

	forThose
	(
		Index,
		0,
		MaxIndexOf(theSources)
	)
	{
		Get_Const_Object(Coord) = theSources[Index]->Coord();

		const Global_Handle(Entity_Element3d) Current = Mesh.TetrahedronLocation((Global_Handle(Entity_Element3d))Start, Coord);

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
		Sources[Index_Of(Element.Node3()->Index())] = MIN(Sources[Index_Of(Element.Node3()->Index())], theSources[Index]->Value());
	}
}