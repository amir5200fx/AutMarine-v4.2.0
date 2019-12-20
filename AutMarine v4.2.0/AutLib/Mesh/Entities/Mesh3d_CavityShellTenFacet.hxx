#pragma once
#ifndef _Mesh3d_CavityShellTenFacet_Header
#define _Mesh3d_CavityShellTenFacet_Header

#include <Mesh3d_CavityShell.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityShellTenFacet : public Mesh3d_CavityShell
		{

		private:


		public:

			Mesh3d_CavityShellTenFacet();

			Mesh3d_CavityShellTenFacet(Global_Handle(Mesh3d_Facet) theFacet0, Global_Handle(Mesh3d_Facet) theFacet1, Global_Handle(Mesh3d_Facet) theFacet2, Global_Handle(Mesh3d_Facet) theFacet3, Global_Handle(Mesh3d_Facet) theFacet4, Global_Handle(Mesh3d_Facet) theFacet5, Global_Handle(Mesh3d_Facet) theFacet6, Global_Handle(Mesh3d_Facet) theFacet7, Global_Handle(Mesh3d_Facet) theFacet8, Global_Handle(Mesh3d_Facet) theFacet9);

			virtual ~Mesh3d_CavityShellTenFacet();
		};
	}
}

#endif // !_Mesh3d_CavityShellTenFacet_Header
