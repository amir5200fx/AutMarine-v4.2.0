#pragma once
#ifndef _GeoMesh_TetrahedronMesh_Header
#define _GeoMesh_TetrahedronMesh_Header

#include <Entity_Element3d.hxx>
#include <TColEntity_HAvlTreeOfNode3d.hxx>
#include <TColEntity_HAvlTreeOfEdge3d.hxx>
#include <TColEntity_HAvlTreeOfFacet.hxx>
#include <TColEntity_HAvlTreeOfElement3d.hxx>
#include <TColEntity_HAry1dOfNode3d.hxx>
#include <TColEntity_HAry1dOfEdge3d.hxx>
#include <TColEntity_HAry1dOfFacet.hxx>
#include <TColEntity_HAry1dOfElement3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Tetrahedralization;

		class GeoMesh_TetrahedronMesh
		{

		private:

			TColEntity_HAvlTreeOfNode3d theNodes_;
			TColEntity_HAvlTreeOfEdge3d theEdges_;
			TColEntity_HAvlTreeOfFacet theFacets_;
			TColEntity_HAvlTreeOfElement3d theElements_;

			Standard_Integer theNbNodes_;
			Standard_Integer theNbEdges_;
			Standard_Integer theNbFacets_;
			Standard_Integer thenbElements_;

			Standard_Boolean IsDone_;

			TColEntity_HAry1dOfNode3d theNodesSequence_;
			TColEntity_HAry1dOfEdge3d theEdgesSequence_;
			TColEntity_HAry1dOfFacet theFacetsSequence_;
			TColEntity_HAry1dOfElement3d theElementsSequence_;

		public:

			GeoMesh_TetrahedronMesh();

			~GeoMesh_TetrahedronMesh() { ReleaseMemory(); }

			Standard_Integer NbNodes() const;

			Standard_Integer NbEdges() const;

			Standard_Integer NbFacets() const;

			Standard_Integer NbElements() const;

			//Throw an exception if conflict data has been occured
			Global_Handle(Entity_Element3d) TetrahedronLocation(Global_Handle(Entity_Element3d) Start, const Geom_Pnt3d& Coord) const;

			Global_Handle(Entity_Element3d) FirstElement() const;

			const TColEntity_HAry1dOfNode3d& NodesSequence() const;

			const TColEntity_HAry1dOfEdge3d& EdgesSequence() const;

			const TColEntity_HAry1dOfFacet& FacetsSequence() const;

			const TColEntity_HAry1dOfElement3d& ElementsSequence() const;

			Entity_Tetrahedralization Static() const;

			void Construct(const Entity_Tetrahedralization& Tetrahedralization);

			//! Throw an exception
			void Insert(Global_Handle(Entity_Node3d) Node);

			//! Throw an exception
			void Insert(Global_Handle(Entity_Edge3d) Edge);

			//! Throw an exception
			void Insert(Global_Handle(Entity_Facet) Facet);

			//! Throw an exception
			void Insert(Global_Handle(Entity_Element3d) Element);

			//! Throw an exception
			void Remove(Global_Handle(Entity_Node3d) Node);

			//! Throw an exception
			void Remove(Global_Handle(Entity_Edge3d) Edge);

			//! Throw an exception
			void Remove(Global_Handle(Entity_Facet) Facet);

			//! Throw an exception
			void Remove(Global_Handle(Entity_Element3d) Element);

			void RetrieveTo(TColEntity_HAry1dOfNode3d& Nodes) const;

			void RetrieveTo(TColEntity_HAry1dOfEdge3d& Edges) const;

			void RetrieveTo(TColEntity_HAry1dOfFacet& Facets) const;

			void RetrieveTo(TColEntity_HAry1dOfElement3d& Elements) const;

			void ReleaseMemory();

			void ExportToPlt(fstream& File) const;

			void ExportBoundaryFacetsToPlt(fstream& File) const;

		private:

			Standard_Boolean IsPointOnRightSide(const Geom_Pnt3d& theCoord, const Global_Handle(Entity_Facet) Facet) const;

			Standard_Boolean IsPointOnLeftSide(const Geom_Pnt3d& theCoord, const Global_Handle(Entity_Facet) Facet) const;

			Standard_Boolean IsPointRightTriangle(const Geom_Pnt3d& theCoord, const Geom_Pnt3d& theP1, const Geom_Pnt3d& theP2, const Geom_Pnt3d& theP3) const;

			Standard_Boolean IsPointRightTriangle(const Geom_Pnt3d& Point, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3, const Standard_Real Tolerance, Standard_Boolean& Undefiend) const;
		};
	}
}

#include <GeoMesh_TetrahedronMeshI.hxx>

#endif // !_GeoMesh_TetrahedronMesh_Header
