#pragma once
#ifndef _Mesh2d_EdgeTools_Header
#define _Mesh2d_EdgeTools_Header

#include <Mesh2d_Edge.hxx>
#include <Mesh2d_BoundaryEdge.hxx>
#include <TColEntity_Ary1dOfEdgeIndex.hxx>
#include <TColMesh2d_HAry1dOfEdge.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_StaticChain2d;
	}

	namespace MeshLib
	{

		class Mesh2d_EdgeTools
		{

		public:

			static Standard_Boolean IsOnBoundary(const Global_Handle(Mesh2d_Edge) theEdge);

			static Standard_Boolean IsLess(Global_Handle(Mesh2d_Edge) const & theEdge1, Global_Handle(Mesh2d_Edge) const & theEdge2);

			static Standard_Boolean IsIntersect(const Mesh2d_Edge& Edge1, const Mesh2d_Edge& Edge2);

			static Standard_Real LengthOf(Global_Handle(Mesh2d_Edge) const & theEdge);

			static M_GEO Entity_EdgeIndex StaticOf(const Mesh2d_Edge& Edge);

			static TColEntity_Ary1dOfEdgeIndex StaticOf(const TColMesh2d_HAry1dOfEdge& Edges);

			static TColMesh2d_HAry1dOfNode RetrieveNodesFrom(const TColMesh2d_HAry1dOfEdge& Edges);

			static TColMesh2d_HAry1dOfNode RetrieveSortedNodesFrom(const TColMesh2d_HAry1dOfEdge& Edges);

			static M_GEO Entity_StaticChain2d RetrieveChainFrom(const TColMesh2d_HAry1dOfEdge& Edges);

			static void ExportToPlt(const TColMesh2d_HAry1dOfEdge& theEdges, fstream& File);
		};
	}
}

#include <Mesh2d_EdgeToolsI.hxx>

#endif // !_Mesh2d_EdgeTools_Header
