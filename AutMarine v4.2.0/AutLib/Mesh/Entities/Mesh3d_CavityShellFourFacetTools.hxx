#pragma once
#ifndef _Mesh3d_CavityShellFourFacetTools_Header
#define _Mesh3d_CavityShellFourFacetTools_Header

#include <Global_Memory.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityShellFourFacet;
		class Mesh3d_Facet;
		class Mesh3d_Node;

		class Mesh3d_CavityShellFourFacetTools
		{

		public:

			static void RetrieveCandidates(const Mesh3d_CavityShellFourFacet& theShell, Global_Handle(Mesh3d_Facet)& theFacet, Global_Handle(Mesh3d_Node)& theNode);
		};
	}
}

#endif // !_Mesh3d_CavityShellFourFacetTools_Header
