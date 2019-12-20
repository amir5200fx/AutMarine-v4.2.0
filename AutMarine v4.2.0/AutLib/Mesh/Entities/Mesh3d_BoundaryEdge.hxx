#pragma once
#ifndef _Mesh3d_BoundaryEdge_Header
#define _Mesh3d_BoundaryEdge_Header

#include <Mesh3d_Edge.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_BoundaryEdge : public Mesh3d_Edge
		{

		private:

		public:

			Mesh3d_BoundaryEdge();

			Mesh3d_BoundaryEdge(const Standard_Integer Index, const Standard_Real Length, Global_Handle(Mesh3d_Node) Node0, Global_Handle(Mesh3d_Node) Node1);

			virtual ~Mesh3d_BoundaryEdge();
		};
	}
}

#include <Mesh3d_BoundaryEdgeI.hxx>

#endif // !_Mesh3d_BoundaryEdge_Header
