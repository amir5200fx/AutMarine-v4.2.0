#pragma once
#ifndef _Mesh3d_NodeTools_Header
#define _Mesh3d_NodeTools_Header

#include <Mesh3d_Node.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <TColMesh3d_HAry1dOfNode.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		
		class Mesh3d_Edge;

		class Mesh3d_NodeTools
		{

		public:

			static Standard_Integer GetIndexOf(Global_Handle(Mesh3d_Node) Node);

			static Standard_Integer GetMaxIndexOf(const TColMesh3d_HAry1dOfNode& theNodes);

			static const Geom_Pnt3d& GetCoordOf(Global_Handle(Mesh3d_Node) Node);

			static TColGeom_Ary1dOfPnt3d GetCoordOf(const TColMesh3d_HAry1dOfNode& Nodes);

			static Standard_Boolean IsLess(Global_Handle(Mesh3d_Node) const& Node1, Global_Handle(Mesh3d_Node) const& Node2);

			static Global_Handle(Mesh3d_Edge) HasAFrontEdgeBetween(const Mesh3d_Node& theNode0, const Mesh3d_Node& theNode1);

			static void RetrieveFrontFacets(const TColMesh3d_HAry1dOfNode &theNodes, TColMesh3d_HAry1dOfFacet& theFacets);
		};
	}
}

#include <Mesh3d_NodeToolsI.hxx>

#endif // !_Mesh3d_NodeTools_Header
