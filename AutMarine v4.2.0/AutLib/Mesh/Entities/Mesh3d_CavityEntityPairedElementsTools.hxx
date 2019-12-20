#pragma once
#ifndef _Mesh3d_CavityEntityPairedElementsTools_Header
#define _Mesh3d_CavityEntityPairedElementsTools_Header

#include <Global_Memory.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityEntityNonConvexity;
		class Mesh3d_Edge;
		class Mesh3d_Facet;

		class Mesh3d_CavityEntityPairedElementsTools
		{

		public:

			//! Throw an exception if found an error
			static Global_Handle(Mesh3d_Facet) PairedFacetOf(const Global_Handle(Mesh3d_Edge) theEdge);
		};
	}
}

#endif // !_Mesh3d_CavityEntityPairedElementsTools_Header
