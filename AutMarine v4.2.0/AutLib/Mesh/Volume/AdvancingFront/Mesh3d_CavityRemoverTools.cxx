#include <Mesh3d_CavityRemoverTools.hxx>

#include <Geometry_Tools.hxx>
#include <Mesh3d_Node.hxx>
#include <Mesh3d_Edge.hxx>
#include <Mesh3d_Facet.hxx>
#include <Mesh3d_Element.hxx>
#include <Mesh3d_ElementTools.hxx>
#include <Mesh3d_FacetTools.hxx>
#include <Mesh3d_CavityShellTools.hxx>
#include <Mesh3d_CavityEntityTools.hxx>
#include <Mesh3d_CavityEntityThreeFacetTools.hxx>
#include <Mesh3d_CavityEntityTwoFacetTools.hxx>
#include <Mesh3d_CavityEntityAllFourFrontsTools.hxx>
#include <Mesh3d_CavityEntityAllThreeFrontsTools.hxx>
#include <Mesh3d_CavityEntityEdgeMoreTwoFrontFacetsTools.hxx>
#include <TColMesh3d_HAry1dOfNode.hxx>
#include <TColMesh3d_HAry1dOfEdge.hxx>
#include <TColMesh3d_HAry1dOfCavityEntity.hxx>
#include <TColMesh3d_HAvlTreeOfElement.hxx>

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityRemoverTools::IsValidToFlip(const Mesh3d_Facet & theFacet)
{
	if (NOT Mesh3d_FacetTools::IsGoodToFlip(theFacet)) { return Standard_False; }

	Debug_Null_Pointer(theFacet.LeftElement());
	Debug_Null_Pointer(theFacet.RightElement());

	Get_Const_Object(LeftElement) = *theFacet.LeftElement();
	Get_Const_Object(RightElement) = *theFacet.RightElement();

	Global_Handle(Mesh3d_Node) LeftVertex = LeftElement.OppositeVertex(&theFacet);
	Global_Handle(Mesh3d_Node) RightVertex = RightElement.OppositeVertex(&theFacet);

	Debug_Null_Pointer(LeftVertex);
	Debug_Null_Pointer(RightVertex);

	Get_Const_Object(P0) = theFacet.Node0()->Coord();
	Get_Const_Object(P1) = theFacet.Node1()->Coord();
	Get_Const_Object(P2) = theFacet.Node2()->Coord();

	if (Geometry_Tools::VolumeOfTetrahedron(P0, P1, P2, LeftVertex->Coord()) < EPS6) { return Standard_False; }
	if (Geometry_Tools::VolumeOfTetrahedron(P0, P2, P1, RightVertex->Coord()) < EPS6) { return Standard_False; }

	return Standard_True;
}

void AutLib::MeshLib::Mesh3d_CavityRemoverTools::DefiniteElementsToRemove
(
	const TColMesh3d_HAry1dOfFacet & theFacets,
	TColMesh3d_HAry1dOfElement & theElements,
	const Standard_Boolean theThreeEntities,
	const Standard_Boolean theFourEntities
)
{
	TColMesh3d_HAry1dOfNode FrontNodes;
	Mesh3d_FacetTools::RetrieveNodes(theFacets, FrontNodes);

	TColMesh3d_HAry1dOfEdge FrontEdges;
	Mesh3d_FacetTools::RetrieveEdges(theFacets, FrontEdges);

	//! Detect three facets entities
	TColMesh3d_HAry1dOfCavityEntity ThreeFacetsEntities;
	Mesh3d_CavityEntityThreeFacetTools::IdentifyThreeFacets(FrontNodes, ThreeFacetsEntities);	

	TColMesh3d_HAry1dOfElement ThreeFacetsElements;
	if (ThreeFacetsEntities.Size()) { Mesh3d_CavityEntityTools::RetrieveDefiniteElementsToRemove(ThreeFacetsEntities, ThreeFacetsElements); }

	//! Detect Two facets entities
	TColMesh3d_HAry1dOfCavityEntity TwoFacetsEntities;
	Mesh3d_CavityEntityTwoFacetTools::IdentifyTwoFacets(FrontEdges, TwoFacetsEntities);

	TColMesh3d_HAry1dOfElement TwoFacetsElements;
	if (TwoFacetsEntities.Size()) { Mesh3d_CavityEntityTools::RetrieveDefiniteElementsToRemove(TwoFacetsEntities, TwoFacetsElements); }

	//! Detect entities that have four edges, four facets and four elements around.
	TColMesh3d_HAry1dOfCavityEntity AllFourFrontsEntities;
	if (theFourEntities) { Mesh3d_CavityEntityAllFourFrontsTools::IdentifyAllFourFronts(FrontNodes, AllFourFrontsEntities); }

	TColMesh3d_HAry1dOfElement AllFourFrontsElements;
	if (AllFourFrontsEntities.Size()) { Mesh3d_CavityEntityTools::RetrieveDefiniteElementsToRemove(AllFourFrontsEntities, AllFourFrontsElements); }

	//! Detect entities that have three edges, three facets and three elements around.
	TColMesh3d_HAry1dOfCavityEntity AllThreeFrontsEntities;
	if (theThreeEntities) { Mesh3d_CavityEntityAllThreeFrontsTools::IdentifyAllThreeFronts(FrontNodes, AllThreeFrontsEntities); }

	TColMesh3d_HAry1dOfElement AllThreeFrontsElements;
	if (AllThreeFrontsEntities.Size()) { Mesh3d_CavityEntityTools::RetrieveDefiniteElementsToRemove(AllThreeFrontsEntities, AllThreeFrontsElements); }

	//! Detect entities that have more than two front facet
	TColMesh3d_HAry1dOfCavityEntity EdgeMoreTwoFrontFacetsEntities;
	Mesh3d_CavityEntityEdgeMoreTwoFrontFacetsTools::IdentifyEdgeMoreTwoFrontFacets(FrontEdges, EdgeMoreTwoFrontFacetsEntities);

	TColMesh3d_HAry1dOfElement EdgeMoreTwoFrontFacetsElements;
	if (EdgeMoreTwoFrontFacetsEntities.Size()) { Mesh3d_CavityEntityTools::RetrieveDefiniteElementsToRemove(EdgeMoreTwoFrontFacetsEntities, EdgeMoreTwoFrontFacetsElements); }

	TColMesh3d_HAvlTreeOfElement Compact;
	Set_Numbering(Compact, Mesh3d_ElementTools::IsLess);

	if (ThreeFacetsElements.Size()) { Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(ThreeFacetsElements)); }
	if (TwoFacetsElements.Size()) { Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(TwoFacetsElements)); }
	if (AllFourFrontsElements.Size()) { Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(AllFourFrontsElements)); }
	if (AllThreeFrontsElements.Size()) { Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(AllThreeFrontsElements)); }
	if (EdgeMoreTwoFrontFacetsElements.Size()) { Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(EdgeMoreTwoFrontFacetsElements)); }

	Compact.RetrieveTo(theElements);
}

void AutLib::MeshLib::Mesh3d_CavityRemoverTools::CreateCavityShells
(
	const TColMesh3d_HAry1dOfFacet & theFacets, 
	TColMesh3d_HAry1dOfCavityShell & theShells
)
{
	Mesh3d_CavityShellTools::IdentifyShells(theFacets, theShells);
}