#pragma once
#ifndef _Mesh2d_Element_Header
#define _Mesh2d_Element_Header

#include <Mesh2d_Edge.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		
		class Mesh2d_Element
		{

		private:

			Global_Handle(Mesh2d_Node) theNodes_[3];
			Global_Handle(Mesh2d_Edge) theEdges_[3];

			Standard_Integer theIndex_;

			Global_Handle(Mesh2d_Element) theNeighbors_[3];

		public:

			Mesh2d_Element();

			Mesh2d_Element(const Standard_Integer Index);

			Global_Handle(Mesh2d_Node) Node0() const;

			Global_Handle(Mesh2d_Node) Node1() const;

			Global_Handle(Mesh2d_Node) Node2() const;

			Global_Handle(Mesh2d_Edge) Edge0() const;

			Global_Handle(Mesh2d_Edge) Edge1() const;

			Global_Handle(Mesh2d_Edge) Edge2() const;

			Global_Handle(Mesh2d_Element) Neighbor0() const;

			Global_Handle(Mesh2d_Element) Neighbor1() const;

			Global_Handle(Mesh2d_Element) Neighbor2() const;

			Global_Handle(Mesh2d_Node) Node(const Standard_Integer Index) const;

			Global_Handle(Mesh2d_Edge) Edge(const Standard_Integer Index) const;

			Global_Handle(Mesh2d_Element) Neighbor(const Standard_Integer Index) const;

			Standard_Integer Index() const;

			//! Throw an exception
			Standard_Integer OppositeVertexIndex(const Mesh2d_Edge & Edge) const;

			//! Throw an exception
			Standard_Integer OppositeVertexIndex(const Mesh2d_Element & Element) const;

			Global_Handle(Mesh2d_Node) OppositeVertex(const Mesh2d_Edge & Edge) const;

			Global_Handle(Mesh2d_Node) OppositeVertex(const Mesh2d_Element & Element) const;

			void SetIndex(const Standard_Integer Value);

			void SetNode0(Global_Handle(Mesh2d_Node) Node);

			void SetNode1(Global_Handle(Mesh2d_Node) Node);

			void SetNode2(Global_Handle(Mesh2d_Node) Node);

			void SetEdge0(Global_Handle(Mesh2d_Edge) Edge);

			void SetEdge1(Global_Handle(Mesh2d_Edge) Edge);

			void SetEdge2(Global_Handle(Mesh2d_Edge) Edge);

			void SetNeighbor0(Global_Handle(Mesh2d_Element) Element);

			void SetNeighbor1(Global_Handle(Mesh2d_Element) Element);

			void SetNeighbor2(Global_Handle(Mesh2d_Element) Element);

			void SetNode(const Standard_Integer Index, Global_Handle(Mesh2d_Node) Node);

			void SetEdge(const Standard_Integer Index, Global_Handle(Mesh2d_Edge) Edge);

			void SetNeighbor(const Standard_Integer Index, Global_Handle(Mesh2d_Element) Element);


		};
	}
}

using AutLib::MeshLib::Mesh2d_Element;

#include <Mesh2d_ElementI.hxx>

#endif // !_Mesh2d_Element_Header
