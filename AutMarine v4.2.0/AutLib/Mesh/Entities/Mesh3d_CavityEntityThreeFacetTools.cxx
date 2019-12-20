#include <Mesh3d_CavityEntityThreeFacetTools.hxx>

#include <Mesh3d_Node.hxx>
#include <Mesh3d_BoundaryNode.hxx>
#include <Mesh3d_CavityEntityThreeFacet.hxx>
#include <TColMesh3d_HBasicQueueOfCavityEntity.hxx>

using namespace AutLib;
using namespace MeshLib;

Global_Handle(Mesh3d_Element) AutLib::MeshLib::Mesh3d_CavityEntityThreeFacetTools::RetrieveElement(const Mesh3d_CavityEntityThreeFacet & theEntity)
{
	return (Global_Handle(Mesh3d_Element))theEntity.Element();
}

void AutLib::MeshLib::Mesh3d_CavityEntityThreeFacetTools::IdentifyThreeFacets
(
	const TColMesh3d_HAry1dOfNode & theNodes, 
	TColMesh3d_HAry1dOfCavityEntity & theEntities
)
{
	TColMesh3d_HBasicQueueOfCavityEntity QEntity;
	forThose
	(
		Index, 
		0,
		MaxIndexOf(theNodes)
	)
	{
		Debug_Null_Pointer(theNodes[Index]);

		if (Global_DownCast(Mesh3d_BoundaryNode, theNodes[Index])) continue;

		if (theNodes[Index]->NbElements() EQUAL 1)
		{
			QEntity.EnQueue(new Mesh3d_CavityEntityThreeFacet(theNodes[Index]->RetrieveElements()[0]));
		}
	}
	QEntity.RetrieveTo(theEntities);
}