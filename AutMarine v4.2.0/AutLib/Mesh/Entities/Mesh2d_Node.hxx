#pragma once
#ifndef _Mesh2d_Node_Header
#define _Mesh2d_Node_Header

#include <Geom_Pnt2d.hxx>
#include <TColMesh2d_HAvlTreeOfEdge.hxx>
#include <TColMesh2d_HAvlTreeOfElement.hxx>
#include <TColMesh2d_HAry1dOfEdge.hxx>
#include <TColMesh2d_HAry1dOfElement.hxx>
#include <TColMesh2d_HBasicQueueOfEdge.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		class Mesh2d_Edge;
		class Mesh2d_Element;

		class Mesh2d_Node
		{

		private:

			Geom_Pnt2d theCoord_;

			Standard_Integer theIndex_;

			Standard_Real theRadius_;
			Standard_Real theMaxL_;

			TColMesh2d_HAvlTreeOfEdge theFront_;
			TColMesh2d_HAvlTreeOfEdge theEdges_;

			TColMesh2d_HAvlTreeOfElement theElements_;

		public:

			Mesh2d_Node();

			Mesh2d_Node(const Standard_Integer Index, const Geom_Pnt2d& Coord);

			virtual ~Mesh2d_Node();

			const Geom_Pnt2d& Coord() const;

			Standard_Integer Index() const;

			Standard_Integer NbFronts() const;

			Standard_Integer NbEdges() const;

			Standard_Integer NbElements() const;

			Standard_Real Radius() const;

			Standard_Real MaxAdjLength() const;

			TColMesh2d_HAry1dOfEdge Edges() const;

			TColMesh2d_HAry1dOfEdge Fronts() const;

			TColMesh2d_HAry1dOfElement Elements() const;

			Standard_Boolean IsOnFront() const;

			Standard_Boolean IsEmptyFront() const;

			Standard_Boolean IsEmptyEdges() const;

			Standard_Boolean IsEmptyElements() const;

			Standard_Boolean IsContainAtFront(Global_Handle(Mesh2d_Edge) Edge) const;

			void SetCoord(const Geom_Pnt2d& Coord);

			void SetIndex(const Standard_Integer Index);

			void SetRadius(const Standard_Real Value);

			void SetMaxAdjLength(const Standard_Real Value);

			void RetrieveFrontsTo(TColMesh2d_HBasicQueueOfEdge& Edges) const;

			void RetrieveEdgesTo(TColMesh2d_HAry1dOfEdge& Edges) const;

			void RetrieveFrontsTo(TColMesh2d_HAry1dOfEdge& Fronts) const;

			void RetrieveElementsTo(TColMesh2d_HAry1dOfElement& Elements) const;

			// Throw an exception
			void InsertToFronts(Global_Handle(Mesh2d_Edge) Edge);

			// Throw an exception
			void InsertToEdges(Global_Handle(Mesh2d_Edge) Edge);

			// Throw an exception
			void InsertToElements(Global_Handle(Mesh2d_Element) Element);

			// Throw an exception
			void RemoveFromFronts(Global_Handle(Mesh2d_Edge) Edge);

			// Throw an exception
			void RemoveFromEdges(Global_Handle(Mesh2d_Edge) Edge);

			// Throw an exception
			void RemoveFromElements(Global_Handle(Mesh2d_Element) Element);
		};
	}
}

using AutLib::MeshLib::Mesh2d_Node;

#include <Mesh2d_NodeI.hxx>

#endif // !_Mesh2d_Node_Header
