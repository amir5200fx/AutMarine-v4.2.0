#include <Mesh3d_CavityEntityAllThreeFrontsTools.hxx>

#include <Mesh3d_Node.hxx>
#include <Mesh3d_CavityEntityAllThreeFronts.hxx>
#include <TColMesh3d_HBasicQueueOfCavityEntity.hxx>

using namespace AutLib;
using namespace MeshLib;

TColMesh3d_HAry1dOfElement AutLib::MeshLib::Mesh3d_CavityEntityAllThreeFrontsTools::RetrieveElements(const Mesh3d_CavityEntityAllThreeFronts & theEntity)
{
	return theEntity.Apex()->RetrieveElements();
}

void AutLib::MeshLib::Mesh3d_CavityEntityAllThreeFrontsTools::IdentifyAllThreeFronts
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

		Get_Const_Object(Node) = *theNodes[Index];

		if (Node.NbElements() EQUAL 3 AND Node.NbFrontFacets() EQUAL 3 AND Node.NbFrontEdges() EQUAL 3)
		{
			QEntity.EnQueue(new Mesh3d_CavityEntityAllThreeFronts(theNodes[Index]));
		}
	}
	QEntity.RetrieveTo(theEntities);
}