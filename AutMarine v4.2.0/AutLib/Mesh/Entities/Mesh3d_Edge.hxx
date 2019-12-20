#pragma once
#ifndef _Mesh3d_Edge_Header
#define _Mesh3d_Edge_Header

#include <Mesh3d_Node.hxx>
#include <TColMesh3d_HBasicQueueOfFacet.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		
		class Mesh3d_Edge
		{

		private:

			Global_Handle(Mesh3d_Node) theNodes_[2];

			Standard_Integer theIndex_;

			Standard_Real theLength_;

			Standard_Boolean IsCavity_;

			TColMesh3d_HAvlTreeOfFacet theFrontFacet_;

			TColMesh3d_HAvlTreeOfFacet theFacets_;
			TColMesh3d_HAvlTreeOfElement theElements_;

		public:

			Mesh3d_Edge();

			Mesh3d_Edge(const Standard_Integer Index, const Standard_Real Length, Global_Handle(Mesh3d_Node) Node0, Global_Handle(Mesh3d_Node) Node1);

			virtual ~Mesh3d_Edge() {}

			Geom_Pnt3d Centre() const;

			Standard_Integer Index() const;

			Standard_Integer NbFrontFacets() const;

			Standard_Integer NbFacets() const;

			Standard_Integer NbElements() const;

			Standard_Real Length() const;

			Standard_Boolean IsCavity() const;

			Standard_Boolean IsOnFront() const;

			TColMesh3d_HAry1dOfFacet RetrieveFrontFacets() const;

			TColMesh3d_HAry1dOfFacet RetrieveFacets() const;

			TColMesh3d_HAry1dOfElement RetrieveElements() const;

			Standard_Boolean IsFrontFacetsEmpty() const;

			Standard_Boolean IsOrphan() const;

			Standard_Boolean IsFacetsEmpty() const;

			Standard_Boolean IsElementsEmpty() const;

			Standard_Boolean IsContainAtMesh(Global_Handle(Mesh3d_Facet) theFacet) const;

			Standard_Boolean IsContainAtMesh(Global_Handle(Mesh3d_Element) theElement) const;

			Standard_Boolean IsContainAtFront(Global_Handle(Mesh3d_Facet) theFacet) const;

			Global_Handle(Mesh3d_Node) Node0() const;

			Global_Handle(Mesh3d_Node) Node1() const;

			Global_Handle(Mesh3d_Node) Node(const Standard_Integer Index) const;

			Global_Handle(Mesh3d_Node)& Node(const Standard_Integer Index);

			void Reverse();

			void SetAsCavity();

			void SetAsNotCavity();

			void SetIndex(const Standard_Integer Index);

			void SetLength(const Standard_Real Length);

			void SetNode(const Standard_Integer Index, Global_Handle(Mesh3d_Node) Node);

			void RetrieveFrontsTo(TColMesh3d_HAry1dOfFacet& Facets) const;

			void RetrieveFrontsTo(TColMesh3d_HBasicQueueOfFacet& theFacets) const;

			void RetrieveTo(TColMesh3d_HAry1dOfFacet& Facets) const;

			void RetrieveTo(TColMesh3d_HAry1dOfElement& Elements) const;

			// Throw an exception
			void InsertToFronts(Global_Handle(Mesh3d_Facet) Facet);

			// Throw an exception
			void InsertToFacets(Global_Handle(Mesh3d_Facet) Facet);

			// Throw an exception
			void InsertToElements(Global_Handle(Mesh3d_Element) Element);

			// Throw an exception
			void RemoveFromFronts(Global_Handle(Mesh3d_Facet) Facet);

			// Throw an exception
			void RemoveFromFacets(Global_Handle(Mesh3d_Facet) Facet);

			// Throw an exception
			void RemoveFromElements(Global_Handle(Mesh3d_Element) Element);
		};
	}
}

using AutLib::MeshLib::Mesh3d_Edge;

#include <Mesh3d_EdgeI.hxx>

#endif // !_Mesh3d_Edge_Header
