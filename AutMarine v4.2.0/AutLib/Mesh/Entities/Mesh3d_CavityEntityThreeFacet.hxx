#pragma once
#ifndef _Mesh3d_CavityEntityThreeFacet_Header
#define _Mesh3d_CavityEntityThreeFacet_Header

#include <Mesh3d_CavityEntity.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_Element;

		class Mesh3d_CavityEntityThreeFacet : public Mesh3d_CavityEntity
		{

		private:

			const Global_Handle(Mesh3d_Element) theElement_;

		public:

			Mesh3d_CavityEntityThreeFacet();

			Mesh3d_CavityEntityThreeFacet(const Global_Handle(Mesh3d_Element) theElement);

			Mesh3d_CavityEntityThreeFacet(const Global_Handle(Mesh3d_Element) theElement, const Global_Handle(Mesh3d_CavityShell) theShell);

			virtual ~Mesh3d_CavityEntityThreeFacet();

			const Global_Handle(Mesh3d_Element) Element() const;

			void Init(const Global_Handle(Mesh3d_Element) theElement);

		};
	}
}

#include <Mesh3d_CavityEntityThreeFacetI.hxx>

#endif // !_Mesh3d_CavityEntityThreeFacet_Header
