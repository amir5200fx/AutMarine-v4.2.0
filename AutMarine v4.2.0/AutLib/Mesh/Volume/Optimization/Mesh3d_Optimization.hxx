#pragma once
#ifndef _Mesh3d_Optimization_Header
#define _Mesh3d_Optimization_Header

#include <Geom_Pnt3d.hxx>
#include <Mesh3d_Element.hxx>
#include <Mesh3d_QualityMap.hxx>
#include <Mesh3d_SmoothingConfig.hxx>
#include <TColMesh3d_HAry1dOfOptTetInfo.hxx>
#include <TColMesh3d_HAry1dOfNode.hxx>
#include <TColMesh3d_HAry1dOfFacet.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_QualityMap;
		class Mesh3d_Volume;
		class Mesh3d_TMesh;
		class Mesh3d_SizeMap;
		class Mesh3d_Node;
		class Mesh3d_Edge;
		class Mesh3d_Facet;
		class Mesh3d_EdgeRemovalEquatorialTriangles;

		class Mesh3d_Optimization
		{

		private:

			const Mesh3d_QualityMap& theQualityMap_;
			const Mesh3d_SizeMap& theSizeMap_;
			Mesh3d_Volume& theMesh_;

			Mesh3d_SmoothingConfig theSmoothingConfig_;

			Standard_Integer theVerbose_;

		public:

			Mesh3d_Optimization(const Mesh3d_QualityMap& theQualityMap, const Mesh3d_SizeMap& theSizeMap, Mesh3d_Volume& theMesh);

			void SetVerbosity(const Standard_Integer theVerbose);

			void Perform();

			void Perform(Mesh3d_TMesh& theMesh);

			void Report(Standard_OStream& Ostream) const;

			Standard_Real CalcQuality(const Mesh3d_Element& theElement) const;

			Standard_Real CalcWorstQuality(const Mesh3d_TMesh& theMesh) const;

		private:

			Standard_Boolean NonSmooth(Global_Handle(Mesh3d_Node) theNode, TColMesh3d_HAry1dOfOptTetInfo& theElements, Standard_Real& theWorst) const;

			Standard_Boolean SingleVertexSmoothing(Global_Handle(Mesh3d_Node) theNode, Standard_Real& theWorst, Standard_Integer& optattempts, Standard_Integer& optsuccesses) const;

			Standard_Real WorstQuality(Global_Handle(Mesh3d_Node) theNode) const;

			Standard_Real WorstQuality(Global_Handle(Mesh3d_Edge) theEdge) const;

			void NonSmoothLineSearch(Global_Handle(Mesh3d_Node) theNode, const TColMesh3d_HAry1dOfOptTetInfo& theElements, Geom_Pnt3d& d, const Standard_Real theWorst, const Standard_Real r, Standard_Real& alpha) const;

			void Topological(Mesh3d_TMesh& theMesh);

			void Smoothing(Mesh3d_TMesh& theMesh);

			void LaplacianSmoothing(TColMesh3d_HAry1dOfNode& theNodes, const Standard_Real theUnderRelaxation);

			void NonSmoothing(TColMesh3d_HAry1dOfNode& theNodes);

			void Sort(TColMesh3d_HAry1dOfNode& theNodes) const;

			void ImportFacetsToMesh(const Mesh3d_EdgeRemovalEquatorialTriangles & theEquatorialTriangles, TColMesh3d_HAry1dOfFacet & theFacets, Mesh3d_TMesh& theMesh);

			Standard_Boolean Flip(Global_Handle(Mesh3d_Edge) theEdge, Mesh3d_TMesh& theMesh);

			Standard_Boolean Flip(Global_Handle(Mesh3d_Facet) theFacet, Mesh3d_TMesh& theMesh);
		};
	}
}

#include <Mesh3d_OptimizationI.hxx>

#endif // !_Mesh3d_Optimization_Header
