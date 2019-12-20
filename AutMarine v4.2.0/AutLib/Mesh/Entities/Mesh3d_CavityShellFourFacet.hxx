#pragma once
#ifndef _Mesh3d_CavityShellFourFacet_Header
#define _Mesh3d_CavityShellFourFacet_Header

#include <Mesh3d_CavityShell.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityShellFourFacet : public Mesh3d_CavityShell
		{

		private:

		public:

			Mesh3d_CavityShellFourFacet();

			Mesh3d_CavityShellFourFacet(Global_Handle(Mesh3d_Facet) theFacet0, Global_Handle(Mesh3d_Facet) theFacet1, Global_Handle(Mesh3d_Facet) theFacet2, Global_Handle(Mesh3d_Facet) theFacet3);

			virtual ~Mesh3d_CavityShellFourFacet();
		};
	}
}

#endif // !_Mesh3d_CavityShellFourFacet_Header
