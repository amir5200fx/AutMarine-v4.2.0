#pragma once
#ifndef _Cad3d_CurveOnSurface_Header
#define _Cad3d_CurveOnSurface_Header

#include <Standard_Handle.hxx>
#include <Global_Memory.hxx>
#include <Geom_Pnt3d.hxx>

class Geom_Curve;

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Box3d;
	}

	namespace CadLib
	{

		class Cad3d_CurveOnSurface
		{

		protected:

			Handle(Geom_Curve) theCurve_;

			Standard_Real theFirst_;
			Standard_Real theLast_;

		public:

			Cad3d_CurveOnSurface();

			Cad3d_CurveOnSurface(const Standard_Real First, const Standard_Real Last, const Handle(Geom_Curve)& Curve);

			virtual ~Cad3d_CurveOnSurface();

			void Init(const Standard_Real First, const Standard_Real Last, const Handle(Geom_Curve)& Curve);

			const Handle(Geom_Curve)& Curve() const;

			Standard_Real FirstParameter() const;

			Standard_Real LastParameter() const;

			Geom_Pnt3d StartCoord() const;

			Geom_Pnt3d LastCoord() const;

			Geom_Pnt3d MidCoord() const;

			Geom_Pnt3d Value(const Standard_Real Parameter) const;

			Standard_Boolean IsClosed(const Standard_Real Tolerance) const;

			Standard_Boolean Split(const Standard_Real theParameter, Global_Handle(Cad3d_CurveOnSurface) theLeft, Global_Handle(Cad3d_CurveOnSurface) theRight, const Standard_Real theTolerance) const;

			Standard_Boolean IsSameDirection(const Cad3d_CurveOnSurface& theOther) const;

			M_GEO Entity_Box3d BoundingBox(const Standard_Real Offset = 0) const;

			Global_Handle(Cad3d_CurveOnSurface) Copy() const;

			void SetFirst(const Standard_Real Value);

			void SetLast(const Standard_Real Value);

			void SetCurve(const Handle(Geom_Curve)& Curve);

			void Reverse();

			void ExportToPlt(fstream& File) const;

			void ExportTopologyToPlt(fstream& File) const;
		};
	}
}

#include <Cad3d_CurveOnSurfaceI.hxx>

#endif // !_Cad3d_EdgeOnSurface_Header
