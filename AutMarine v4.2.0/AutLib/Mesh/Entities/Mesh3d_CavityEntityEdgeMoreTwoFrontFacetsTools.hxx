#pragma once
#ifndef _Mesh3d_CavityEntityEdgeMoreTwoFrontFacetsTools_Header
#define _Mesh3d_CavityEntityEdgeMoreTwoFrontFacetsTools_Header

#include <TColMesh3d_HAry1dOfEdge.hxx>
#include <TColMesh3d_HAry1dOfElement.hxx>
#include <TColMesh3d_HAry1dOfCavityEntity.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityEntityEdgeMoreTwoFrontFacets;

		class Mesh3d_CavityEntityEdgeMoreTwoFrontFacetsTools
		{

		public:

			static TColMesh3d_HAry1dOfElement RetrieveElements(const Mesh3d_CavityEntityEdgeMoreTwoFrontFacets& theEntity);

			static void IdentifyEdgeMoreTwoFrontFacets(const TColMesh3d_HAry1dOfEdge& theEdges, TColMesh3d_HAry1dOfCavityEntity& theEntities);
		};
	}
}

#endif // !_Mesh3d_CavityEntityEdgeMoreTwoFrontFacetsTools_Header
