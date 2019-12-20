#pragma once
#ifndef _Mesh3d_CavityEntityThreeFacetHole_Header
#define _Mesh3d_CavityEntityThreeFacetHole_Header

#include <Mesh3d_CavityEntity.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_Node;

		class Mesh3d_CavityEntityThreeFacetHole : public Mesh3d_CavityEntity
		{

		private:

			const Global_Handle(Mesh3d_Node) theApex_;

		public:

			Mesh3d_CavityEntityThreeFacetHole();

			Mesh3d_CavityEntityThreeFacetHole(const Global_Handle(Mesh3d_Node) theApex, const Global_Handle(Mesh3d_CavityShell) theShell);

			void Init(const Global_Handle(Mesh3d_Node) theApex, const Global_Handle(Mesh3d_CavityShell) theShell);

			const Global_Handle(Mesh3d_Node) Apex() const;

		};
	}
}

#include <Mesh3d_CavityEntityThreeFacetHoleI.hxx>

#endif // !_Mesh3d_CavityEntityThreeFacetHole_Header
