#pragma once
#ifndef _Mesh2d_FastFront_Header
#define _Mesh2d_FastFront_Header

#include <Mesh2d_Front.hxx>
#include <TColMesh2d_HBasicQueueOfEdge.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_FastFront : public Mesh2d_Front
		{

		private:

			TColMesh2d_HBasicQueueOfEdge theNextLevels_;
			TColMesh2d_HBasicQueueOfEdge theCurrentLevels_;

		public:

			Mesh2d_FastFront();

			virtual Standard_Boolean IsCurrentLevelEmpty() const;

			virtual Standard_Boolean IsNextLevelEmpty() const;

			virtual void InsertToCurrentLevel(Global_Handle(Mesh2d_Edge) Edge);

			virtual void InsertToNextLevel(Global_Handle(Mesh2d_Edge) Edge);

			virtual void ClearCurrentLevel();

			virtual void ClearNextLevel();

			virtual void RetrieveCurrentLevelTo(TColMesh2d_HAry1dOfEdge& Edges) const;

			virtual void RetrieveNextLevelTo(TColMesh2d_HAry1dOfEdge& Edges) const;
		};
	}
}

#include <Mesh2d_FastFrontI.hxx>

#endif // !_Mesh2d_FastFront_Header
