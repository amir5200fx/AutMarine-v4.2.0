#pragma once
#ifndef _Mesh3d_FacetTools_Header
#define _Mesh3d_FacetTools_Header

#include <Mesh3d_Facet.hxx>
#include <Entity_TriangleIndex.hxx>
#include <TColEntity_Ary1dOfTriangleIndex.hxx>
#include <TColMesh3d_HAry1dOfFacet.hxx>
#include <TColMesh3d_HAry1dOfEdge.hxx>
#include <TColMesh3d_HAry1dOfNode.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_StaticChain3d;
	}

	namespace MeshLib
	{
		
		class Mesh3d_FacetTools
		{

		public:

			static M_GEO Entity_TriangleIndex StaticOf(const Mesh3d_Facet& Facet);

			static TColEntity_Ary1dOfTriangleIndex StaticOf(const TColMesh3d_HAry1dOfFacet& Facets);

			static Standard_Boolean IsLess(Global_Handle(Mesh3d_Facet) const &Facet1, Global_Handle(Mesh3d_Facet) const &Facet2);

			static Standard_Boolean IsGoodToFlip(const Mesh3d_Facet& theFacet);

			static Standard_Boolean CheckFront(const TColMesh3d_HAry1dOfFacet & theFacet);

			static Standard_Real AreaOf(Global_Handle(Mesh3d_Facet) const & Facet);

			Global_Handle(Mesh3d_Facet) GetCommonFrontFacetOf(const Mesh3d_Node& theNode0, const Mesh3d_Node& theNode1, const Mesh3d_Node& theNode2);

			static TColMesh3d_HAry1dOfNode RetrieveNodesFrom(const TColMesh3d_HAry1dOfFacet& theFacets);

			static TColMesh3d_HAry1dOfEdge RetrieveEdgesFrom(const TColMesh3d_HAry1dOfFacet& theFacets);

			static void RetrieveNodes(const TColMesh3d_HAry1dOfFacet& theFacets, TColMesh3d_HAry1dOfNode& theNodes);

			static void RetrieveEdges(const TColMesh3d_HAry1dOfFacet& theFacets, TColMesh3d_HAry1dOfEdge& theEdges);

			static void RetrieveNormals(const TColMesh3d_HAry1dOfFacet& theFacets, GeoLib::Entity_StaticChain3d& theChain);
		};
	}
}

#include <Mesh3d_FacetToolsI.hxx>

#endif // !_Mesh3d_FacetTools_Header
