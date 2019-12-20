#pragma once
#ifndef _GeoMesh_TriangleMesh2d_Header
#define _GeoMesh_TriangleMesh2d_Header

#include <Entity_Element2d.hxx>
#include <TColEntity_HAvlTreeOfNode2d.hxx>
#include <TColEntity_HAvlTreeOfEdge2d.hxx>
#include <TColEntity_HAvlTreeOfElement2d.hxx>
#include <TColEntity_HAry1dOfNode2d.hxx>
#include <TColEntity_HAry1dOfEdge2d.hxx>
#include <TColEntity_HAry1dOfElement2d.hxx>
#include <TGeoMesh_TriangleMesh2dBoundaryList.hxx>
#include <GeoMesh_TriangleMesh2dOutterBoundary.hxx>
#include <GeoMesh_TriangleMesh2dInnerBoundary.hxx>
#include <GeoMesh_TriangleMesh2dInnerBoundaryList.hxx>


namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Polygon2d;
		class Entity_Triangulation2d;

		class GeoMesh_TriangleMesh2d
		{

		public:

			typedef TGeoMesh_TriangleMesh2dBoundaryList BoundaryEdges;

		private:

			TColEntity_HAvlTreeOfNode2d theNodes_;
			TColEntity_HAvlTreeOfEdge2d theEdges_;
			TColEntity_HAvlTreeOfElement2d theElements_;

			Standard_Integer theNbNodes_;
			Standard_Integer theNbEdges_;
			Standard_Integer thenbElements_;

			BoundaryEdges theBoundaries_;

			Standard_Boolean IsDone_;

			TColEntity_HAry1dOfNode2d theNodesSequence_;
			TColEntity_HAry1dOfEdge2d theEdgesSequence_;
			TColEntity_HAry1dOfElement2d theElementsSequence_;

		public:

			GeoMesh_TriangleMesh2d();

			~GeoMesh_TriangleMesh2d() { ReleaseMemory(); }

			Standard_Integer NbNodes() const;

			Standard_Integer NbEdges() const;

			Standard_Integer NbElements() const;

			Standard_Integer NbBoundaries() const;

			Global_Handle(Entity_Element2d) TriangleLocation(Global_Handle(Entity_Element2d) Start, const Geom_Pnt2d& Coord) const;

			Global_Handle(Entity_Element2d) FirstElement() const;

			const TColEntity_HAry1dOfNode2d& NodesSequence() const;

			const TColEntity_HAry1dOfEdge2d& EdgesSequence() const;

			const TColEntity_HAry1dOfElement2d& ElementsSequence() const;

			Entity_Polygon2d GetBoundaryPolygon(const Standard_Integer Index) const;

			Entity_Triangulation2d Static() const;

			void Construct(const Entity_Triangulation2d& Triangulation);

			template<typename T>
			void LaplacianSmoothing(ADT_Ary1d<T>& Values, const Standard_Integer NbIterations, const Standard_Real Factor) const;

			//! Throw an exception
			void Insert(Global_Handle(Entity_Node2d) Node);

			//! Throw an exception
			void Insert(Global_Handle(Entity_Edge2d) Edge);

			//! Throw an exception
			void Insert(Global_Handle(Entity_Element2d) Element);

			//! Throw an exception
			void Remove(Global_Handle(Entity_Node2d) Node);

			//! Throw an exception
			void Remove(Global_Handle(Entity_Edge2d) Edge);

			//! Throw an exception
			void Remove(Global_Handle(Entity_Element2d) Element);

			void RetrieveTo(TColEntity_HAry1dOfNode2d& Nodes) const;

			void RetrieveTo(TColEntity_HAry1dOfEdge2d& Edges) const;

			void RetrieveTo(TColEntity_HAry1dOfElement2d& Elements) const;

			void ReleaseMemory();

			void ExportEdgesAround(const Standard_Integer Index, fstream& File) const;

			void ExportToPlt(fstream& File) const;
		};
	}
}

#include <GeoMesh_TriangleMesh2dI.hxx>

#endif // !_GeoMesh_TriangleMesh2d_Header
