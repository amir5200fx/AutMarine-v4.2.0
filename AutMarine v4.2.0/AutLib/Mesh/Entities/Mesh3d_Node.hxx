#pragma once
#ifndef _Mesh3d_Node_Header
#define _Mesh3d_Node_Header

#include <Geom_Pnt3d.hxx>
#include <TColMesh3d_HAvlTreeOfEdge.hxx>
#include <TColMesh3d_HAvlTreeOfFacet.hxx>
#include <TColMesh3d_HAvlTreeOfElement.hxx>
#include <TColMesh3d_HAry1dOfEdge.hxx>
#include <TColMesh3d_HAry1dOfFacet.hxx>
#include <TColMesh3d_HAry1dOfElement.hxx>
#include <TColMesh3d_HBasicQueueOfEdge.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		
		class Mesh3d_Node
		{

		private:

			Geom_Pnt3d theCoord_;

			Standard_Integer theIndex_;

			Standard_Real theRadius_;
			Standard_Real theMaxL_;

			TColMesh3d_HAvlTreeOfEdge theFrontEdges_;
			TColMesh3d_HAvlTreeOfFacet theFrontFacets_;

			TColMesh3d_HAvlTreeOfEdge theEdges_;
			TColMesh3d_HAvlTreeOfFacet theFacets_;
			TColMesh3d_HAvlTreeOfElement theElements_;

		public:

			Mesh3d_Node();

			Mesh3d_Node(const Standard_Integer Index, const Geom_Pnt3d& Coord);

			virtual ~Mesh3d_Node();

			const Geom_Pnt3d& Coord() const;

			Standard_Integer Index() const;

			Standard_Integer NbFrontEdges() const;

			Standard_Integer NbFrontFacets() const;

			Standard_Integer NbEdges() const;

			Standard_Integer NbFacets() const;

			Standard_Integer NbElements() const;

			Standard_Real Radius() const;

			Standard_Real MaxAdjLength() const;

			TColMesh3d_HAry1dOfEdge RetriveFrontEdges() const;

			TColMesh3d_HAry1dOfFacet RetrieveFrontFacets() const;

			TColMesh3d_HAry1dOfEdge RetrieveEdges() const;

			TColMesh3d_HAry1dOfFacet RetrieveFacets() const;

			TColMesh3d_HAry1dOfElement RetrieveElements() const;

			Standard_Boolean IsFrontEdgesEmpty() const;

			Standard_Boolean IsFrontFacetsEmpty() const;

			Standard_Boolean IsEdgesEmpty() const;

			Standard_Boolean IsFacetsEmpty() const;

			Standard_Boolean IsElementsEmpty() const;

			Standard_Boolean IsContainAtMesh(Global_Handle(Mesh3d_Edge) theEdge) const;

			Standard_Boolean IsContainAtMesh(Global_Handle(Mesh3d_Facet) theFacet) const;

			Standard_Boolean IsContainAtMesh(Global_Handle(Mesh3d_Element) theElement) const;

			Standard_Boolean IsContainAtFront(Global_Handle(Mesh3d_Edge) theEdge) const;

			Standard_Boolean IsContainAtFront(Global_Handle(Mesh3d_Facet) theFacet) const;

			Standard_Boolean IsOnFront() const;

			void SetCoord(const Geom_Pnt3d& Coord);

			void SetIndex(const Standard_Integer Index);

			void SetRadius(const Standard_Real Value);

			void SetMaxAdjLength(const Standard_Real Value);

			void RetrieveFrontsTo(TColMesh3d_HAry1dOfEdge& Edges) const;

			void RetrieveFrontsTo(TColMesh3d_HAry1dOfFacet& Facets) const;

			void RetrieveFrontsTo(TColMesh3d_HBasicQueueOfEdge& theEdges) const;

			void RetrievTo(TColMesh3d_HAry1dOfEdge& Edges) const;

			void RetrieveTo(TColMesh3d_HAry1dOfFacet& Facets) const;

			void RetrieveTo(TColMesh3d_HAry1dOfElement& Elements) const;

			// Throw an exception
			void InsertToFronts(Global_Handle(Mesh3d_Edge) Edge);

			// Throw an exception
			void InsertToFronts(Global_Handle(Mesh3d_Facet) Facet);

			// Throw an exception
			void InsertToEdges(Global_Handle(Mesh3d_Edge) Edge);

			// Throw an exception
			void InsertToFacets(Global_Handle(Mesh3d_Facet) Facet);

			// Throw an exception
			void InsertToElements(Global_Handle(Mesh3d_Element) Element);

			// Throw an exception
			void RemoveFromFronts(Global_Handle(Mesh3d_Edge) Edge);

			// Throw an exception
			void RemoveFromFronts(Global_Handle(Mesh3d_Facet) Facet);

			// Throw an exception
			void RemoveFromEdges(Global_Handle(Mesh3d_Edge) Edge);

			// Throw an exception
			void RemoveFromFacets(Global_Handle(Mesh3d_Facet) Facet);

			// Throw an exception
			void RemoveFromElements(Global_Handle(Mesh3d_Element) Element);
		};
	}
}

using AutLib::MeshLib::Mesh3d_Node;

#include <Mesh3d_NodeI.hxx>

#endif // !_Mesh3d_Node_Header
