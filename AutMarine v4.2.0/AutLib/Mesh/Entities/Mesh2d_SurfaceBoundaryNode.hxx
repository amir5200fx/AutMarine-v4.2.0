#pragma once
#ifndef _Mesh2d_SurfaceBoundaryNode_Header
#define _Mesh2d_SurfaceBoundaryNode_Header

#include <Geom_Pnt3d.hxx>
#include <Mesh2d_BoundaryNode.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_SurfaceBoundaryNode : public Mesh2d_BoundaryNode
		{

		private:

			Geom_Pnt3d theCoord3d_;		

			Standard_Boolean IsDone_;

		public:

			Mesh2d_SurfaceBoundaryNode();

			Mesh2d_SurfaceBoundaryNode(const Standard_Integer Index, const Geom_Pnt2d& Coord);

			virtual ~Mesh2d_SurfaceBoundaryNode();

			const Geom_Pnt3d& Coord3d() const;

			Standard_Boolean IsDone() const;	

			void SetCondition(const Standard_Boolean theCondition);

			void SetCoord3d(const Geom_Pnt3d& theCoord);
		};
	}
}

#include <Mesh2d_SurfaceBoundaryNodeI.hxx>

#endif // !_Mesh2d_SurfaceBoundaryNode_Header
