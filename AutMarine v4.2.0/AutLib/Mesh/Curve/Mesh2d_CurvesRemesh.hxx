#pragma once
#ifndef _Mesh2d_CurvesRemesh_Header
#define _Mesh2d_CurvesRemesh_Header

#include <Standard_Real.hxx>
#include <Mesh_VariationRateInfo.hxx>
#include <GeoMesh_BackGroundMesh2d.hxx>
#include <Entity_StaticChain2d.hxx>
#include <Entity_Box2d.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColCad2d_HAry1dOfCurveOnPlane.hxx>

class Geom2dLProp_CLProps2d;
class Geom2d_Curve;

namespace AutLib
{
	namespace MeshLib
	{
		
		class Mesh2d_SizeMap;

		struct DiscreteParameters;

		class Mesh2d_CurvesRemesh
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

			Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) theMesh_;
			M_GEO Entity_StaticChain2d theChain_;
			M_GEO Entity_Box2d theDomain_;

			TColCad2d_HAry1dOfCurveOnPlane theCurve_;

			Standard_Boolean IsDone_;
			Standard_Boolean IsConverged_;

		public:

			Mesh2d_CurvesRemesh(const M_CAD Cad2d_CurveOnPlane& theCurve);

			Mesh2d_CurvesRemesh(const M_CAD Cad2d_CurveOnPlane& theCurve, const M_GEO Entity_Box2d& Domain);

			Mesh2d_CurvesRemesh(const TColCad2d_HAry1dOfCurveOnPlane& Curves, const M_GEO Entity_Box2d& Domain);

			Mesh2d_CurvesRemesh(const TColCad2d_HAry1dOfCurveOnPlane& Curves, const M_GEO Entity_Box2d& Domain, const Standard_Real BaseSize, const Standard_Real MinSize, const Standard_Real SpanAngle);

			~Mesh2d_CurvesRemesh();

			const M_GEO Entity_StaticChain2d& Chain() const;

			const M_GEO GeoMesh_BackGroundMesh2d& BackGroundMesh() const;

			Standard_Boolean IsDone() const;

			void SetRelaxation(const Standard_Real Factor);

			void SetBaseSize(const Standard_Real BaseSize);

			void SetMinSize(const Standard_Real MinSize);

			void SetSpanAngle(const Standard_Real SpanAngle);

			void SetMaxNbIterations(const Standard_Integer NbIterations);

			void Perform();

			void ExportToPlt(fstream & File) const;

		private:

			Standard_Real Discrete(const Global_Handle(Mesh2d_SizeMap) Map);

			void UpdateGeoSize(const M_CAD Cad2d_CurveOnPlane& theCurve, const TColStd_Ary1dOfReal& Parameters, TColStd_Ary1dOfReal& H) const;

			void SetSourcesToMesh(const DiscreteParameters& DP);

			void MakeChain(const TColStd_Ary1dOfReal& Parameters);

			void ReleaseMemory();

		};
	}
}

#endif // !_Mesh2d_CurvesRemesh_Header
