#pragma once
#ifndef _Nurbs_Curve2d_Header
#define _Nurbs_Curve2d_Header

#include <TColStd_Ary1dOfReal.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Box2d;
	}

	namespace CadLib
	{

		class Nurbs_Curve2d
		{

		private:

			Standard_Integer theMaxIndex_;
			Standard_Integer theDeg_;

			TColGeom_Ary1dOfPnt2d thePoles_;

			TColStd_Ary1dOfReal theWeights_;
			TColStd_Ary1dOfReal theKnots_;

		public:

			Nurbs_Curve2d();

			Nurbs_Curve2d(const Standard_Integer Degree, const Standard_Integer MaxIndex, const TColStd_Ary1dOfReal& Knots, const TColStd_Ary1dOfReal& Weights, const TColGeom_Ary1dOfPnt2d& Poles);

			Geom_Pnt2d PointAt(const Standard_Real theParameter) const;

			Standard_Integer MaxIndex() const;

			Standard_Integer Degree() const;

			Standard_Integer NbPoles() const;

			Standard_Integer NbKnots() const;

			Standard_Real Weight(const Standard_Integer Index) const;

			Standard_Real Knot(const Standard_Integer Index) const;

			Standard_Real FirstParameter() const;

			Standard_Real LastParameter() const;

			Geom_Pnt2d StartPoint() const;

			Geom_Pnt2d EndPoint() const;

			M_GEO Entity_Box2d BoundingBox() const;

			TColGeom_Ary1dOfPnt2d DeriveAt(const Standard_Real Parameter, const Standard_Integer Nth) const;

			const Geom_Pnt2d& Pole(const Standard_Integer Index) const;

			const TColStd_Ary1dOfReal& Weights() const;

			const TColStd_Ary1dOfReal& Knots() const;

			const TColGeom_Ary1dOfPnt2d& Poles() const;

			void SetPole(const Standard_Integer Index, const Geom_Pnt2d& Pole);

			void SetWeight(const Standard_Integer Index, const Standard_Real Value);

			void SetKnot(const Standard_Integer Index, const Standard_Real Value);

			void IncreaseDegree(const Standard_Integer Degree);

			void D0(const Standard_Real Parameter, M_GEO Geom_Pnt2d& Point) const;

			void D1(const Standard_Real U, M_GEO Geom_Pnt2d& P, M_GEO Geom_Pnt2d& V1) const;

			void D2(const Standard_Real U, M_GEO Geom_Pnt2d& P, M_GEO Geom_Pnt2d& V1, M_GEO Geom_Pnt2d& V2) const;

			void D3(const Standard_Real U, M_GEO Geom_Pnt2d& P, M_GEO Geom_Pnt2d& V1, M_GEO Geom_Pnt2d& V2, M_GEO Geom_Pnt2d& V3) const;

			/*
			brief It inserts a knot a number of times

			It inserts the knot u, r times and generates the curve nc.
			For more information, see A5.1 on page 151 of the NURBS book
			*/
			// param u  the knot to insert
			// param r  the number of times to insert \a u.
			void InsertKnot(const Standard_Real Parameter, const Standard_Integer r, const Standard_Real ParametricTolerance = 0.0);

			/*
			brief Removes an internal knot from a curve.
			This is A5.8 on p185 from the NURB book modified to not check for
			tolerance before removing the knot.
			*/
			// param r  the knot to remove
			// param s  the multiplicity of the knot
			// param num  the number of times to try to remove the knot
			void RemoveKnot(const Standard_Integer r, const Standard_Integer s, const Standard_Integer num);

			// Reverses the orientation of this BSpline curve. As a result
			// - the knots and poles tables are modified;
			// - the start point of the initial curve becomes the end
			// point of the reversed curve;
			// - the end point of the initial curve becomes the start
			// point of the reversed curve.
			void Reverse();

			//! Throw an exception
			//void Split(const Standard_Real Parameter, Cad2d_BSplineCurve& Left, Cad2d_BSplineCurve& Right) const;

			//void Split(const TColStd_Array1OfReal& Parameters, TColCad2d_HArray1OfBSplineCurve& Curves) const;

			void NormalizeKnots();

			void MakeLine(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2);

			void MakeArc(const Geom_Pnt2d& P0, const Geom_Pnt2d& Tan0, const Geom_Pnt2d& P2, const Geom_Pnt2d& Tan2, const Geom_Pnt2d& ArbtPoint);

			void MakeCircle(const Standard_Real Radius, const Geom_Pnt2d& Centre, Standard_Real Start_Degree, Standard_Real End_Degree);

			void Transform(const gp_Trsf2d& T);

			void ExportToPlt(fstream& File) const;

			void ExportPolesToPlt(fstream& File) const;

			void Print(Standard_OStream& Ostream = cout) const;

		private:

			void Allocate(const Standard_Integer Degree, const Standard_Integer MaxIndex);
		};
	}
}

#include <Nurbs_Curve2dI.hxx>

#endif // !_Nurbs_Curve2d_Header
