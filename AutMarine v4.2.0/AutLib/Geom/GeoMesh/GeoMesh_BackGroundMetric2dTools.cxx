#include <GeoMesh_BackGroundMetric2dTools.hxx>

#include <GeoMesh_BackGroundMetric2d.hxx>
#include <Mesh2d_MetricSourcePoint.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;

void AutLib::GeoLib::GeoMesh_BackGroundMetric2dTools::SetSourcesToMesh
(
	const TColMesh2d_HAry1dOfMetricSourcePoint & theSources,
	GeoMesh_BackGroundMetric2d & theMesh,
	Entity_Metric1(*InterSection)(const Entity_Metric1&, const Entity_Metric1&)
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
	Sources.Init(Entity_Metric1(1, 0, 1));

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

		Sources[Index_Of(Element.Node0()->Index())] = InterSection(theSources[Index]->Metric(), Sources[Index_Of(Element.Node0()->Index())]);
		Sources[Index_Of(Element.Node1()->Index())] = InterSection(theSources[Index]->Metric(), Sources[Index_Of(Element.Node1()->Index())]);
		Sources[Index_Of(Element.Node2()->Index())] = InterSection(theSources[Index]->Metric(), Sources[Index_Of(Element.Node2()->Index())]);
	}
}