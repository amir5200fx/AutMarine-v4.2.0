#pragma once
#ifndef _Mesh2d_Front_Header
#define _Mesh2d_Front_Header

#include <Mesh2d_Node.hxx>
#include <Mesh2d_Edge.hxx>
#include <TColMesh2d_HeapOfEdge2d.hxx>
#include <TColMesh2d_HAvlTreeOfNode.hxx>
#include <TColMesh2d_HAry1dOfEdge.hxx>
#include <TColMesh2d_HAry1dOfNode.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_Front
		{

		private:

			TColMesh2d_HeapOfEdge2d theSortedEdges_;

			Standard_Integer theLevelNb_;
			Standard_Integer theLevelMaxIndex_;

		public:

			Standard_Integer LevelNumber() const;

			Standard_Integer LevelMaxIndex() const;

			Standard_Boolean GetItemFromFront(Global_Handle(Mesh2d_Edge)& Edge);

			Standard_Boolean IsFrontEmpty() const;

			virtual Standard_Boolean IsCurrentLevelEmpty() const = 0;

			virtual Standard_Boolean IsNextLevelEmpty() const = 0;

			Standard_Boolean IsOnLevel(const Mesh2d_Edge& theEdge) const;

			// Throw an exception
			void InsertToFronts(const TColMesh2d_HAry1dOfEdge& Edges);

			// Throw an exception
			virtual void InsertToCurrentLevel(Global_Handle(Mesh2d_Edge) Edge) = 0;

			// Throw an exception
			virtual void InsertToNextLevel(Global_Handle(Mesh2d_Edge) Edge) = 0;

			virtual void ClearCurrentLevel() = 0;

			virtual void ClearNextLevel() = 0;

			void SetLevelNumber(const Standard_Integer Value);

			void SetLevelMaxIndex(const Standard_Integer Value);

			virtual void RetrieveCurrentLevelTo(TColMesh2d_HAry1dOfEdge& Edges) const = 0;

			virtual void RetrieveNextLevelTo(TColMesh2d_HAry1dOfEdge& Edges) const = 0;

		protected:

			Mesh2d_Front();
		};
	}
}

#include <Mesh2d_FrontI.hxx>

#endif // !_Mesh2d_Front_Header
