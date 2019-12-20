#pragma once
#ifndef _Mesh3d_CavityEntitySwapEdgeTools_Header
#define _Mesh3d_CavityEntitySwapEdgeTools_Header

#include <TColMesh3d_HAry1dOfCavityShell.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_Edge;
		class Mesh3d_CavityEntitySwapEdge;

		class Mesh3d_CavityEntitySwapEdgeTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Mesh3d_CavityEntitySwapEdge) const& theSwapEdge0, Global_Handle(Mesh3d_CavityEntitySwapEdge) const& theSwapEdge1);

			static void IdentifySwapEdgesOf(Mesh3d_CavityShell& theShell);

			static void IdentifySwapEdgesOf(TColMesh3d_HAry1dOfCavityShell& theShells);
		};
	}
}

#endif // !_Mesh3d_CavityEntitySwapEdgeTools_Header
