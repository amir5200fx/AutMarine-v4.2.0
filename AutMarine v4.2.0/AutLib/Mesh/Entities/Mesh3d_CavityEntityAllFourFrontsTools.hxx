#pragma once
#ifndef _Mesh3d_CavityEntityAllFourFrontsTools_Header
#define _Mesh3d_CavityEntityAllFourFrontsTools_Header

#include <TColMesh3d_HAry1dOfNode.hxx>
#include <TColMesh3d_HAry1dOfElement.hxx>
#include <TColMesh3d_HAry1dOfCavityEntity.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityEntityAllFourFronts;

		class Mesh3d_CavityEntityAllFourFrontsTools
		{

		public:

			static TColMesh3d_HAry1dOfElement RetrieveElements(const Mesh3d_CavityEntityAllFourFronts& theEntity);

			static void IdentifyAllFourFronts(const TColMesh3d_HAry1dOfNode& theNodes, TColMesh3d_HAry1dOfCavityEntity& theEntities);
		};
	}
}

#endif // !_Mesh3d_CavityEntityAllFourFrontsTools_Header
