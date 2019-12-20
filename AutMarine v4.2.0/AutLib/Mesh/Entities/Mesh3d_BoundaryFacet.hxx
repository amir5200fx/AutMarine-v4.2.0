#pragma once
#ifndef _Mesh3d_BoundaryFacet_Header
#define _Mesh3d_BoundaryFacet_Header

#include <Mesh3d_Facet.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_BoundaryFacet : public Mesh3d_Facet
		{

		public:

			Mesh3d_BoundaryFacet();

			Mesh3d_BoundaryFacet(const Standard_Integer Index);

			Mesh3d_BoundaryFacet(const Standard_Integer Index, Global_Handle(Mesh3d_Node) theNode0, Global_Handle(Mesh3d_Node) theNode1, Global_Handle(Mesh3d_Node) theNode2);

			Mesh3d_BoundaryFacet(const Standard_Integer Index, Global_Handle(Mesh3d_Node) theNode0, Global_Handle(Mesh3d_Node) theNode1, Global_Handle(Mesh3d_Node) theNode2, Global_Handle(Mesh3d_Edge) theEdge0, Global_Handle(Mesh3d_Edge) theEdge1, Global_Handle(Mesh3d_Edge) theEdge2);

			virtual ~Mesh3d_BoundaryFacet();
		};
	}
}

#include <Mesh3d_BoundaryFacetI.hxx>

#endif // !_Mesh3d_BoundaryFacet_Header
