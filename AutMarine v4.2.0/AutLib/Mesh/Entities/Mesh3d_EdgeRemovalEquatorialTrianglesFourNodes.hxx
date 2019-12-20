#pragma once
#ifndef _Mesh3d_EdgeRemovalEquatorialTrianglesFourNodes_Header
#define _Mesh3d_EdgeRemovalEquatorialTrianglesFourNodes_Header

#include <Mesh3d_EdgeRemovalEquatorialTriangles.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_EdgeRemovalEquatorialTrianglesFourNodes : public Mesh3d_EdgeRemovalEquatorialTriangles
		{

		private:


		public:

			Mesh3d_EdgeRemovalEquatorialTrianglesFourNodes();

			Mesh3d_EdgeRemovalEquatorialTrianglesFourNodes(const TColMesh3d_HAry1dOfNode& theNodes, const TColMesh3d_HAry1dOfEdge& theEdges, const TColEntity_Ary1dOfTriangleIndex& theTriangles);

			virtual ~Mesh3d_EdgeRemovalEquatorialTrianglesFourNodes();
		};
	}
}

#endif // !_Mesh3d_EdgeRemovalEquatorialTrianglesFourNodes_Header
