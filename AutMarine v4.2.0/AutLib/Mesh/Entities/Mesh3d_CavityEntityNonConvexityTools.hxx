#pragma once
#ifndef _Mesh3d_CavityEntityNonConvexityTools_Header
#define _Mesh3d_CavityEntityNonConvexityTools_Header

#include <TColMesh3d_HAry1dOfCavityShell.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_Edge;
		class Mesh3d_CavityEntityNonConvexity;
		class Mesh3d_CavityEntitySwapEdge;

		class Mesh3d_CavityEntityNonConvexityTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Mesh3d_CavityEntityNonConvexity) const& theNonConvexity0, Global_Handle(Mesh3d_CavityEntityNonConvexity) const& theNonConvexity1);

			static void IdentifyNonConvexityOf(Mesh3d_CavityShell& theShell, const Standard_Real theCriteria_Radian);

			static void IdentifyNonConvexityOf(TColMesh3d_HAry1dOfCavityShell& theShells, const Standard_Real theCriteria_Degree);

			//! Warning: Not release from memory automatically
			static Global_Handle(Mesh3d_CavityEntityNonConvexity) CreateNonConvexity(const Global_Handle(Mesh3d_Edge) theEdge);
		};
	}
}

#endif // !_Mesh3d_CavityEntityNonConvexityTools_Header
