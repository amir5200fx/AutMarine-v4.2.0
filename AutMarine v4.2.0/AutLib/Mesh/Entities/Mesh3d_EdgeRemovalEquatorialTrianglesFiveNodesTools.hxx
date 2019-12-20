#pragma once
#ifndef _Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodesTools_Header
#define _Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodesTools_Header

#include <TColEntity_Ary1dOfTriangleIndex.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodesTools
		{

		public:

			static TColEntity_Ary1dOfTriangleIndex EquatorialTrianglesArrange(const Standard_Integer Index);
		};
	}
}

#endif // !_Mesh3d_EdgeRemovalEquatorialTrianglesFiveNodesTools_Header
