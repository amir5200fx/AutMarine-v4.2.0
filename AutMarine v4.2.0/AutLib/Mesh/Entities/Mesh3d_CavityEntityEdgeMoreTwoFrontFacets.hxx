#pragma once
#ifndef _Mesh3d_CavityEntityEdgeMoreTwoFrontFacets_Header
#define _Mesh3d_CavityEntityEdgeMoreTwoFrontFacets_Header

#include <Mesh3d_CavityEntity.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_Edge;

		class Mesh3d_CavityEntityEdgeMoreTwoFrontFacets : public Mesh3d_CavityEntity
		{

		private:

			const Global_Handle(Mesh3d_Edge) theEdge_;

		public:

			Mesh3d_CavityEntityEdgeMoreTwoFrontFacets();

			Mesh3d_CavityEntityEdgeMoreTwoFrontFacets(const Global_Handle(Mesh3d_Edge) theEdge);

			Mesh3d_CavityEntityEdgeMoreTwoFrontFacets(const Global_Handle(Mesh3d_Edge) theEdge, const Global_Handle(Mesh3d_CavityShell) theShell);

			void Init(const Global_Handle(Mesh3d_Edge) theEdge, const Global_Handle(Mesh3d_CavityShell) theShell);

			const Global_Handle(Mesh3d_Edge) Edge() const;
		};
	}
}

#include <Mesh3d_CavityEntityEdgeMoreTwoFrontFacetsI.hxx>

#endif // !_Mesh3d_CavityEntityEdgeMoreTwoFrontFacets_Header
