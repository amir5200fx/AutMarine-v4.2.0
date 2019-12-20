#pragma once
#ifndef _Mesh3d_CavityShell_Header
#define _Mesh3d_CavityShell_Header

#include <Geom_Pnt3d.hxx>
#include <TColMesh3d_HAry1dOfCavityEntity.hxx>
#include <TColMesh3d_HAry1dOfNode.hxx>
#include <TColMesh3d_HAry1dOfEdge.hxx>
#include <TColMesh3d_HAry1dOfFacet.hxx>
#include <TColMesh3d_HAvlTreeOfCavityEntity.hxx>
#include <TColMesh3d_HAvlTreeOfFacet.hxx>
#include <TColMesh3d_HAry1dOfCavityEntityNonConvexity.hxx>
#include <TColMesh3d_HAry1dOfCavityEntitySwapEdge.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityShell
		{

		private:

			TColMesh3d_HAvlTreeOfFacet theFacets_;

			TColMesh3d_HAvlTreeOfCavityEntity theEntities_;

			Standard_Integer theIndex_;

		public:

			virtual ~Mesh3d_CavityShell();

			Standard_Integer NbFacets() const;

			Standard_Integer NbEntities() const;

			Standard_Integer Index() const;

			Standard_Boolean IsEmpty() const;

			Standard_Boolean IsConvex() const;

			Standard_Boolean IsOnShell(const Global_Handle(Mesh3d_Facet) theFacet) const;

			Standard_Boolean IsOnShell(const Global_Handle(Mesh3d_Node) theNode) const;

			Geom_Pnt3d Centre() const;

			TColMesh3d_HAry1dOfFacet RetrieveFacetsOnShell(const TColMesh3d_HAry1dOfFacet& theFacets) const;

			Global_Handle(Mesh3d_Node) HasPick() const;

			void SetIndex(const Standard_Integer theIndex);

			void ImportToFacets(Global_Handle(Mesh3d_Facet) theFacet);

			void ImportToEntities(Global_Handle(Mesh3d_CavityEntity) theEntity);

			void RemoveFromFacets(Global_Handle(Mesh3d_Facet) theFacet);

			void RemoveFromEntities(Global_Handle(Mesh3d_CavityEntity) theEntity);

			void RetrieveNodesTo(TColMesh3d_HAry1dOfNode& theNodes) const;

			void RetrieveEdgesTo(TColMesh3d_HAry1dOfEdge& theEdges) const;

			void RetrieveFacetsTo(TColMesh3d_HAry1dOfFacet& theFacets) const;

			void RetrieveEntitiesTo(TColMesh3d_HAry1dOfCavityEntity& theEntities) const;

			void RetrieveNonConvexitiesTo(TColMesh3d_HAry1dOfCavityEntityNonConvexity& theNonConvexities) const;

			void RetrieveSwapEdgesTo(TColMesh3d_HAry1dOfCavityEntitySwapEdge& theSwapEdges) const;

			void Clear();

			void ClearEntities();

			void Update();

		protected:

			Mesh3d_CavityShell();
		};
	}
}

#include <Mesh3d_CavityShellI.hxx>

#endif // !_Mesh3d_CavityShell_Header
