#pragma once
#ifndef _Mesh3d_CavityShellEightFacet_Header
#define _Mesh3d_CavityShellEightFacet_Header

#include <Mesh3d_CavityShell.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityShellEightFacet : public Mesh3d_CavityShell
		{

		private:

		public:

			Mesh3d_CavityShellEightFacet();

			Mesh3d_CavityShellEightFacet(Global_Handle(Mesh3d_Facet) theFacet0, Global_Handle(Mesh3d_Facet) theFacet1, Global_Handle(Mesh3d_Facet) theFacet2, Global_Handle(Mesh3d_Facet) theFacet3, Global_Handle(Mesh3d_Facet) theFacet4, Global_Handle(Mesh3d_Facet) theFacet5, Global_Handle(Mesh3d_Facet) theFacet6, Global_Handle(Mesh3d_Facet) theFacet7);

			virtual ~Mesh3d_CavityShellEightFacet();
		};
	}
}

#include <Mesh3d_CavityShellEightFacetI.hxx>

#endif // !_Mesh3d_CavityShellEightFacet_Header
