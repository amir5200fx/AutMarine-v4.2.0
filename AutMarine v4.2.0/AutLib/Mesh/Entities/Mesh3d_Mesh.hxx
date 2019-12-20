#pragma once
#ifndef _Mesh3d_Mesh_Header
#define _Mesh3d_Mesh_Header

#include <Mesh3d_Node.hxx>
#include <Mesh3d_Edge.hxx>
#include <Mesh3d_Facet.hxx>
#include <Mesh3d_Element.hxx>
#include <QualityMap3d_TypesInfo.hxx>
#include <TColMesh3d_HAvlTreeOfNode.hxx>
#include <TColMesh3d_HAvlTreeOfEdge.hxx>
#include <TColMesh3d_HAvlTreeOfFacet.hxx>
#include <TColMesh3d_HAvlTreeOfElement.hxx>
#include <TColMesh3d_HAry1dOfNode.hxx>
#include <TColMesh3d_HAry1dOfEdge.hxx>
#include <TColMesh3d_HAry1dOfFacet.hxx>
#include <TColMesh3d_HAry1dOfElement.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColEntity_Ary1dOfEdgeIndex.hxx>
#include <TColEntity_Ary1dOfTriangleIndex.hxx>
#include <TColEntity_Ary1dOfTetrahedronIndex.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <TColStd_Ary1dOfReal.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Tetrahedralization;
	}

	namespace MeshLib
	{

		class Mesh3d_SizeMap;

		class Mesh3d_Mesh
		{

		private:

			TColMesh3d_HAvlTreeOfNode theNodes_;

			TColMesh3d_HAvlTreeOfEdge theEdges_;

			TColMesh3d_HAvlTreeOfFacet theFacets_;

			TColMesh3d_HAvlTreeOfElement theElements_;

			TColMesh3d_HAvlTreeOfNode theFrontNodes_;
			TColMesh3d_HAvlTreeOfFacet theFrontFacets_;

			mutable TColStd_Ary1dOfReal theQuality_;

			Standard_Integer theNbNodes_;
			Standard_Integer theNbEdges_;
			Standard_Integer theNbFacets_;
			Standard_Integer theNbElements_;

			Standard_String theName_;

		public:

			Mesh3d_Mesh();

			virtual ~Mesh3d_Mesh();

			Standard_Boolean CheckFront1() const;

			Standard_Integer NbNodes() const;

			Standard_Integer NbEdges() const;

			Standard_Integer NbFacets() const;

			Standard_Integer NbElements() const;

			Standard_Integer& NbNodes();

			Standard_Integer& NbEdges();

			Standard_Integer& NbFacets();

			Standard_Integer& NbElements();

			Standard_String Name() const;

			M_GEO Entity_Tetrahedralization Static() const;

			TColMesh3d_HAry1dOfNode SortedNodes() const;

			TColMesh3d_HAry1dOfEdge SortedEdges() const;

			TColMesh3d_HAry1dOfFacet SortedFacets() const;

			TColMesh3d_HAry1dOfElement SortedElements() const;

			TColStd_Ary1dOfReal& Quality();

			void SetName(const Standard_String theName);

			void CalcQuality(const QualityMap3d_TypesInfo theQualityType = QualityMap3d_TypesInfo::QualityMap3d_VLRMS3RATIO) const;

			void InsertToMesh(const TColMesh3d_HAry1dOfNode& theNodes);

			void InsertToMesh(const TColMesh3d_HAry1dOfEdge& theEdges);

			void InsertToMesh(const TColMesh3d_HAry1dOfFacet& theFacets);

			void InsertToMesh(const TColMesh3d_HAry1dOfElement& theElements);

			void InsertToFronts(const TColMesh3d_HAry1dOfNode& theNodes);

			void InsertToFronts(const TColMesh3d_HAry1dOfFacet& theFacets);

			void RemoveFromMesh(const TColMesh3d_HAry1dOfNode& theNodes);

			void RemoveFromMesh(const TColMesh3d_HAry1dOfEdge& theEdges);

			void RemoveFromMesh(const TColMesh3d_HAry1dOfFacet& theFacets);

			void RemoveFromMesh(const TColMesh3d_HAry1dOfElement& theElements);

			void RemoveFromFronts(const TColMesh3d_HAry1dOfNode& theNodes);

			void RemoveFromFronts(const TColMesh3d_HAry1dOfFacet& theFacets);

			//! Throw an exception
			void InsertToMesh(Global_Handle(Mesh3d_Node) theNode);

			//! Throw an exception
			void InsertToMesh(Global_Handle(Mesh3d_Edge) theEdge);

			//! Throw an exception
			void InsertToMesh(Global_Handle(Mesh3d_Facet) theFacet);

			//! Throw an exception
			void InsertToMesh(Global_Handle(Mesh3d_Element) theElement);

			//! Throw an exception
			void InsertToFronts(Global_Handle(Mesh3d_Node) theNode);

			//! Throw an exception
			void InsertToFronts(Global_Handle(Mesh3d_Facet) theFacet);

			//! Throw an exception
			void RemoveFromMesh(Global_Handle(Mesh3d_Node) theNode);

			//! Throw an exception
			void RemoveFromMesh(Global_Handle(Mesh3d_Edge) theEdge);

			//! Throw an exception
			void RemoveFromMesh(Global_Handle(Mesh3d_Facet) theFacet);

			//! Throw an exception
			void RemoveFromMesh(Global_Handle(Mesh3d_Element) theElement);

			//! Throw an exception
			void RemoveFromFronts(Global_Handle(Mesh3d_Node) theNode);

			//! Throw an exception
			void RemoveFromFronts(Global_Handle(Mesh3d_Facet) theFacet);

			void RetrieveTo(TColMesh3d_HAry1dOfNode& Nodes) const;

			void RetrieveTo(TColMesh3d_HAry1dOfEdge& Edges) const;

			void RetrieveTo(TColMesh3d_HAry1dOfFacet& Facets) const;

			void RetrieveTo(TColMesh3d_HAry1dOfElement& Elements) const;

			void RetrieveFrontsTo(TColMesh3d_HAry1dOfNode& Nodes) const;

			void RetrieveFrontsTo(TColMesh3d_HAry1dOfFacet& Facets) const;

			//void RetrieveFrontsFromEdgesTo(TColMesh3d_HAry1dOfFacet& Facets) const;

			void RetrieveSortedTo(TColGeom_Ary1dOfPnt3d& Points) const;

			void RetrieveSortedTo(TColEntity_Ary1dOfEdgeIndex& Edges) const;

			void RetrieveSortedTo(TColEntity_Ary1dOfTriangleIndex& Facets) const;

			void RetrieveSortedTo(TColEntity_Ary1dOfTetrahedronIndex& Elements) const;

			void NodesCompactNumbering() const;

			void EdgesCompactNumbering() const;

			void FacetsCompactNumbering() const;

			void ElementsCompactNumbering() const;

			void CompactNumbering() const;

			void ExportElementsToPlt(fstream & File) const;

			void ExportQualityToPlt(fstream& File, const QualityMap3d_TypesInfo theQualityType = QualityMap3d_TypesInfo::QualityMap3d_VLRMS3RATIO) const;

			void ExportEdgesToPlt(const TColMesh3d_HAry1dOfEdge& theEdges, fstream& File) const;

			void ExportFacetsToPlt(const TColMesh3d_HAry1dOfFacet& theFacets, fstream& File) const;

			void ExportFacetsWithNormalsToPlt(const TColMesh3d_HAry1dOfFacet& theFacets, fstream& File) const;

			void ExportElementsToPlt(const TColMesh3d_HAry1dOfElement& theElements, fstream& File) const;

			void ReportQuality(Standard_OStream& Ostream, const QualityMap3d_TypesInfo theQualityType = QualityMap3d_TypesInfo::QualityMap3d_VLRMS3RATIO) const;

			void ReleaseMemory();
		};
	}
}

#include <Mesh3d_MeshI.hxx>

#endif // !_Mesh3d_Mesh_Header
