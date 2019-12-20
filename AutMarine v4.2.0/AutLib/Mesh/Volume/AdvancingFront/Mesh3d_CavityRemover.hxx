#pragma once
#ifndef _Mesh3d_CavityRemover_Header
#define _Mesh3d_CavityRemover_Header

#include <Mesh3d_BasicAft.hxx>
#include <TColMesh3d_HAvlTreeOfCavityShell.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_CavityShellFourFacet;
		class Mesh3d_CavityShellSixFacet;
		class Mesh3d_CavityShellEightFacet;
		class Mesh3d_CavityShellTenFacet;
		class Mesh3d_CavityShellGeneral;
		class Mesh3d_EdgeRemovalEquatorialTriangles;

		class Mesh3d_CavityRemover : public Mesh3d_BasicAft
		{

		private:

			Standard_Real theNonConvexityAngle_;

			TColMesh3d_HAvlTreeOfCavityShell theShells_;

		public:

			Mesh3d_CavityRemover(const Mesh3d_SizeMap& theSizeMap, Global_Handle(TColMesh3d_GeomSearchOfNode) theSearchEngine);

			virtual ~Mesh3d_CavityRemover();

		private:

			virtual Standard_Integer MeshGeneration();

			Standard_Boolean MeshCavityShell(Global_Handle(Mesh3d_CavityShell) theShell);

			Standard_Boolean MeshCavityShell(Global_Handle(Mesh3d_CavityShellFourFacet) theShell);

			Standard_Boolean MeshCavityShell(Global_Handle(Mesh3d_CavityShellSixFacet) theShell);

			Standard_Boolean MeshCavityShell(Global_Handle(Mesh3d_CavityShellEightFacet) theShell);

			Standard_Boolean MeshCavityShell(Global_Handle(Mesh3d_CavityShellTenFacet) theShell);

			Standard_Boolean MeshCavityShell(Global_Handle(Mesh3d_CavityShellGeneral) theShell);

			Standard_Boolean MeshPick(Global_Handle(Mesh3d_Node) theNode, Global_Handle(Mesh3d_CavityShell) theShell);

			Standard_Boolean CheckFront(const TColMesh3d_HAry1dOfFacet & theFacet) const;

			Standard_Boolean CheckFront1(const TColMesh3d_HAry1dOfFacet & theFacet) const;

			Standard_Boolean CheckFront2(const TColMesh3d_HAry1dOfFacet & theFacet) const;

			Standard_Boolean CheckShell(const Mesh3d_CavityShell& theShell) const;

			Standard_Boolean IsValidNewFace(const Geom_Pnt3d& theP0, const Geom_Pnt3d& theP1, const Geom_Pnt3d& theP2, const TColMesh3d_HAry1dOfNode& theNodes, const TColMesh3d_HAry1dOfEdge& theEdges, const Standard_Real theDisCoeff) const;

			Standard_Boolean IsPickNode(const Global_Handle(Mesh3d_Node) theNode, const Global_Handle(Mesh3d_CavityShell) theShell) const;

			Standard_Integer OneLevelRemoveDefiniteElements(TColMesh3d_HAry1dOfFacet& theRetrieveFacets, TColMesh3d_HAry1dOfFacet& theRemoveFacets, const Standard_Boolean theThreeEntities = Standard_True, const Standard_Boolean theFourEntities = Standard_True);

			Global_Handle(Mesh3d_EdgeRemovalEquatorialTriangles) IsValidToSwap(const Global_Handle(Mesh3d_Edge) theEdge, const Global_Handle(Mesh3d_CavityShell) theShell) const;

			Global_Handle(Mesh3d_Facet) ImportFacetToMesh(Global_Handle(Mesh3d_Node) theNode0, Global_Handle(Mesh3d_Node) theNode1, Global_Handle(Mesh3d_Node) theNode2);

			Global_Handle(Mesh3d_Edge) FrontFlip(Global_Handle(Mesh3d_Edge) theEdge);

			void RemoveEdge(Global_Handle(Mesh3d_Edge) theEdge);

			void RemoveDefiniteElements(TColMesh3d_HAry1dOfFacet& theRetrieveFacets);

			void FormFront();

			void FormFront(const TColMesh3d_HAry1dOfFacet& theFacets);

			void MarkAsUnCavity(const TColMesh3d_HAry1dOfFacet& theFacets);

			void GenerateOneElement(Global_Handle(Mesh3d_Facet) theCurrent, Global_Handle(Mesh3d_Node) theNode, const Standard_Boolean CreationNode = Standard_False);

			void ImportFacetsToMesh(const Mesh3d_EdgeRemovalEquatorialTriangles& theEquatorialTriangles, TColMesh3d_HAry1dOfFacet& theFacets);

			void RepairLevel1();

			void RepairLevel2();

			void ClearShells();
		};
	}
}

#endif // !_Mesh3d_CavityRemover_Header
