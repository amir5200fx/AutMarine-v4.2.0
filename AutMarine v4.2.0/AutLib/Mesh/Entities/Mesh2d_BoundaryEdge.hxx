#pragma once
#ifndef _Mesh2d_BoundaryEdge_Header
#define _Mesh2d_BoundaryEdge_Header

#include <Mesh2d_Edge.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_BoundaryEdge : public Mesh2d_Edge
		{

		private:

		public:

			Mesh2d_BoundaryEdge();

			Mesh2d_BoundaryEdge(const Standard_Integer Index, const Standard_Real Length, const Geom_Pnt2d& Centre, Global_Handle(Mesh2d_Node) Node0, Global_Handle(Mesh2d_Node) Node1);

			virtual ~Mesh2d_BoundaryEdge();
		};
	}
}

#include <Mesh2d_BoundaryEdgeI.hxx>

#endif // !_Mesh2d_BoundaryEdge_Header
