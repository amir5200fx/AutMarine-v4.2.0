#include <Mesh3d_CavityEntityTwoFacetTools.hxx>

#include <Mesh3d_Edge.hxx>
#include <Mesh3d_BoundaryEdge.hxx>
#include <Mesh3d_CavityEntityTools.hxx>
#include <Mesh3d_CavityEntityTwoFacet.hxx>
#include <TColMesh3d_HAvlTreeOfCavityEntity.hxx>

using namespace AutLib;
using namespace MeshLib;

Global_Handle(Mesh3d_Element) AutLib::MeshLib::Mesh3d_CavityEntityTwoFacetTools::RetrieveElement(const Mesh3d_CavityEntityTwoFacet & theEntity)
{
	return (Global_Handle(Mesh3d_Element))theEntity.Element();
}

void AutLib::MeshLib::Mesh3d_CavityEntityTwoFacetTools::IdentifyTwoFacets
(
	const TColMesh3d_HAry1dOfEdge & theEdges,
	TColMesh3d_HAry1dOfCavityEntity & theEntities
)
{
	TColMesh3d_HAvlTreeOfCavityEntity Compact;
	Set_Numbering(Compact, Mesh3d_CavityEntityTools::IsLess);

	Standard_Integer K = 0;
	forThose
	(
		Index,
		0, 
		MaxIndexOf(theEdges)
	)
	{
		Debug_Null_Pointer(theEdges[Index]);

		if (Global_DownCast(Mesh3d_BoundaryEdge, theEdges[Index])) continue;

		if (theEdges[Index]->NbElements() EQUAL 1 AND theEdges[Index]->NbFrontFacets() EQUAL 2)
		{
			Global_Handle(Mesh3d_CavityEntityTwoFacet) newEntity = new Mesh3d_CavityEntityTwoFacet(theEdges[Index]->RetrieveElements()[0]);
			newEntity->SetIndex(++K);

			Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(newEntity));
		}
	}
	Compact.RetrieveTo(theEntities);
}