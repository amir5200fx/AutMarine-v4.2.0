#include <Mesh3d_CavityEntityEdgeMoreTwoFrontFacetsTools.hxx>

#include <Mesh3d_Edge.hxx>
#include <Mesh3d_CavityEntityEdgeMoreTwoFrontFacets.hxx>
#include <TColMesh3d_HBasicQueueOfCavityEntity.hxx>

using namespace AutLib;
using namespace MeshLib;

TColMesh3d_HAry1dOfElement AutLib::MeshLib::Mesh3d_CavityEntityEdgeMoreTwoFrontFacetsTools::RetrieveElements(const Mesh3d_CavityEntityEdgeMoreTwoFrontFacets & theEntity)
{
	return theEntity.Edge()->RetrieveElements();
}

void AutLib::MeshLib::Mesh3d_CavityEntityEdgeMoreTwoFrontFacetsTools::IdentifyEdgeMoreTwoFrontFacets
(
	const TColMesh3d_HAry1dOfEdge & theEdges,
	TColMesh3d_HAry1dOfCavityEntity & theEntities
)
{
	TColMesh3d_HBasicQueueOfCavityEntity QEdges;
	forThose
	(
		Index,
		0, 
		MaxIndexOf(theEdges)
	)
	{
		Debug_Null_Pointer(theEdges[Index]);

		if (theEdges[Index]->NbFrontFacets() > 2)
		{
			QEdges.EnQueue(new Mesh3d_CavityEntityEdgeMoreTwoFrontFacets(theEdges[Index]));
		}
	}
	QEdges.RetrieveTo(theEntities);
}