#pragma once
#ifndef _Mesh2d_DegenBoundaryNode_Header
#define _Mesh2d_DegenBoundaryNode_Header

#include <Mesh2d_SurfaceBoundaryNode.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_DegenBoundaryNode : public Mesh2d_SurfaceBoundaryNode
		{

		private:

			Geom_Pnt2d theOrigin_;

		public:

			Mesh2d_DegenBoundaryNode();

			Mesh2d_DegenBoundaryNode(const Standard_Integer theIndex, const Geom_Pnt2d& theCoord);

			Mesh2d_DegenBoundaryNode(const Standard_Integer theIndex, const Geom_Pnt2d& theCoord, const Geom_Pnt2d& theOrigin);

			virtual ~Mesh2d_DegenBoundaryNode();

			const Geom_Pnt2d& Origin() const;

			void SetOrigin(const Geom_Pnt2d& theOrigin);

			void TranslateToOrigin();
		};
	}
}

#include <Mesh2d_DegenBoundaryNodeI.hxx>

#endif // !_Mesh2d_DegenBoundaryNode_Header
