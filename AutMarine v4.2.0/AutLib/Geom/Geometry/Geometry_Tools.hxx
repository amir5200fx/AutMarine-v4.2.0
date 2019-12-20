#pragma once
#ifndef _Geometry_Tools_Header
#define _Geometry_Tools_Header

#include <Standard_Real.hxx>
#include <Standard_Integer.hxx>
#include <Geom_Pnt2d.hxx>
#include <Geom_Pnt3d.hxx>
#include <Entity_Metric1.hxx>
#include <ADT_AvlTree.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <Armadillo.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Geometry_Tools
		{

		public:

			static Standard_Integer Round(const Standard_Real X);

			static Standard_Real DegToRadian(const Standard_Real Degree);

			static Standard_Real RadianToDegree(const Standard_Real Radian);

			static Standard_Real MachineEpsilon();

			static void InitExact(Standard_Real& theEpsilon);

			static void CalcMinMax(const TColGeom_Ary1dOfPnt2d& Points, Standard_Real & Xmin, Standard_Real & Xmax, Standard_Real& Ymin, Standard_Real & Ymax);

			static void CalcMinMax(const TColGeom_Ary1dOfPnt3d& Points, Standard_Real & Xmin, Standard_Real & Xmax, Standard_Real& Ymin, Standard_Real & Ymax, Standard_Real& Zmin, Standard_Real & Zmax);

			static void slowerCalcMinMax(const TColGeom_Ary1dOfPnt2d& Points, Standard_Real & Xmin, Standard_Real & Xmax, Standard_Real& Ymin, Standard_Real & Ymax);

			static void TriangleInterpolate(const Geom_Pnt2d& thePoint, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Geom_Pnt2d& P3, Standard_Real& c1, Standard_Real& c2, Standard_Real& c3);

			static Geom_Pnt2d Mul(const Geom_Pnt2d& Vec, const Entity_Metric1& M);

			static Geom_Pnt2d Mul(const Entity_Metric1& M, const Geom_Pnt2d& Vec);

			static Geom_Pnt3d ProjectPointonEdge(const Geom_Pnt3d& thePoint, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, Standard_Real& t);

			static Geom_Pnt3d NormalOfTriangle(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3);

			static Geom_Pnt3d CentreOfTetrahedron(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3, const Geom_Pnt3d& P4);

			static Standard_Real AreaOfTriangle(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Geom_Pnt2d& P3);

			static Standard_Real AreaOfTriangleAdapt(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Geom_Pnt2d& P3);

			static Standard_Real AreaOfTriangle(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3);

			static Standard_Real VolumeOfTetrahedron(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3, const Geom_Pnt3d& P4);

			static Standard_Real MinimumSineOfTetrahedron(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3, const Geom_Pnt3d& P4);

			static Standard_Real SignedAreaOfTriangle(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Geom_Pnt2d& P3);

			static Standard_Real Oriented(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Geom_Pnt2d& P3);

			static Standard_Real FastOriented(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Geom_Pnt2d& P3);

			static Standard_Real Oriented(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3, const Geom_Pnt3d& P4);

			static Standard_Real FastOriented(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3, const Geom_Pnt3d& P4);

			static Standard_Boolean IsCcwOrder(const TColGeom_Ary1dOfPnt2d& Points);

			static Standard_Boolean IsPointRightEdge(const Geom_Pnt2d& Point, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2);

			static Standard_Boolean IsPointRightEdgeAdapt(const Geom_Pnt2d& Point, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2);

			static Standard_Boolean IsPointRightOnEdge(const Geom_Pnt2d& Point, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2);

			static Standard_Boolean IsPointRightOnEdgeAdapt(const Geom_Pnt2d& Point, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Standard_Real theEpsilon);

			static Standard_Boolean IsPointLeftOnEdgeAdapt(const Geom_Pnt2d& Point, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2);

			static Standard_Boolean IsPointLeftEdge(const Geom_Pnt2d& Point, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2);

			static Standard_Boolean IsPointLeftEdgeAdapt(const Geom_Pnt2d& Point, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2);

			static Standard_Boolean IsPointLeftOnEdge(const Geom_Pnt2d& Point, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2);

			static Standard_Boolean IsPointRightTriangle(const Geom_Pnt3d& Point, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3);

			static Standard_Boolean IsPointRightTriangle_1(const Geom_Pnt3d& Point, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3, const Standard_Real Tolerance, Standard_Boolean& Undefiend);

			static Standard_Boolean IsPointRightOnTriangle(const Geom_Pnt3d& Point, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3);

			static Standard_Boolean IsPointLeftTriangle(const Geom_Pnt3d& Point, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3);

			static Standard_Boolean IsPointLeftOnTriangle(const Geom_Pnt3d& Point, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3);

			static Standard_Boolean IsPointInsideOnTriangle(const Geom_Pnt2d& Point, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Geom_Pnt2d& P3);

			static Standard_Boolean IsPointInsideOnTriangleAdapt(const Geom_Pnt2d& Point, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Geom_Pnt2d& P3, const Standard_Real theEpsilon);

			static Standard_Boolean IsPointInsideOnTriangleCW(const Geom_Pnt2d& Point, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Geom_Pnt2d& P3);

			static Standard_Boolean IsPointInsideOnTriangleCWAdapt(const Geom_Pnt2d& Point, const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Geom_Pnt2d& P3);

			static Standard_Boolean IsPointInsideOnTetrahedron(const Geom_Pnt3d& Point, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3, const Geom_Pnt3d& P4);

			static Standard_Boolean IsPointInsideOnInterval(const Standard_Real Point, const Standard_Real x0, const Standard_Real x1);

			static Standard_Boolean IsPointInsideOnBox(const Geom_Pnt2d& Point, const Standard_Real x0, const Standard_Real x1, const Standard_Real y0, const Standard_Real y1);

			static Standard_Boolean IsPointInsideOnBox(const Geom_Pnt3d& Point, const Standard_Real x0, const Standard_Real x1, const Standard_Real y0, const Standard_Real y1, const Standard_Real z0, const Standard_Real z1);

			static Standard_Boolean IsPointOnTriangle(const Geom_Pnt3d& thePoint, const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3, const Standard_Real Tolerance);

			static Standard_Boolean IsOneCommonPointTwoLineSegment(const Standard_Integer v1, const Standard_Integer v2, const Standard_Integer q1, const Standard_Integer q2);

			static Standard_Boolean IsPairedTwoLineSegment(const Standard_Integer v1, const Standard_Integer v2, const Standard_Integer q1, const Standard_Integer q2);

			static Standard_Boolean IsOneCommonPointLineSegmentTriangle(const Standard_Integer v1, const Standard_Integer v2, const Standard_Integer q1, const Standard_Integer q2, const Standard_Integer q3);

			static Standard_Boolean IsOneCommonTwoTriangle(const Standard_Integer v1, const Standard_Integer v2, const Standard_Integer v3, const Standard_Integer q1, const Standard_Integer q2, const Standard_Integer q3);

			static Standard_Boolean IsThreeCommonTwoTriangle(const Standard_Integer v1, const Standard_Integer v2, const Standard_Integer v3, const Standard_Integer q1, const Standard_Integer q2, const Standard_Integer q3);

			static Standard_Boolean IsPairedTwoTriangle(const Standard_Integer v1, const Standard_Integer v2, const Standard_Integer v3, const Standard_Integer q1, const Standard_Integer q2, const Standard_Integer q3);

			static mat33 CalcRotationMatrix(const Geom_Pnt3d& Vec1, const Geom_Pnt3d& Vec2);

			static TColGeom_Ary1dOfPnt3d FacetNormalOfTetrahedron(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Geom_Pnt3d& P3, const Geom_Pnt3d& P4);

			template<typename T>
			static ADT_Ary1d<T> RemoveMults(const ADT_Ary1d<T>& Objects);

			static void ConvertTriangleTo2D(const Geom_Pnt3d& theQ1, const Geom_Pnt3d& theQ2, const Geom_Pnt3d& theQ3, Geom_Pnt2d& theP2, Geom_Pnt2d& theP3);
		};
	}
}

#include <Geometry_ToolsI.hxx>

#endif // !_Geometry_Tools_Header
