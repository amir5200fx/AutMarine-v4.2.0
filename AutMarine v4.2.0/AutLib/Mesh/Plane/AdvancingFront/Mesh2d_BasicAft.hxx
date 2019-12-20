#pragma once
#ifndef _Mesh2d_BasicAft_Header
#define _Mesh2d_BasicAft_Header

#include <Geom_Search2d.hxx>
#include <Mesh2d_Plane.hxx>
#include <Mesh2d_Front.hxx>
#include <Mesh2d_Cavity.hxx>
#include <Mesh2d_CycleInfo.hxx>
#include <Mesh2d_SizeMap.hxx>
#include <Mesh2d_Plane.hxx>
#include <Mesh2d_AdvancingFrontConfig.hxx>
#include <TColMesh2d_GeomSearchOfNode.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColCad2d_HBasicQueueOfPlane.hxx>

namespace AutLib
{
	namespace CadLib
	{
		class Cad2d_Plane;
	}

	namespace GeoLib
	{
		class Entity_StaticChain2d;
	}

	namespace MeshLib
	{

		class Mesh2d_BasicAft : public Mesh2d_Plane
		{

		protected:

			TColMesh2d_HAry1dOfEdge theBoundary_;

			TColCad2d_HBasicQueueOfPlane theShapes_;

			TColMesh2d_GeomSearchOfNode& theSearch_;

			const Mesh2d_SizeMap& theMap_;
			const Mesh2d_SizeMap& theBoundaryMap_;

			Mesh2d_Front& theFront_;

			Mesh2d_Cavity theCavity_;

			Mesh2d_CycleInfo theInfo_;

			Standard_Integer theALLOWED_MAX_LEVEL_;

			Standard_Boolean IsDone_;

			Standard_Integer theVerbosity_;

			Standard_Real theDimension_;

			Standard_String theDomainName_;

			Mesh2d_AdvancingFrontConfig theConfig_;

		public:

			Mesh2d_BasicAft(const Mesh2d_SizeMap& theSizeMap, Global_Handle(TColMesh2d_GeomSearchOfNode) theSearchEngine);

			Mesh2d_BasicAft(const Mesh2d_SizeMap& theSizeMap, const Mesh2d_SizeMap& theBoundarySizeMap, Global_Handle(TColMesh2d_GeomSearchOfNode) SearchEngine);

			virtual ~Mesh2d_BasicAft();

			const TColMesh2d_HAry1dOfEdge& Boundary() const;

			TColMesh2d_HAry1dOfEdge& Boundary();

			Standard_Integer NbRegions() const;

			Standard_Boolean IsDone() const;

			Mesh2d_AdvancingFrontConfig& Config();

			void SetVerbosity(const Standard_Integer);

			void SetDomainName(const Standard_String theName);

			void Import(const M_CAD Cad2d_Plane& thePlane);

			void Perform();

			void Perform(const M_GEO Entity_StaticChain2d& Shape);

			void Perform(const TColMesh2d_HAry1dOfEdge& theEdges);

			void ExportQualityToPlt(fstream& File) const;

			void ReportQualityTo(Standard_OStream& Ostream) const;

		private:

			virtual Standard_Integer MeshGeneration();

			Standard_Boolean IsNewNode() const;

			Standard_Boolean GetFront();

			Standard_Boolean IsBelongToFront() const;

			Standard_Boolean IsValidNewPoint(const TColMesh2d_HAry1dOfEdge & theEffectives) const;

			Standard_Boolean IsSameLevelSupply();

			Standard_Boolean IsNextLevelSupply();

			Standard_Boolean IsCavityRemoverSupply();

			Standard_Boolean CheckSelfIntersection() const;

			Standard_Boolean CheckCcwOrder(const TColMesh2d_HAry1dOfNode& theNodes) const;

			const Mesh2d_Edge& CurrentEdge() const;

			const Mesh2d_Node& ValidNode() const;

			Mesh2d_Edge& CurrentEdge();

			void SetConfig();

			void Import(const M_GEO Entity_StaticChain2d & theFront);

			void Import(const TColMesh2d_HAry1dOfEdge& theFront);

			void CreateBoundary(const M_GEO Entity_StaticChain2d & theFront);

			void CreateBoundary(const TColMesh2d_HAry1dOfEdge& theFront);

			void RemoveDegeneracy(const Standard_Real LengthCriteria = 1.0E-4);

			void ActiveFront();

			void MeshingOneLevel();

			void RetrieveEarlyNodes(TColMesh2d_HAry1dOfNode& theNodes) const;

			void RetrieveLocalEdges(const TColMesh2d_HAry1dOfNode & theEarly, TColMesh2d_HAry1dOfEdge & theLocal) const;

			void RetrieveEffectiveFronts(const TColMesh2d_HAry1dOfNode & theNodesInRadius, const TColMesh2d_HAry1dOfEdge & theLocal, TColMesh2d_HAry1dOfEdge & theEffectives) const;

			void RetrieveNodesInRadius(const TColMesh2d_HAry1dOfNode& theNodes, TColMesh2d_HAry1dOfNode& theInners) const;

			void RetrieveNodesInRadius(const TColMesh2d_HAry1dOfNode& theNodes, TColMesh2d_HAry1dOfNode& theNodesLevel1, TColMesh2d_HAry1dOfNode& theNodesLevel2) const;

			void NodesInRadius(const Standard_Real theRadius, const Geom_Pnt2d & theCoord, const TColMesh2d_HAry1dOfNode & theNodes, TColMesh2d_HAry1dOfNode & theInnerNodes) const;

			void AppendOptimumPoint(TColMesh2d_HAry1dOfNode & theNodesInRadius);

			void CalcQuality(const TColMesh2d_HAry1dOfNode & theNodes, TColStd_Ary1dOfReal & theQuality) const;

			void SortNodes(TColMesh2d_HAry1dOfNode & NodesInRadius) const;

			void FindValidNode(const TColMesh2d_HAry1dOfNode & theNodesInRadius, const TColMesh2d_HAry1dOfEdge & theEffectiveEdges);

			void RemoveCurrentFromFront();

			void CalcElementSize();

			void CalcOptimumPoint();

			void CalcSearchRadius();

			void SetDepthSearching();

			void CreateElement();

			//! Throw an exception if the facet is a cavity face
			void Reject(Mesh2d_Edge & theEdge);

			//void CalcGeometryOf(Mesh2d_Edge & theEdge);

			void ModifyLocalFront(const Standard_Real Factor);

			void SetPairedEdges();

			void UpdateEdges();

			void UpdateElement();

			void UpdateFront();

			void Update();

			void InsertNewEdgesToLevels();

			void UpdateMaxLength(const Standard_Real theLength, Mesh2d_Edge & theEdge);

			static Standard_Real CalcUnitDistance(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Mesh2d_SizeMap& Map);
		};
	}
}

#include <Mesh2d_BasicAftI.hxx>

#endif // !_Mesh2d_BasicAft_Header
