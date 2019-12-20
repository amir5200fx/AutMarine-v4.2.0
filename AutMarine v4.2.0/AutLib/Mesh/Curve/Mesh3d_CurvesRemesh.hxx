#pragma once
#ifndef _Mesh3d_CurvesRemesh_Header
#define _Mesh3d_CurvesRemesh_Header

#include <Standard_Real.hxx>
#include <Entity_Box3d.hxx>
#include <Entity_StaticChain3d.hxx>
#include <Mesh_VariationRateInfo.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColCad3d_HAry1dOfEdgeOnSurface.hxx>

class Geom_Curve;

namespace AutLib
{
	namespace GeoLib
	{
		class GeoMesh_BackGroundMesh3d;
	}

	namespace MeshLib
	{

		class Mesh3d_SizeMap;
		struct DiscreteParameters;

		class Mesh3d_CurvesRemesh
		{

		private:

			Standard_Real theBaseSize_;
			Standard_Real theMinSize_;

			Standard_Real theUnderRelaxation_;

			Standard_Real theSpanAngle_;

			Standard_Integer theMaxNbIterations_;
			Standard_Integer theMaxNbSmoothing_;

			Standard_Real theIterTolerance_;
			Standard_Real theSmoothingFactor_;

			Mesh_VariationRateInfo theVariationRateInfo_;

			Global_Handle(M_GEO GeoMesh_BackGroundMesh3d) theMesh_;
			M_GEO Entity_StaticChain3d theChain_;
			M_GEO Entity_Box3d theDomain_;

			TColCad3d_HAry1dOfEdgeOnSurface theCurve_;

			Standard_Boolean IsDone_;
			Standard_Boolean IsConverged_;

		public:

			Mesh3d_CurvesRemesh(const TColCad3d_HAry1dOfEdgeOnSurface& Curves, const M_GEO Entity_Box3d& Domain);

			Mesh3d_CurvesRemesh(const TColCad3d_HAry1dOfEdgeOnSurface& Curves, const M_GEO Entity_Box3d& Domain, const Standard_Real BaseSize, const Standard_Real MinSize, const Standard_Real SpanAngle);

			~Mesh3d_CurvesRemesh();

			const M_GEO Entity_StaticChain3d& Chain() const;

			const M_GEO GeoMesh_BackGroundMesh3d& BackGroundMesh() const;

			Standard_Boolean IsDone() const;

			void SetRelaxation(const Standard_Real Factor);

			void SetBaseSize(const Standard_Real BaseSize);

			void SetMinSize(const Standard_Real MinSize);

			void SetSpanAngle(const Standard_Real SpanAngle);

			void SetMaxNbIterations(const Standard_Integer NbIterations);

			void Perform();

			void ExportToPlt(fstream & File) const;

		private:

			Standard_Real Discrete(const Global_Handle(Mesh3d_SizeMap) Map);

			void UpdateGeoSize(const Geom_Curve& Curve, const TColStd_Ary1dOfReal& Parameters, TColStd_Ary1dOfReal& H) const;

			void SetSourcesToMesh(const DiscreteParameters& DP);

			void MakeChain(const TColStd_Ary1dOfReal& Parameters);

			void ReleaseMemory();
		};
	}
}

#endif // !_Mesh3d_CurvesRemesh_Header
