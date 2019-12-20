#pragma once
#ifndef _Mesh2d_NodeTools_Header
#define _Mesh2d_NodeTools_Header

#include <Mesh2d_Node.hxx>
#include <Mesh2d_BoundaryNode.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColMesh2d_HAry1dOfNode.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_NodeTools
		{

		public:

			static Standard_Boolean IsOnBoundary(const Global_Handle(Mesh2d_Node) theNode);

			static Standard_Boolean IsLess(Global_Handle(Mesh2d_Node) const & theNode1, Global_Handle(Mesh2d_Node) const & theNode2);

			static TColGeom_Ary1dOfPnt2d GetCoordOf(const TColMesh2d_HAry1dOfNode& Nodes);

			static const Geom_Pnt2d & GetCoordOf(Global_Handle(Mesh2d_Node) Node);
		};
	}
}

#include <Mesh2d_NodeToolsI.hxx>

#endif // !_Mesh2d_NodeTools_Header
