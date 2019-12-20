#pragma once
#ifndef _Mesh2d_BoundaryNode_Header
#define _Mesh2d_BoundaryNode_Header

#include <Mesh2d_Node.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_BoundaryNode : public Mesh2d_Node
		{

		private:

			Standard_Real theParameter_;

		public:

			Mesh2d_BoundaryNode();

			Mesh2d_BoundaryNode(const Standard_Integer Index, const Geom_Pnt2d& Coord);

			virtual ~Mesh2d_BoundaryNode();

			Standard_Real Parameter() const;

			void SetParameter(const Standard_Real theParameter);
		};
	}
}

#include <Mesh2d_BoundaryNodeI.hxx>

#endif // !_Mesh2d_BoundaryNode_Header
