#pragma once
#ifndef _Mesh3d_EdgeTools_Header
#define _Mesh3d_EdgeTools_Header

#include <Mesh3d_Edge.hxx>
#include <Entity_EdgeIndex.hxx>
#include <TColEntity_Ary1dOfEdgeIndex.hxx>
#include <TColMesh3d_HAry1dOfNode.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		
		class Mesh3d_EdgeTools
		{

		public:

			static M_GEO Entity_EdgeIndex StaticOf(const Mesh3d_Edge& Edge);

			static TColEntity_Ary1dOfEdgeIndex StaticOf(const TColMesh3d_HAry1dOfEdge& Edges);

			static TColMesh3d_HAry1dOfNode RetrieveNodesFrom(const TColMesh3d_HAry1dOfEdge& Edges);

			static TColMesh3d_HAry1dOfNode RetrieveStarNodesAround(const Mesh3d_Edge& theEdge, TColMesh3d_HAry1dOfEdge& theEdges);

			//! Throw an exception if found an error
			static Standard_Real AngleOf(const Mesh3d_Edge& theEdge);

			static Standard_Real LengthOf(Global_Handle(Mesh3d_Edge) const &Edge);

			static Standard_Boolean IsLess(Global_Handle(Mesh3d_Edge) const & Edge1, Global_Handle(Mesh3d_Edge) const & Edge2);
		};
	}
}

#include <Mesh3d_EdgeToolsI.hxx>

#endif // !_Mesh3d_EdgeTools_Header
