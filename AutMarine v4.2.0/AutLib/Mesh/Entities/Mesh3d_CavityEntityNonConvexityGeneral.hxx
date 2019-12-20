#pragma once
#ifndef _Mesh3d_CavityEntityNonConvexityGeneral_Header
#define _Mesh3d_CavityEntityNonConvexityGeneral_Header

#include <Mesh3d_CavityEntityNonConvexity.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityEntityNonConvexityGeneral : public Mesh3d_CavityEntityNonConvexity
		{

		private:

		public:

			Mesh3d_CavityEntityNonConvexityGeneral();

			Mesh3d_CavityEntityNonConvexityGeneral(const Global_Handle(Mesh3d_Edge) theEdge);

			Mesh3d_CavityEntityNonConvexityGeneral(const Global_Handle(Mesh3d_Edge) theEdge, const Global_Handle(Mesh3d_CavityShell) theShell);

			virtual ~Mesh3d_CavityEntityNonConvexityGeneral();
		};
	}
}

#endif // !_Mesh3d_CavityEntityNonConvexityGeneral_Header
