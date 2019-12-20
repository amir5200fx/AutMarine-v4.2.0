#pragma once
#ifndef _Mesh2d_Mesh_Header
#define _Mesh2d_Mesh_Header

#include <TColMesh2d_HAvlTreeOfNode.hxx>
#include <TColMesh2d_HAvlTreeOfEdge.hxx>
#include <TColMesh2d_HAvlTreeOfElement.hxx>
#include <TColMesh2d_HAry1dOfNode.hxx>
#include <TColMesh2d_HAry1dOfEdge.hxx>
#include <TColMesh2d_HAry1dOfElement.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColEntity_Ary1dOfTriangleIndex.hxx>
#include <TColEntity_Ary1dOfEdgeIndex.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <Standard_Stream.hxx>


namespace AutLib
{

	namespace GeoLib
	{
		class Entity_Triangulation2d;
	}

	namespace MeshLib
	{
		
		class Mesh2d_SizeMap;
		class Mesh2d_QualityMap;

		class Mesh2d_Mesh
		{

		private:

			TColMesh2d_HAvlTreeOfNode theNodes_;

			TColMesh2d_HAvlTreeOfEdge theEdges_;

			TColMesh2d_HAvlTreeOfElement theElements_;

			TColMesh2d_HAvlTreeOfNode theFrontNodes_;
			TColMesh2d_HAvlTreeOfEdge theFrontEdges_;

			mutable TColStd_Ary1dOfReal theQuality_;

			Standard_Integer theNbNodes_;
			Standard_Integer theNbEdges_;
			Standard_Integer thenbElements_;

			Standard_String theName_;

		public:

			Mesh2d_Mesh();

			virtual ~Mesh2d_Mesh();

			Standard_Integer NbNodes() const;

			Standard_Integer NbEdges() const;

			Standard_Integer NbElements() const;

			Standard_Integer& NbNodes();

			Standard_Integer& NbEdges();

			Standard_Integer& NbElements();

			Standard_Real WorstQuality(const Mesh2d_Node& theNode, const Mesh2d_SizeMap& theSizeMap, const Mesh2d_QualityMap& theQualityMap) const;

			TColMesh2d_HAry1dOfNode SortedNodes() const;

			TColMesh2d_HAry1dOfEdge SortedEdges() const;

			TColMesh2d_HAry1dOfElement SortedElements() const;

			Standard_String Name() const;

			M_GEO Entity_Triangulation2d Static() const;

			void SetName(const Standard_String theName);

			//! Throw an exception
			void InsertToMesh(Global_Handle(Mesh2d_Node) Node);

			//! Throw an exception
			void InsertToMesh(Global_Handle(Mesh2d_Edge) Edge);

			//! Throw an exception
			void InsertToMesh(Global_Handle(Mesh2d_Element) Element);

			//! Throw an exception
			void InsertToMesh(const TColMesh2d_HAry1dOfNode& Nodes);

			//! Throw an exception
			void InsertToMesh(const TColMesh2d_HAry1dOfEdge& Edges);

			//! Throw an exception
			void InsertToFronts(Global_Handle(Mesh2d_Node) Node);

			//! Throw an exception
			void InsertToFronts(Global_Handle(Mesh2d_Edge) Edge);

			//! Throw an exception
			void InsertToFronts(const TColMesh2d_HAry1dOfNode& Nodes);

			//! Throw an exception
			void RemoveFromMesh(Global_Handle(Mesh2d_Node) Node);

			//! Throw an exception
			void RemoveFromMesh(Global_Handle(Mesh2d_Edge) Edge);

			//! Throw an exception
			void RemoveFromMesh(Global_Handle(Mesh2d_Element) Element);

			//! Throw an exception
			void RemoveFromFronts(Global_Handle(Mesh2d_Node) Node);

			//! Throw an exception
			void RemoveFromFronts(Global_Handle(Mesh2d_Edge) Edge);

			void RetrieveTo(TColMesh2d_HAry1dOfNode& Nodes) const;

			void RetrieveTo(TColMesh2d_HAry1dOfEdge& Edges) const;

			void RetrieveTo(TColMesh2d_HAry1dOfElement& Elements) const;

			void RetrieveFrontsTo(TColMesh2d_HAry1dOfNode& Nodes) const;

			void RetrieveFrontsTo(TColMesh2d_HAry1dOfEdge& Edges) const;

			void RetrieveSortedTo(TColGeom_Ary1dOfPnt2d& Points) const;

			void RetrieveSortedTo(TColEntity_Ary1dOfEdgeIndex& Edges) const;

			void RetrieveSortedTo(TColEntity_Ary1dOfTriangleIndex& Elements) const;

			void NodesCompactNumbering() const;

			void EdgesCompactNumbering() const;

			void ElementsCompactNumbering() const;

			void CompactNumbering() const;

			void CalcQuality(const Mesh2d_SizeMap& theSizeMap) const;

			void ExportEdgesToPlt(const TColMesh2d_HAry1dOfEdge& theEdges, fstream& File) const;

			void ExportElementsToPlt(const TColMesh2d_HAry1dOfElement& theElements, fstream & File) const;

			void ExportElementsToPlt(fstream & File) const;

			void ExportQualityToPlt(fstream& File, const Mesh2d_SizeMap& theSizeMap) const;

			void ReportQualityTo(Standard_OStream& Ostream, const Mesh2d_SizeMap& theSizeMap) const;

			void LaplacianSmoothing(const Standard_Integer NbLevels, const Standard_Real UnderRelaxation, Standard_Real(*Distance)(const Geom_Pnt2d&, const Geom_Pnt2d&, const Mesh2d_SizeMap&), const Mesh2d_SizeMap& Map, const Standard_Boolean Verbose);

			void ReleaseMemory();
		};
	}
}

#include <Mesh2d_MeshI.hxx>

#endif // !_Mesh2d_Mesh_Header
