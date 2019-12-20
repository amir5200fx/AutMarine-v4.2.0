#pragma once
#ifndef _Mesh3d_EdgeRemovalEquatorialTrianglesSixNodes_Header
#define _Mesh3d_EdgeRemovalEquatorialTrianglesSixNodes_Header

#include <Mesh3d_EdgeRemovalEquatorialTriangles.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_EdgeRemovalEquatorialTrianglesSixNodes : public Mesh3d_EdgeRemovalEquatorialTriangles
		{

		private:

		public:

			Mesh3d_EdgeRemovalEquatorialTrianglesSixNodes();

			Mesh3d_EdgeRemovalEquatorialTrianglesSixNodes(const TColMesh3d_HAry1dOfNode& theNodes, const TColMesh3d_HAry1dOfEdge& theEdges, const TColEntity_Ary1dOfTriangleIndex& theTriangles);

			~Mesh3d_EdgeRemovalEquatorialTrianglesSixNodes();
		};
	}
}

#endif // !_Mesh3d_EdgeRemovalEquatorialTrianglesSixNodes_Header
