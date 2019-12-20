#pragma once
#ifndef _Mesh2d_SafeFront_Header
#define _Mesh2d_SafeFront_Header

#include <Mesh2d_Front.hxx>
#include <TColMesh2d_HAvlTreeOfEdge.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_SafeFront : public Mesh2d_Front
		{

		private:

			TColMesh2d_HAvlTreeOfEdge theNextLevels_;
			TColMesh2d_HAvlTreeOfEdge theCurrentLevels_;

		public:

			Mesh2d_SafeFront();

			virtual Standard_Boolean IsCurrentLevelEmpty() const;

			virtual Standard_Boolean IsNextLevelEmpty() const;

			// Throw an exception
			virtual void InsertToCurrentLevel(Global_Handle(Mesh2d_Edge) Edge);

			// Throw an exception
			virtual void InsertToNextLevel(Global_Handle(Mesh2d_Edge) Edge);

			virtual void ClearCurrentLevel();

			virtual void ClearNextLevel();

			virtual void RetrieveCurrentLevelTo(TColMesh2d_HAry1dOfEdge& Edges) const;

			virtual void RetrieveNextLevelTo(TColMesh2d_HAry1dOfEdge& Edges) const;
		};
	}
}

#include <Mesh2d_SafeFrontI.hxx>

#endif // !_Mesh2d_SafeFront_Header
