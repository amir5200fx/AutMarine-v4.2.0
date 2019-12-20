#pragma once
#ifndef _Cad3d_CurveOnPlane_Header
#define _Cad3d_CurveOnPlane_Header

#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>
#include <Geom_Pnt2d.hxx>
#include <Global_Memory.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColCad3d_HAry1dOfCurveOnPlane.hxx>

class Geom2d_Curve;

class gp_Pnt2d;
class gp_Vec2d;
class gp_Ax22d;
class gp_Ax2d;
class gp_Trsf2d;

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Box2d;
		class Entity_Polygon2d;
	}

	namespace CadLib
	{

		class Cad3d_CurveOnPlane
		{

		protected:

			Handle(Geom2d_Curve) theCurve_;

			Standard_Real theFirst_;
			Standard_Real theLast_;

			Standard_Boolean IsReversed_;

		public:

			Cad3d_CurveOnPlane();

			Cad3d_CurveOnPlane(const Standard_Real theFirstParameter, const Standard_Real theLastParameter, const Handle(Geom2d_Curve)& theCurve);

			virtual ~Cad3d_CurveOnPlane() { ReleaseMemory(); }

			virtual void Init(const Standard_Real theFirstParameter, const Standard_Real theLastParameter, const Handle(Geom2d_Curve)& theCurve);

			const Handle(Geom2d_Curve)& Curve() const;

			Standard_Boolean IsClosed(const Standard_Real theTolerance) const;

			Standard_Boolean IsReversed() const;

			Standard_Real FirstParameter() const;

			Standard_Real LastParameter() const;

			Standard_Real CalcLength(const Standard_Real theTolerance = 1.0E-2) const;

			Geom_Pnt2d FirstCoord() const;

			Geom_Pnt2d LastCoord() const;

			Geom_Pnt2d MidCoord() const;

			Geom_Pnt2d Value(const Standard_Real theParameter) const;

			Geom_Pnt2d NormalizedParameterValue(const Standard_Real theParameter) const;

			GeoLib::Entity_Box2d BoundingBox(const Standard_Real theTolerance = 0.0) const;

			GeoLib::Entity_Polygon2d UniformParametricDiscretize(const Standard_Integer NbSegments) const;

			void Split(const Standard_Real theParameter, Global_Handle(Cad3d_CurveOnPlane) theCurve1, Global_Handle(Cad3d_CurveOnPlane) theCurve2) const;

			void Split(const Standard_Real theParameter, Geom_Pnt2d& theCoord, Global_Handle(Cad3d_CurveOnPlane) theCurve1, Global_Handle(Cad3d_CurveOnPlane) theCurve2) const;

			void Split(const TColStd_Ary1dOfReal& theParameters, TColGeom_Ary1dOfPnt2d& theCoords, TColCad3d_HAry1dOfCurveOnPlane& theCurves, const Standard_Real theTolerance = 1.0E-7) const;

			void SetFirst(const Standard_Real theValue);

			void SetLast(const Standard_Real theValue);

			void SetCurve(const Handle(Geom2d_Curve)& theCurve);

			void SetReverse(const Standard_Boolean Reversed);

			void Reverse();

			void ReleaseMemory();

			void Mirror(const gp_Pnt2d& P);

			void Mirror(const gp_Ax2d& A);

			void Rotate(const gp_Pnt2d& P, const Standard_Real Ang);

			void Scale(const gp_Pnt2d& P, const Standard_Real S);

			void Translate(const gp_Vec2d& V);

			void Translate(const gp_Pnt2d& P1, const gp_Pnt2d& P2);

			void Transform(const gp_Trsf2d& T);

			void ExportToPlt(fstream& File) const;

			virtual Global_Handle(Cad3d_CurveOnPlane) Copy() const;
		};
	}
}

#include <Cad3d_CurveOnPlaneI.hxx>

#endif // !_Cad3d_CurveOnPlane_Header
