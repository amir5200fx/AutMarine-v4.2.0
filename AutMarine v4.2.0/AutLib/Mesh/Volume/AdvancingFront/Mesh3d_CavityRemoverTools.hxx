#pragma once
#ifndef _Mesh3d_CavityRemoverTools_Header
#define _Mesh3d_CavityRemoverTools_Header

#include <TColMesh3d_HAry1dOfFacet.hxx>
#include <TColMesh3d_HAry1dOfElement.hxx>
#include <TColMesh3d_HAry1dOfCavityShell.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityRemoverTools
		{

		public:

			static Standard_Boolean IsValidToFlip(const Mesh3d_Facet& theFacet);

			static void DefiniteElementsToRemove(const TColMesh3d_HAry1dOfFacet& theFacets, TColMesh3d_HAry1dOfElement& theElements, const Standard_Boolean theThreeEntities = Standard_True, const Standard_Boolean theFourEntities = Standard_True);

			static void CreateCavityShells(const TColMesh3d_HAry1dOfFacet& theFacets, TColMesh3d_HAry1dOfCavityShell& theShells);
		};
	}
}

#endif // !_Mesh3d_CavityRemoverTools_Header
