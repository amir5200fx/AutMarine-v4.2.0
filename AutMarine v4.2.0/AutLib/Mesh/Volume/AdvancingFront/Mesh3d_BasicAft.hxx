#pragma once
#ifndef _Mesh3d_BasicAft_Header
#define _Mesh3d_BasicAft_Header

#include <Mesh3d_Volume.hxx>
#include <Mesh3d_SizeMap.hxx>
#include <Mesh3d_Front.hxx>
#include <Mesh3d_Cavity.hxx>
#include <Mesh3d_CycleInfo.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColMesh3d_GeomSearchOfNode.hxx>
#include <TColMesh3d_HAry1dOfFacet.hxx>
#include <TColCad3d_HBasicQueueOfSolid.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Triangulation3d;
		class GeoMesh_StaticTriangleMesh3d;
	}

	namespace MeshLib
	{

		class Mesh3d_BasicAft : public Mesh3d_Volume
		{

		protected:

			TColMesh3d_HAry1dOfFacet theBoundary_;

			TColCad3d_HBasicQueueOfSolid theShapes_;

			TColMesh3d_GeomSearchOfNode& theSearch_;

			const Mesh3d_SizeMap& theMap_;

			Mesh3d_Front theFront_;

			Mesh3d_Cavity theCavity_;

			Mesh3d_CycleInfo theInfo_;

			Standard_Integer theALLOWED_MAX_LEVEL_;

			Standard_Boolean IsDone_;
			Standard_Boolean UseExactMetric_;
			Standard_Boolean SurfaceMeshOnly_;

			Standard_Integer theVerbosity_;

			Standard_Real theDimension_;
			Standard_Real theMaxGradation_;

			Standard_String theDomainName_;

		public:

			Mesh3d_BasicAft(const Mesh3d_SizeMap& theSizeMap, Global_Handle(TColMesh3d_GeomSearchOfNode) theSearchEngine);

			virtual ~Mesh3d_BasicAft();

			Standard_Integer NbRegions() const;

			Standard_Boolean IsDone() const;

			void SetToUseExactMetricForSurfaceMesh();

			void SetVerbosity(const Standard_Integer);

			void SetDomainName(const Standard_String theName);

			void SetToSurfaceMeshOnly();

			void Import(const M_CAD Cad3d_Solid& theSolid);

			void Perform();

			void Perform(const M_GEO Entity_Triangulation3d& theTriangulation);

		protected:

			virtual Standard_Integer MeshGeneration();

			Standard_Boolean IsNewNode() const;

			Standard_Boolean GetFront();

			Standard_Boolean IsBelongToFront() const;

			Standard_Boolean IsValidNewPoint(const TColMesh3d_HAry1dOfFacet & theEffectives) const;

			Standard_Boolean IsValidNewEdge(const Geom_Pnt3d& theP0, const Geom_Pnt3d& theP1, const TColMesh3d_HAry1dOfEdge & theEffectives) const;

			Standard_Boolean IsSameLevelSupply();

			Standard_Boolean IsNextLevelSupply();

			Standard_Boolean IsCavityRemoverSupply();

			Standard_Boolean CheckSelfIntersection() const;

			const Mesh3d_Facet& CurrentFacet() const;

			const Mesh3d_Node& ValidNode() const;

			Mesh3d_Facet& CurrentFacet();

			void Import(const M_GEO Entity_Triangulation3d & theFront);

			void CreateBoundary(const M_GEO GeoMesh_StaticTriangleMesh3d & theFront);

			void ActiveFront();

			void MeshingOneLevel();

			void RetrieveEarlyNodes(TColMesh3d_HAry1dOfNode& theNodes) const;

			void RetrieveLocalFacets(const TColMesh3d_HAry1dOfNode & theEarly, TColMesh3d_HAry1dOfFacet & theLocal) const;

			void RetrieveEffectiveFronts(const TColMesh3d_HAry1dOfNode & theNodesInRadius, const TColMesh3d_HAry1dOfFacet & theLocal, TColMesh3d_HAry1dOfFacet & theEffectives) const;

			void RetrieveNodesInRadius(const TColMesh3d_HAry1dOfNode& theNodes, TColMesh3d_HAry1dOfNode& theInnerNodes) const;

			void RetrieveNodesInRadius(const TColMesh3d_HAry1dOfNode& theNodes, TColMesh3d_HAry1dOfNode& theNodesLevel1, TColMesh3d_HAry1dOfNode& theNodesLevel2) const;

			void NodesInRadius(const Standard_Real theRadius, const Geom_Pnt3d & theCoord, const TColMesh3d_HAry1dOfNode & theNodes, TColMesh3d_HAry1dOfNode & theInnerNodes) const;

			void AppendOptimumPoint(TColMesh3d_HAry1dOfNode & theNodesInRadius);

			void CalcQuality(const TColMesh3d_HAry1dOfNode & theNodes, TColStd_Ary1dOfReal & theQuality) const;

			void SortNodes(TColMesh3d_HAry1dOfNode & NodesInRadius) const;

			void FindValidNode(const TColMesh3d_HAry1dOfNode & theNodesInRadius, const TColMesh3d_HAry1dOfNode & theEarly, const TColMesh3d_HAry1dOfEdge & theEffectiveEdges, const TColMesh3d_HAry1dOfFacet & theEffectiveFacet);

			void RemoveCurrentFromFront();

			void CalcElementSize();

			void CalcOptimumPoint();

			void CalcSearchRadius();

			void SetDepthSearching();

			void CreateElement();

			//! Throw an exception if the facet is a cavity face
			void Reject(Mesh3d_Facet & theFacet);

			void CalcGeometryOf(Mesh3d_Facet & theFacet);

			void ModifyLocalFront(const Standard_Real Factor);

			void SetPairedFacets();

			void SetPairedEdges();

			void UpdateEdges();

			void UpdateFacets();

			void UpdateElement();

			void UpdateFront();

			void Update();

			void InsertNewFacetsToLevels();

			void UpdateMaxLength(const Standard_Real theLength, Mesh3d_Edge & theEdge);
		};
	}
}

#include <Mesh3d_BasicAftI.hxx>

#endif // !_Mesh3d_BasicAft_Header
