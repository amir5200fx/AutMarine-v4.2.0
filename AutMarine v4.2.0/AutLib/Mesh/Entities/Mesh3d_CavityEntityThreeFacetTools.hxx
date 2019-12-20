#pragma once
#ifndef _Mesh3d_CavityEntityThreeFacetTools_Header
#define _Mesh3d_CavityEntityThreeFacetTools_Header

#include <TColMesh3d_HAry1dOfNode.hxx>
#include <TColMesh3d_HAry1dOfCavityEntity.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		class Mesh3d_Element;
		class Mesh3d_CavityEntityThreeFacet;

		class Mesh3d_CavityEntityThreeFacetTools
		{

		public:

			static Global_Handle(Mesh3d_Element) RetrieveElement(const Mesh3d_CavityEntityThreeFacet& theEntity);

			static void IdentifyThreeFacets(const TColMesh3d_HAry1dOfNode& theNodes, TColMesh3d_HAry1dOfCavityEntity& theEntities);
		};
	}
}

#endif // !_Mesh3d_CavityEntityThreeFacetTools_Header
