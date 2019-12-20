#pragma once
#ifndef _Mesh3d_Element_Header
#define _Mesh3d_Element_Header

#include <Mesh3d_Facet.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		
		class Mesh3d_Element
		{

		private:

			Global_Handle(Mesh3d_Node) theNodes_[4];

			Global_Handle(Mesh3d_Edge) theEdges_[6];

			Global_Handle(Mesh3d_Facet) theFacets_[4];

			Global_Handle(Mesh3d_Element) theNeighbors_[4];

			Standard_Integer theIndex_;

		public:

			Mesh3d_Element();

			Mesh3d_Element(const Standard_Integer Index);

			Global_Handle(Mesh3d_Node) Node(const Standard_Integer Index) const;

			Global_Handle(Mesh3d_Edge) Edge(const Standard_Integer Index) const;

			Global_Handle(Mesh3d_Facet) Facet(const Standard_Integer Index) const;

			Global_Handle(Mesh3d_Element) Neighbor(const Standard_Integer Index) const;

			Global_Handle(Mesh3d_Node) OppositeVertex(const Global_Handle(Mesh3d_Facet) Facet) const;

			Global_Handle(Mesh3d_Node) OppositeVertex(const Global_Handle(Mesh3d_Element) Element) const;

			Standard_Integer Index() const;

			Standard_Integer OppositeVertexIndex(const Global_Handle(Mesh3d_Facet) Facet) const;

			Standard_Integer OppositeVertexIndex(const Global_Handle(Mesh3d_Element) Element) const;

			Standard_Real Volume() const;

			Geom_Pnt3d Centre() const;

			void SetIndex(const Standard_Integer Index);

			void SetNode(const Standard_Integer Index, Global_Handle(Mesh3d_Node) Node);

			void SetEdge(const Standard_Integer Index, Global_Handle(Mesh3d_Edge) Edge);

			void SetFacet(const Standard_Integer Index, Global_Handle(Mesh3d_Facet) Facet);

			void SetNeighbor(const Standard_Integer Index, Global_Handle(Mesh3d_Element) Element);

		};
	}
}

using AutLib::MeshLib::Mesh3d_Element;

#include <Mesh3d_ElementI.hxx>

#endif // !_Mesh3d_Element_Header
