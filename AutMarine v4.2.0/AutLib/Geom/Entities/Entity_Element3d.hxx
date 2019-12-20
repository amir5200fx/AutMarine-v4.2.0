#pragma once
#ifndef _Entity_Element3d_Header
#define _Entity_Element3d_Header

#include <Entity_Edge3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Element3d
		{

		private:

			Global_Handle(Entity_Node3d) theNodes_[4];
			Global_Handle(Entity_Edge3d) theEdges_[6];
			Global_Handle(Entity_Facet) theFacets_[4];

			Standard_Integer theIndex_;

			Standard_Real theVolume_;
			Standard_Real thel_;

			Global_Handle(Entity_Element3d) theNeighbors_[4];

		public:

			Entity_Element3d();

			Entity_Element3d(const Standard_Integer Index);

			Global_Handle(Entity_Node3d) Node0() const;

			Global_Handle(Entity_Node3d) Node1() const;

			Global_Handle(Entity_Node3d) Node2() const;

			Global_Handle(Entity_Node3d) Node3() const;

			Global_Handle(Entity_Edge3d) Edge0() const;

			Global_Handle(Entity_Edge3d) Edge1() const;

			Global_Handle(Entity_Edge3d) Edge2() const;

			Global_Handle(Entity_Edge3d) Edge3() const;

			Global_Handle(Entity_Edge3d) Edge4() const;

			Global_Handle(Entity_Edge3d) Edge5() const;

			Global_Handle(Entity_Facet) Facet0() const;

			Global_Handle(Entity_Facet) Facet1() const;

			Global_Handle(Entity_Facet) Facet2() const;

			Global_Handle(Entity_Facet) Facet3() const;

			Global_Handle(Entity_Element3d) Neighbor0() const;

			Global_Handle(Entity_Element3d) Neighbor1() const;

			Global_Handle(Entity_Element3d) Neighbor2() const;

			Global_Handle(Entity_Element3d) Neighbor3() const;

			Global_Handle(Entity_Node3d) Node(const Standard_Integer Index) const;

			Global_Handle(Entity_Edge3d) Edge(const Standard_Integer Index) const;

			Global_Handle(Entity_Facet) Facet(const Standard_Integer Index) const;

			Global_Handle(Entity_Element3d) Neighbor(const Standard_Integer Index) const;

			Standard_Integer Index() const;

			//! Throw an exception
			Standard_Integer OppositeVertexIndex(const Entity_Facet & Facet) const;

			//! Throw an exception
			Standard_Integer OppositeVertexIndex(const Entity_Element3d & Element) const;

			Standard_Real Volume() const;

			Standard_Real Characteristic() const;

			Global_Handle(Entity_Node3d) OppositeVertex(const Entity_Facet & Facet) const;

			Global_Handle(Entity_Node3d) OppositeVertex(const Entity_Element3d & Element) const;

			void SetIndex(const Standard_Integer Value);

			void SetNode0(Global_Handle(Entity_Node3d) Node);

			void SetNode1(Global_Handle(Entity_Node3d) Node);

			void SetNode2(Global_Handle(Entity_Node3d) Node);

			void SetNode3(Global_Handle(Entity_Node3d) Node);

			void SetEdge0(Global_Handle(Entity_Edge3d) Edge);

			void SetEdge1(Global_Handle(Entity_Edge3d) Edge);

			void SetEdge2(Global_Handle(Entity_Edge3d) Edge);

			void SetEdge3(Global_Handle(Entity_Edge3d) Edge);

			void SetEdge4(Global_Handle(Entity_Edge3d) Edge);

			void SetEdge5(Global_Handle(Entity_Edge3d) Edge);

			void SetNeighbor0(Global_Handle(Entity_Element3d) Element);

			void SetNeighbor1(Global_Handle(Entity_Element3d) Element);

			void SetNeighbor2(Global_Handle(Entity_Element3d) Element);

			void SetNeighbor3(Global_Handle(Entity_Element3d) Element);

			void SetNode(const Standard_Integer Index, Global_Handle(Entity_Node3d) Node);

			void SetEdge(const Standard_Integer Index, Global_Handle(Entity_Edge3d) Edge);

			void SetFacet(const Standard_Integer Index, Global_Handle(Entity_Facet) Facet);

			void SetNeighbor(const Standard_Integer Index, Global_Handle(Entity_Element3d) Element);

			void CalcVolume();
		};
	}
}

#include <Entity_Element3dI.hxx>

#endif // !_Entity_Element3d_Header
