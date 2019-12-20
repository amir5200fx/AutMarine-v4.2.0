#pragma once
#ifndef _Mesh3d_CavityEntityPairedElements_Header
#define _Mesh3d_CavityEntityPairedElements_Header

#include <Mesh3d_CavityEntityNonConvexity.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		class Mesh3d_Edge;
		class Mesh3d_Facet;
		class Mesh3d_Element;

		class Mesh3d_CavityEntityPairedElements : public Mesh3d_CavityEntityNonConvexity
		{

		public:

			Mesh3d_CavityEntityPairedElements();

			Mesh3d_CavityEntityPairedElements(const Global_Handle(Mesh3d_Edge) thePairedEdge);

			Mesh3d_CavityEntityPairedElements(const Global_Handle(Mesh3d_Edge) thePairedEdge, const Global_Handle(Mesh3d_CavityShell) theShell);

			virtual ~Mesh3d_CavityEntityPairedElements();

		};
	}
}

#include <Mesh3d_CavityEntityPairedElementsI.hxx>

#endif // !_Mesh3d_CavityEntityPairedElements_Header
