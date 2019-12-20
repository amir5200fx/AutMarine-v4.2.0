#pragma once
#ifndef _Mesh2d_Optimization_Header
#define _Mesh2d_Optimization_Header

#include <Geom_Pnt2d.hxx>
#include <Mesh2d_Element.hxx>
#include <TColMesh2d_HAry1dOfNode.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_QualityMap;
		class Mesh2d_Plane;
		class Mesh2d_TMesh;
		class Mesh2d_SizeMap;
		class Mesh2d_MetricMap;
		class Mesh2d_Node;
		class Mesh2d_Edge;

		class Mesh2d_Optimization
		{

		private:

			const Mesh2d_QualityMap& theQualityMap_;
			const Mesh2d_SizeMap& theSizeMap_;
			Mesh2d_Plane& theMesh_;

			const Global_Handle(Mesh2d_MetricMap) theMetricMap_;

			Standard_Integer theVerbose_;

			Global_Handle(Mesh2d_SizeMap) UnionSizeMap_;

		public:

			Mesh2d_Optimization(const Mesh2d_QualityMap& theQualityMap, const Mesh2d_SizeMap& theSizeMap, const Global_Handle(Mesh2d_MetricMap) MetricMap, Mesh2d_Plane& theMesh);

			~Mesh2d_Optimization();

			void SetVerbosity(const Standard_Integer theVerbose);

			void Perform();

			void Perform(Mesh2d_TMesh& theMesh);

			void Report(Standard_OStream& Ostream) const;

			Standard_Real CalcQuality(const Mesh2d_Element& theElement) const;

			Standard_Real CalcWorstQuality(const Mesh2d_TMesh& theMesh) const;

		private:

			Standard_Real WorstQuality(const Mesh2d_Edge& theEdge) const;

			void Topological(Mesh2d_TMesh& theMesh);

			void Smoothing(Mesh2d_TMesh& theMesh);

			void LaplacianSmoothing(Mesh2d_TMesh & theMesh, const Standard_Real theUnderRelaxation);

			Global_Handle(Mesh2d_Edge) ImportEdgeToMesh(Global_Handle(Mesh2d_Node) theNode0, Global_Handle(Mesh2d_Node) theNode1, Mesh2d_TMesh& theMesh);

			Standard_Boolean Flip(Global_Handle(Mesh2d_Edge) theEdge, Mesh2d_TMesh& theMesh);

			Standard_Boolean CheckFlip(const Global_Handle(Mesh2d_Edge) theEdge, Global_Handle(Mesh2d_Node)& theVertex0, Global_Handle(Mesh2d_Node)& theVertex1) const;

			static Standard_Real CalcUnitDistance(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Mesh2d_SizeMap& Map);
		};
	}
}

#endif // !_Mesh2d_Optimization_Header
