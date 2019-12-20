#pragma once
#ifndef _Mesh3d_CavityEntityAllThreeFronts_Header
#define _Mesh3d_CavityEntityAllThreeFronts_Header

#include <Mesh3d_CavityEntity.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_Node;

		class Mesh3d_CavityEntityAllThreeFronts : public Mesh3d_CavityEntity
		{

		private:

			const Global_Handle(Mesh3d_Node) theApex_;

		public:

			Mesh3d_CavityEntityAllThreeFronts();

			Mesh3d_CavityEntityAllThreeFronts(const Global_Handle(Mesh3d_Node) theApex);

			Mesh3d_CavityEntityAllThreeFronts(const Global_Handle(Mesh3d_Node) theApex, const Global_Handle(Mesh3d_CavityShell) theShell);

			~Mesh3d_CavityEntityAllThreeFronts();

			const Global_Handle(Mesh3d_Node) Apex() const;

			void Init(const Global_Handle(Mesh3d_Node) theApex, const Global_Handle(Mesh3d_CavityShell) theShell);
		};
	}
}

#include <Mesh3d_CavityEntityAllThreeFrontsI.hxx>

#endif // !_Mesh3d_CavityEntityAllThreeFronts_Header
