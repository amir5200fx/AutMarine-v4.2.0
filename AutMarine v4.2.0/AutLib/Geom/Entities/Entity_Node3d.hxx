#pragma once
#ifndef _Entity_Node3d_Header
#define _Entity_Node3d_Header

#include <Geom_Pnt3d.hxx>
#include <TColEntity_HBasicQueueOfEdge3d.hxx>
#include <TColEntity_HBasicQueueOfFacet.hxx>
#include <TColEntity_HBasicQueueOfElement3d.hxx>
#include <TColEntity_HAry1dOfEdge3d.hxx>
#include <TColEntity_HAry1dOfFacet.hxx>
#include <TColEntity_HAry1dOfElement3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Node3d
		{

		private:

			Geom_Pnt3d theCoord_;

			Standard_Integer theIndex_;

			Standard_Boolean IsOnBoundary_;

			TColEntity_HBasicQueueOfEdge3d theEdges_;
			TColEntity_HBasicQueueOfFacet theFacets_;
			TColEntity_HBasicQueueOfElement3d theElements_;

		public:

			Entity_Node3d();

			Entity_Node3d(const Standard_Integer Index, const Geom_Pnt3d& Coord);

			void SetIndex(const Standard_Integer Index);

			void SetCoord(const Geom_Pnt3d& Coord);

			void SetAsBoundary();

			void Edges(TColEntity_HAry1dOfEdge3d& Edges) const;

			void Facets(TColEntity_HAry1dOfFacet& Facets) const;

			void Elements(TColEntity_HAry1dOfElement3d& Elements) const;

			void InsertToEdges(Global_Handle(Entity_Edge3d) Edge);

			void InsertToFacets(Global_Handle(Entity_Facet) Facet);

			void InsertToElements(Global_Handle(Entity_Element3d) Element);

			Standard_Integer Index() const;

			Standard_Integer NbEdges() const;

			Standard_Integer NbFacets() const;

			Standard_Integer NbElements() const;

			const Geom_Pnt3d& Coord() const;

			TColEntity_HAry1dOfEdge3d Edges() const;

			TColEntity_HAry1dOfFacet Facets() const;

			TColEntity_HAry1dOfElement3d Elements() const;
		};
	}
}

#include <Entity_Node3dI.hxx>

#endif // !_Entity_Node3d_Header
