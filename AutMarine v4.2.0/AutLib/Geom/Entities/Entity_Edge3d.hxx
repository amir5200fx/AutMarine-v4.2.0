#pragma once
#ifndef _Entity_Edge3d_Header
#define _Entity_Edge3d_Header

#include <Entity_Node3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Edge3d
		{

		private:

			Global_Handle(Entity_Node3d) theNodes_[2];

			Standard_Integer theIndex_;

			Standard_Boolean IsOnBoundary_;

			TColEntity_HBasicQueueOfFacet theFacets_;

		public:

			Entity_Edge3d();

			Entity_Edge3d(const Standard_Integer Index, Global_Handle(Entity_Node3d) Node0, Global_Handle(Entity_Node3d) Node1);

			Standard_Integer Index() const;

			Standard_Boolean IsOnBoundary() const;

			Global_Handle(Entity_Node3d) Node(const Standard_Integer Index) const;

			Global_Handle(Entity_Node3d)& Node(const Standard_Integer Index);

			TColEntity_HAry1dOfFacet Facets() const;

			void Facets(TColEntity_HAry1dOfFacet& Facets) const;

			void InsertToFacets(Global_Handle(Entity_Facet) Facet);

			void SetIndex(const Standard_Integer Index);

			void SetNode(const Standard_Integer Index, Global_Handle(Entity_Node3d) Node);

			void SetAsBoundary();

			void SetAsNonBoundary();
		};
	}
}

#include <Entity_Edge3dI.hxx>

#endif // !_Entity_Edge3d_Header
