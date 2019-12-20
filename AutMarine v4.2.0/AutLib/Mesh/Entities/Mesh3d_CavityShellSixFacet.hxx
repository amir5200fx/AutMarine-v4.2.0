#pragma once
#ifndef _Mesh3d_CavityShellSixFacet_Header
#define _Mesh3d_CavityShellSixFacet_Header

#include <Mesh3d_CavityShell.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityShellSixFacet : public Mesh3d_CavityShell
		{

		private:

			Global_Handle(Mesh3d_Node) theVertex0_;
			Global_Handle(Mesh3d_Node) theVertex1_;

			TColMesh3d_HAry1dOfNode theEquatorial_;

		public:

			Mesh3d_CavityShellSixFacet();

			Mesh3d_CavityShellSixFacet(Global_Handle(Mesh3d_Facet) theFacet0, Global_Handle(Mesh3d_Facet) theFacet1, Global_Handle(Mesh3d_Facet) theFacet2, Global_Handle(Mesh3d_Facet) theFacet3, Global_Handle(Mesh3d_Facet) theFacet4, Global_Handle(Mesh3d_Facet) theFacet5);

			virtual ~Mesh3d_CavityShellSixFacet();

			Global_Handle(Mesh3d_Node) Vertex0() const;

			Global_Handle(Mesh3d_Node) Vertex1() const;

			const TColMesh3d_HAry1dOfNode& Equatorial() const;

		private:

			void FindApices();
		};
	}
}

#include <Mesh3d_CavityShellSixFacetI.hxx>

#endif // !_Mesh3d_CavityShellSixFacet_Header
