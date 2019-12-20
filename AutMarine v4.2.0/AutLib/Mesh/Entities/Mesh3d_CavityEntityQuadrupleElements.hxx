#pragma once
#ifndef _Mesh3d_CavityEntityQuadrupleElements_Header
#define _Mesh3d_CavityEntityQuadrupleElements_Header

#include <Mesh3d_CavityEntityNonConvexity.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityEntityQuadrupleElements : public Mesh3d_CavityEntityNonConvexity
		{

		private:

		public:

			Mesh3d_CavityEntityQuadrupleElements();

			Mesh3d_CavityEntityQuadrupleElements(const Global_Handle(Mesh3d_Edge) thePairedEdge);

			Mesh3d_CavityEntityQuadrupleElements(const Global_Handle(Mesh3d_Edge) thePairedEdge, const Global_Handle(Mesh3d_CavityShell) theShell);

			virtual ~Mesh3d_CavityEntityQuadrupleElements();
		};
	}
}

#endif // !_Mesh3d_CavityEntityQuadrupleElements_Header
