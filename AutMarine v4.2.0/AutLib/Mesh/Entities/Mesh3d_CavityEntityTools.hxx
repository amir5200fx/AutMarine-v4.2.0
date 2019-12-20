#pragma once
#ifndef _Mesh3d_CavityEntityTools_Header
#define _Mesh3d_CavityEntityTools_Header

#include <Mesh3d_CavityEntity.hxx>
#include <TColMesh3d_HAry1dOfElement.hxx>
#include <TColMesh3d_HAry1dOfCavityEntity.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityEntityTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Mesh3d_CavityEntity) const& theCavity1, Global_Handle(Mesh3d_CavityEntity) const& theCavity2);

			static void RetrieveDefiniteElementsToRemove(const TColMesh3d_HAry1dOfCavityEntity& theEntities, TColMesh3d_HAry1dOfElement& Elements);
		};
	}
}

#include <Mesh3d_CavityEntityToolsI.hxx>

#endif // !_Mesh3d_CavityEntityTools_Header
