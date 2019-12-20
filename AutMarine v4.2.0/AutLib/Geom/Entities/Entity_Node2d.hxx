#pragma once
#ifndef _Entity_Node2d_Header
#define _Entity_Node2d_Header

#include <Geom_Pnt2d.hxx>
#include <TColEntity_HBasicQueueOfEdge2d.hxx>
#include <TColEntity_HBasicQueueOfElement2d.hxx>
#include <TColEntity_HAry1dOfEdge2d.hxx>
#include <TColEntity_HAry1dOfElement2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Node2d
		{

		private:

			Geom_Pnt2d theCoord_;

			Standard_Integer theIndex_;

			Standard_Boolean IsOnBoundary_;

			TColEntity_HBasicQueueOfEdge2d theEdges_;
			TColEntity_HBasicQueueOfElement2d theElements_;

		public:

			Entity_Node2d();

			Entity_Node2d(const Standard_Integer Index, const Geom_Pnt2d& Coord);

			void SetIndex(const Standard_Integer Index);

			void SetCoord(const Geom_Pnt2d& Coord);

			void SetAsBoundary();

			void Edges(TColEntity_HAry1dOfEdge2d& Edges) const;

			void Elements(TColEntity_HAry1dOfElement2d& Elements) const;

			void InsertToEdges(Global_Handle(Entity_Edge2d) Edge);

			void InsertToElements(Global_Handle(Entity_Element2d) Element);

			Standard_Integer Index() const;

			Standard_Integer NbEdges() const;

			Standard_Integer NbElements() const;

			const Geom_Pnt2d& Coord() const;

			TColEntity_HAry1dOfEdge2d Edges() const;

			TColEntity_HAry1dOfElement2d Elements() const;


		};
	}
}

#include <Entity_Node2dI.hxx>

#endif // !_Entity_Node2d_Header
