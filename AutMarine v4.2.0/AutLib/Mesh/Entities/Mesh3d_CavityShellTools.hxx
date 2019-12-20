#pragma once
#ifndef _Mesh3d_CavityShellTools_Header
#define _Mesh3d_CavityShellTools_Header

#include <Mesh3d_CavityShell.hxx>
#include <TColMesh3d_HAry1dOfFacet.hxx>
#include <TColMesh3d_HAry1dOfCavityShell.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityShellTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Mesh3d_CavityShell) const& theShell0, Global_Handle(Mesh3d_CavityShell) const& theShell1);

			static void IdentifyShells(const TColMesh3d_HAry1dOfFacet& theFacets, TColMesh3d_HAry1dOfCavityShell& theShells);

			static void IdentifyNonConvexitiesOf(TColMesh3d_HAry1dOfCavityShell& theShells);

			//! Warning: not removed from memory automatically
			static Global_Handle(Mesh3d_CavityShell) CreateShell(const TColMesh3d_HAry1dOfFacet& theFacets);
		};
	}
}

#include <Mesh3d_CavityShellToolsI.hxx>

#endif // !_Mesh3d_CavityShellTools_Header
