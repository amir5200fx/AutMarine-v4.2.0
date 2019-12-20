#pragma once
#ifndef _Mesh3d_Front_Header
#define _Mesh3d_Front_Header

#include <Mesh3d_Facet.hxx>
#include <TColMesh3d_HeapOfFacet.hxx>
#include <TColMesh3d_HAvlTreeOfNode.hxx>
#include <TColMesh3d_HAvlTreeOfFacet.hxx>
#include <TColMesh3d_HAry1dOfFacet.hxx>
#include <TColMesh3d_HAry1dOfNode.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_Front
		{

		private:

			TColMesh3d_HeapOfFacet theSortedFacets_;
		
			TColMesh3d_HAvlTreeOfFacet theNextLevels_;
			TColMesh3d_HAvlTreeOfFacet theCurrentLevels_;

			Standard_Integer theLevelNb_;
			Standard_Integer theLevelMaxIndex_;

		public:

			Mesh3d_Front();

			Standard_Integer LevelNumber() const;

			Standard_Integer LevelMaxIndex() const;

			Standard_Boolean GetItemFromFront(Global_Handle(Mesh3d_Facet)& Facet);

			Standard_Boolean IsFrontEmpty() const;

			Standard_Boolean IsCurrentLevelEmpty() const;

			Standard_Boolean IsNextLevelEmpty() const;

			Standard_Boolean IsOnLevel(const Mesh3d_Facet& theFacet) const;

			// Throw an exception
			void InsertToFronts(const TColMesh3d_HAry1dOfFacet& Facets);

			// Throw an exception
			void InsertToCurrentLevel(Global_Handle(Mesh3d_Facet) Facet);

			// Throw an exception
			void InsertToNextLevel(Global_Handle(Mesh3d_Facet) Facet);

			void ClearCurrentLevel();

			void ClearNextLevel();

			void SetLevelNumber(const Standard_Integer Value);

			void SetLevelMaxIndex(const Standard_Integer Value);

			void RetrieveCurrentLevelTo(TColMesh3d_HAry1dOfFacet& Facets) const;

			void RetrieveNextLevelTo(TColMesh3d_HAry1dOfFacet& Facets) const;
		};
	}
}

#include <Mesh3d_FrontI.hxx>

#endif // !_Mesh3d_Front_Header
