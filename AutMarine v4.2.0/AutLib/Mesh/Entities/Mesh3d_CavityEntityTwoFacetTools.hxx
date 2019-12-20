#pragma once
#ifndef _Mesh3d_CavityEntityTwoFacetTools_Header
#define _Mesh3d_CavityEntityTwoFacetTools_Header

#include <TColMesh3d_HAry1dOfEdge.hxx>
#include <TColMesh3d_HAry1dOfCavityEntity.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_Element;
		class Mesh3d_CavityEntityTwoFacet;

		class Mesh3d_CavityEntityTwoFacetTools
		{

		public:

			static Global_Handle(Mesh3d_Element) RetrieveElement(const Mesh3d_CavityEntityTwoFacet& theEntity);

			static void IdentifyTwoFacets(const TColMesh3d_HAry1dOfEdge& theEdges, TColMesh3d_HAry1dOfCavityEntity& theEntities);
		};
	}
}

#endif // !_Mesh3d_CavityEntityTwoFacetTools_Header
