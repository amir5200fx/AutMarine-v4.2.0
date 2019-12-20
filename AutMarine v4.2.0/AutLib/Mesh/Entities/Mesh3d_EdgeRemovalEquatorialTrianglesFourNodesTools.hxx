#pragma once
#ifndef _Mesh3d_EdgeRemovalEquatorialTrianglesFourNodesTools_Header
#define _Mesh3d_EdgeRemovalEquatorialTrianglesFourNodesTools_Header

#include <TColEntity_Ary1dOfTriangleIndex.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_EdgeRemovalEquatorialTrianglesFourNodesTools
		{

		public:

			static TColEntity_Ary1dOfTriangleIndex EquatorialTrianglesArrange1();

			static TColEntity_Ary1dOfTriangleIndex EquatorialTrianglesArrange2();
		};
	}
}

#endif // !_Mesh3d_EdgeRemovalEquatorialTrianglesFourNodesTools_Header
