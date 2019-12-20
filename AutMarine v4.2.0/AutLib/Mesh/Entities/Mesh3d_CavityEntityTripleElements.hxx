#pragma once
#ifndef _Mesh3d_CavityEntityTripleElements_Header
#define _Mesh3d_CavityEntityTripleElements_Header

#include <Mesh3d_CavityEntityNonConvexity.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_Edge;
		class Mesh3d_Facet;
		class Mesh3d_Element;

		class Mesh3d_CavityEntityTripleElements : public Mesh3d_CavityEntityNonConvexity
		{

		private:


		public:

			Mesh3d_CavityEntityTripleElements();

			Mesh3d_CavityEntityTripleElements(const Global_Handle(Mesh3d_Edge) thePairedEdge);

			Mesh3d_CavityEntityTripleElements(const Global_Handle(Mesh3d_Edge) thePairedEdge, const Global_Handle(Mesh3d_CavityShell) theShell);

			virtual ~Mesh3d_CavityEntityTripleElements();

		};
	}
}

#include <Mesh3d_CavityEntityTripleElementsI.hxx>

#endif // !_Mesh3d_CavityEntityTripleElements_Header
