#pragma once
#ifndef _Mesh3d_CavityEntityTwoFacet_Header
#define _Mesh3d_CavityEntityTwoFacet_Header

#include <Mesh3d_CavityEntity.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_Element;

		class Mesh3d_CavityEntityTwoFacet : public Mesh3d_CavityEntity
		{

		private:

			const Global_Handle(Mesh3d_Element) theElement_;

		public:

			Mesh3d_CavityEntityTwoFacet();

			Mesh3d_CavityEntityTwoFacet(const Global_Handle(Mesh3d_Element) theElement);

			Mesh3d_CavityEntityTwoFacet(const Global_Handle(Mesh3d_Element) theElement, const Global_Handle(Mesh3d_CavityShell) theShell);

			~Mesh3d_CavityEntityTwoFacet();

			void Init(const Global_Handle(Mesh3d_Element) theElement);

			const Global_Handle(Mesh3d_Element) Element() const;
		};
	}
}

#include <Mesh3d_CavityEntityTwoFacetI.hxx>

#endif // !_Mesh3d_CavityEntityTwoFacet_Header
