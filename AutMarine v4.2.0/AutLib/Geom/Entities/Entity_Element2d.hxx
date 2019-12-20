#pragma once
#ifndef _Entity_Element2d_Header
#define _Entity_Element2d_Header

#include <Entity_Edge2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Element2d
		{

		private:

			Global_Handle(Entity_Node2d) theNodes_[3];
			Global_Handle(Entity_Edge2d) theEdges_[3];

			Standard_Integer theIndex_;

			Global_Handle(Entity_Element2d) theNeighbors_[3];

		public:

			Entity_Element2d();

			Entity_Element2d(const Standard_Integer Index);

			Global_Handle(Entity_Node2d) Node0() const;

			Global_Handle(Entity_Node2d) Node1() const;

			Global_Handle(Entity_Node2d) Node2() const;

			Global_Handle(Entity_Edge2d) Edge0() const;

			Global_Handle(Entity_Edge2d) Edge1() const;

			Global_Handle(Entity_Edge2d) Edge2() const;

			Global_Handle(Entity_Element2d) Neighbor0() const;

			Global_Handle(Entity_Element2d) Neighbor1() const;

			Global_Handle(Entity_Element2d) Neighbor2() const;

			Global_Handle(Entity_Node2d) Node(const Standard_Integer Index) const;

			Global_Handle(Entity_Edge2d) Edge(const Standard_Integer Index) const;

			Global_Handle(Entity_Element2d) Neighbor(const Standard_Integer Index) const;

			Standard_Integer Index() const;

			//! Throw an exception
			Standard_Integer OppositeVertexIndex(const Entity_Edge2d & Edge) const;

			//! Throw an exception
			Standard_Integer OppositeVertexIndex(const Entity_Element2d & Element) const;

			Global_Handle(Entity_Node2d) OppositeVertex(const Entity_Edge2d & Edge) const;

			Global_Handle(Entity_Node2d) OppositeVertex(const Entity_Element2d & Element) const;

			void SetIndex(const Standard_Integer Value);

			void SetNode0(Global_Handle(Entity_Node2d) Node);

			void SetNode1(Global_Handle(Entity_Node2d) Node);

			void SetNode2(Global_Handle(Entity_Node2d) Node);

			void SetEdge0(Global_Handle(Entity_Edge2d) Edge);

			void SetEdge1(Global_Handle(Entity_Edge2d) Edge);

			void SetEdge2(Global_Handle(Entity_Edge2d) Edge);

			void SetNeighbor0(Global_Handle(Entity_Element2d) Element);

			void SetNeighbor1(Global_Handle(Entity_Element2d) Element);

			void SetNeighbor2(Global_Handle(Entity_Element2d) Element);

			void SetNode(const Standard_Integer Index, Global_Handle(Entity_Node2d) Node);

			void SetEdge(const Standard_Integer Index, Global_Handle(Entity_Edge2d) Edge);

			void SetNeighbor(const Standard_Integer Index, Global_Handle(Entity_Element2d) Element);
		};
	}
}

#include <Entity_Element2dI.hxx>

#endif // !_Entity_Element2d_Header
