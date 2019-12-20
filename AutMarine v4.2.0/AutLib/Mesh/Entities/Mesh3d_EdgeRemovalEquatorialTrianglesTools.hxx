#pragma once
#ifndef _Mesh3d_EdgeRemovalEquatorialTrianglesTools_Header
#define _Mesh3d_EdgeRemovalEquatorialTrianglesTools_Header

#include <Global_Memory.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_Edge;
		class Mesh3d_EdgeRemovalEquatorialTriangles;
		class Mesh3d_QualityMap;

		class Mesh3d_EdgeRemovalEquatorialTrianglesTools
		{

		public:

			//! Warning: not removed from memory automatically
			static Global_Handle(Mesh3d_EdgeRemovalEquatorialTriangles) CreateEquatorialTriangle(const Mesh3d_Edge& theEdge, const Mesh3d_QualityMap& theQualityMap);
		};
	}
}

#endif // !_Mesh3d_EdgeRemovalEquatorialTrianglesTools_Header
