#pragma once
#ifndef _Mesh3d_BoundaryNode_Header
#define _Mesh3d_BoundaryNode_Header

#include <Mesh3d_Node.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_BoundaryNode : public Mesh3d_Node
		{

		private:

		public:

			Mesh3d_BoundaryNode();

			Mesh3d_BoundaryNode(const Standard_Integer Index, const Geom_Pnt3d& Coord);

			virtual ~Mesh3d_BoundaryNode();
		};
	}
}

#include <Mesh3d_BoundaryNodeI.hxx>

#endif // !_Mesh3d_BoundaryNode_Header
