#pragma once
#ifndef _Cad3d_EdgeOnPlane_Header
#define _Cad3d_EdgeOnPlane_Header

#include <Standard_Handle.hxx>
#include <Global_Memory.hxx>
#include <Geom_Pnt2d.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColCad3d_HAry1dOfPointOnPlane.hxx>
#include <TColCad3d_HAry1dOfEdgeOnPlane.hxx>

class Geom2d_Curve;

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Box2d;
		class Geom_Pnt2d;
	}

	namespace CadLib
	{

		class Cad3d_PointOnPlane;
		class Cad3d_CurveOnPlane;
		class Cad3d_WireOnPlane;

		class Cad3d_EdgeOnPlane
		{

		protected:

			const Global_Handle(Cad3d_PointOnPlane) theFirstPoint_;
			const Global_Handle(Cad3d_PointOnPlane) theLastPoint_;

			Global_Handle(Cad3d_CurveOnPlane) theCurve_;

			const Global_Handle(Cad3d_WireOnPlane) theWire_;

			Standard_Integer theIndex_;

		public:

			Cad3d_EdgeOnPlane();

			Cad3d_EdgeOnPlane(const Standard_Integer theIndex, const Global_Handle(Cad3d_PointOnPlane) theFirstPoint, const Global_Handle(Cad3d_PointOnPlane) theLastPoint, Global_Handle(Cad3d_CurveOnPlane) theCurve);

			virtual ~Cad3d_EdgeOnPlane();

			virtual void Init(const Standard_Integer theIndex, const Global_Handle(Cad3d_PointOnPlane) theFirstPoint, const Global_Handle(Cad3d_PointOnPlane) theLastPoint, Global_Handle(Cad3d_CurveOnPlane) theCurve);

			virtual void Init(const Global_Handle(Cad3d_PointOnPlane) theFirstPoint, const Global_Handle(Cad3d_PointOnPlane) theLastPoint, Global_Handle(Cad3d_CurveOnPlane) theCurve);

			Global_Handle(Cad3d_CurveOnPlane) Curve() const;

			const Global_Handle(Cad3d_PointOnPlane) FirstPoint() const;

			const Global_Handle(Cad3d_PointOnPlane) LastPoint() const;

			const Global_Handle(Cad3d_WireOnPlane) Wire() const;

			Standard_Integer Index() const;

			GeoLib::Entity_Box2d BoundingBox(const Standard_Real theTolerance = 0.0) const;

			void SetIndex(const Standard_Integer theIndex);

			void SetWire(const Global_Handle(Cad3d_WireOnPlane) theWire);

			void Reverse();

			void Split(const Standard_Real theParameter, Global_Handle(Cad3d_PointOnPlane) thePoint, Global_Handle(Cad3d_EdgeOnPlane) theEdge1, Global_Handle(Cad3d_EdgeOnPlane) theEdge2) const;

			void Split(const TColStd_Ary1dOfReal& theParameters, TColCad3d_HAry1dOfPointOnPlane& thePoints, TColCad3d_HAry1dOfEdgeOnPlane& theEdges) const;

			void ExportToPlt(fstream& File) const;

			virtual Global_Handle(Cad3d_EdgeOnPlane) Copy() const;
		};
	}
}

#include <Cad3d_EdgeOnPlaneI.hxx>

#endif // !_Cad3d_EdgeOnPlane_Header
