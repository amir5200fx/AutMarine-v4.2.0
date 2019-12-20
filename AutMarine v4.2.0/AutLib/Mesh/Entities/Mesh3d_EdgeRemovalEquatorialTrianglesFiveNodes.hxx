#pragma once
#ifndef _Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodes_Header
#define _Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodes_Header

#include <Mesh3d_EdgeRemovalEquatorialTriangles.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodes : public Mesh3d_EdgeRemovalEquatorialTriangles
		{

		private:

		public:

			Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodes();

			Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodes(const TColMesh3d_HAry1dOfNode& theNodes, const TColMesh3d_HAry1dOfEdge& theEdges, const TColEntity_Ary1dOfTriangleIndex& theTriangles);

			virtual ~Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodes();
		};
	}
}

#endif // !_Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodes_Header
