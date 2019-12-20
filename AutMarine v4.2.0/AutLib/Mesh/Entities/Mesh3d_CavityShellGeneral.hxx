#pragma once
#ifndef _Mesh3d_CavityShellGeneral_Header
#define _Mesh3d_CavityShellGeneral_Header

#include <Mesh3d_CavityShell.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityShellGeneral : public Mesh3d_CavityShell
		{

		private:

		public:

			Mesh3d_CavityShellGeneral();

			Mesh3d_CavityShellGeneral(const TColMesh3d_HAry1dOfFacet& theFacets);

			virtual ~Mesh3d_CavityShellGeneral();
		};
	}
}

#endif // !_Mesh3d_CavityShellGeneral_Header
