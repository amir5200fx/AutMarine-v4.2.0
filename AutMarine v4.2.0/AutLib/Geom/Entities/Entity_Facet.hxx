#pragma once
#ifndef _Entity_Facet_Header
#define _Entity_Facet_Header

#include <Entity_Edge3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Facet
		{

		private:

			Geom_Pnt3d theNormal_;

			Standard_Integer theIndex_;

			Standard_Boolean IsOnBoundary_;

			Global_Handle(Entity_Node3d) theNodes_[3];
			Global_Handle(Entity_Edge3d) theEdges_[3];

			Global_Handle(Entity_Element3d) theLeft_;
			Global_Handle(Entity_Element3d) theRight_;

		public:

			Entity_Facet(const Standard_Integer Index);

			Entity_Facet(const Standard_Integer Index, Global_Handle(Entity_Node3d) Node0, Global_Handle(Entity_Node3d) Node1, Global_Handle(Entity_Node3d) Node2);

			Global_Handle(Entity_Node3d) Node0() const;

			Global_Handle(Entity_Node3d) Node1() const;

			Global_Handle(Entity_Node3d) Node2() const;

			Global_Handle(Entity_Edge3d) Edge0() const;

			Global_Handle(Entity_Edge3d) Edge1() const;

			Global_Handle(Entity_Edge3d) Edge2() const;

			Global_Handle(Entity_Element3d) LeftElement() const;

			Global_Handle(Entity_Element3d) RightElement() const;

			Global_Handle(Entity_Node3d) Node(const Standard_Integer Index) const;

			Global_Handle(Entity_Edge3d) Edge(const Standard_Integer Index) const;

			Standard_Integer Index() const;

			Standard_Boolean IsOnBoundary() const;

			const Geom_Pnt3d& Normal() const;

			const Geom_Pnt3d& ReverseNormal() const;

			void CalcNormal();

			void SetNode0(Global_Handle(Entity_Node3d) Node);

			void SetNode1(Global_Handle(Entity_Node3d) Node);

			void SetNode2(Global_Handle(Entity_Node3d) Node);

			void SetEdge0(Global_Handle(Entity_Edge3d) Edge);

			void SetEdge1(Global_Handle(Entity_Edge3d) Edge);

			void SetEdge2(Global_Handle(Entity_Edge3d) Edge);

			void SetLeftNeighbor(Global_Handle(Entity_Element3d) Element);

			void SetRightNeighbor(Global_Handle(Entity_Element3d) Element);

			void SetNode(const Standard_Integer Index, Global_Handle(Entity_Node3d) Node);

			void SetEdge(const Standard_Integer Index, Global_Handle(Entity_Edge3d) Edge);

			void SetAsBoundary();

			void SetAsNonBoundary();
		};
	}
}

#include <Entity_FacetI.hxx>

#endif // !_Entity_Facet_Header
