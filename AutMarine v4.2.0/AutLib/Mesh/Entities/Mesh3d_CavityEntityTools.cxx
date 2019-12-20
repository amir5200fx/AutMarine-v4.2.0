#include <Mesh3d_CavityEntityTools.hxx>

#include <Mesh3d_CavityEntityAllFourFronts.hxx>
#include <Mesh3d_CavityEntityAllThreeFronts.hxx>
#include <Mesh3d_CavityEntityThreeFacet.hxx>
#include <Mesh3d_CavityEntityTwoFacet.hxx>
#include <Mesh3d_CavityEntityAllFourFrontsTools.hxx>
#include <Mesh3d_CavityEntityAllThreeFrontsTools.hxx>
#include <Mesh3d_CavityEntityEdgeMoreTwoFrontFacets.hxx>
#include <Mesh3d_CavityEntityEdgeMoreTwoFrontFacetsTools.hxx>
#include <Mesh3d_CavityEntityThreeFacetTools.hxx>
#include <Mesh3d_CavityEntityTwoFacetTools.hxx>
#include <TColMesh3d_HBasicQueueOfElement.hxx>

using namespace AutLib;
using namespace MeshLib;

namespace AutLib
{
	namespace MeshLib
	{

		static inline TColMesh3d_HAry1dOfElement RetrieveElementsFrom(Global_Handle(Mesh3d_CavityEntity) theEntity)
		{
			Debug_Null_Pointer(theEntity);

			Global_Handle(Mesh3d_CavityEntityAllFourFronts) AllFourFronts = Global_DownCast(Mesh3d_CavityEntityAllFourFronts, theEntity);

			if (AllFourFronts)
			{
				return Mesh3d_CavityEntityAllFourFrontsTools::RetrieveElements(*AllFourFronts);
			}

			Global_Handle(Mesh3d_CavityEntityAllThreeFronts) AllThreeFronts = Global_DownCast(Mesh3d_CavityEntityAllThreeFronts, theEntity);

			if (AllThreeFronts)
			{
				return Mesh3d_CavityEntityAllThreeFrontsTools::RetrieveElements(*AllThreeFronts);
			}

			Global_Handle(Mesh3d_CavityEntityEdgeMoreTwoFrontFacets) EdgeMoreTwoFrontFacets = Global_DownCast(Mesh3d_CavityEntityEdgeMoreTwoFrontFacets, theEntity);

			if (EdgeMoreTwoFrontFacets)
			{
				return Mesh3d_CavityEntityEdgeMoreTwoFrontFacetsTools::RetrieveElements(*EdgeMoreTwoFrontFacets);
			}

			Global_Handle(Mesh3d_CavityEntityThreeFacet) ThreeFacet = Global_DownCast(Mesh3d_CavityEntityThreeFacet, theEntity);

			if (ThreeFacet)
			{
				TColMesh3d_HAry1dOfElement Elements(1);
				Elements[0] = Mesh3d_CavityEntityThreeFacetTools::RetrieveElement(*ThreeFacet);
				return Elements;
			}

			Global_Handle(Mesh3d_CavityEntityTwoFacet) TwoFacet = Global_DownCast(Mesh3d_CavityEntityTwoFacet, theEntity);

			if (TwoFacet)
			{
				TColMesh3d_HAry1dOfElement Elements(1);
				Elements[0] = Mesh3d_CavityEntityTwoFacetTools::RetrieveElement(*TwoFacet);
				return Elements;
			}

			THROW_STANDARD_EXCEPTION(" Not Identified Entity");
		}
	}
}

void AutLib::MeshLib::Mesh3d_CavityEntityTools::RetrieveDefiniteElementsToRemove
(
	const TColMesh3d_HAry1dOfCavityEntity & theEntities,
	TColMesh3d_HAry1dOfElement & theElements
)
{
	TColMesh3d_HBasicQueueOfElement QElements;
	forThose(Index, 0, MaxIndexOf(theEntities))
		Try_Exception_Handle_Exit(QElements.EnQueue(::RetrieveElementsFrom(theEntities[Index])));
	QElements.RetrieveTo(theElements);
}