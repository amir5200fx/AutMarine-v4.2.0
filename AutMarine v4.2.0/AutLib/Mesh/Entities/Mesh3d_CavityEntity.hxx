#pragma once
#ifndef _Mesh3d_CavityEntity_Header
#define _Mesh3d_CavityEntity_Header

#include <Global_Memory.hxx>
#include <Standard_Type.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityShell;

		class Mesh3d_CavityEntity
		{

		protected:

			const Global_Handle(Mesh3d_CavityShell) theCavity_;

			Standard_Integer theIndex_;

		protected:

			Mesh3d_CavityEntity();

			Mesh3d_CavityEntity(const Standard_Integer theIndex, const Global_Handle(Mesh3d_CavityShell) theShell);

			void Init(const Standard_Integer theIndex, const Global_Handle(Mesh3d_CavityShell) theShell);

			virtual ~Mesh3d_CavityEntity();	

		public:

			void SetIndex(const Standard_Integer theIndex);

			void SetShell(const Global_Handle(Mesh3d_CavityShell) theShell);

			Standard_Integer Index() const;

			const Global_Handle(Mesh3d_CavityShell) Cavity() const;
			
		};
	}
}

#include <Mesh3d_CavityEntityI.hxx>

#endif // !_Mesh3d_CavityEntity_Header
