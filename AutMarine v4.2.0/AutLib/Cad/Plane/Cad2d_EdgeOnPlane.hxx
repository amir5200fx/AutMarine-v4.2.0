#pragma once
#ifndef _Cad2d_EdgeOnPlane_Header
#define _Cad2d_EdgeOnPlane_Header

#include <Standard_TypeDef.hxx>
#include <Global_Memory.hxx>
#include <Standard_Stream.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColCad2d_HAry1dOfPointOnPlane.hxx>
#include <TColCad2d_HAry1dOfEdgeOnPlane.hxx>

class Geom2d_Curve;

namespace AutLib
{

	namespace GeoLib
	{
		class Entity_Box2d;
	}

	namespace CadLib
	{

		class Cad2d_PointOnPlane;
		class Cad2d_CurveOnPlane;
		class Cad2d_WireOnPlane;

		class Cad2d_EdgeOnPlane
		{

		protected:

			const Global_Handle(Cad2d_PointOnPlane) theFirstPoint_;
			const Global_Handle(Cad2d_PointOnPlane) theLastPoint_;

			Global_Handle(Cad2d_CurveOnPlane) theCurve_;

			const Global_Handle(Cad2d_WireOnPlane) theWire_;

			Standard_Integer theIndex_;

		public:

			Cad2d_EdgeOnPlane();

			Cad2d_EdgeOnPlane(const Standard_Integer theIndex, const Global_Handle(Cad2d_PointOnPlane) theFirstPoint, const Global_Handle(Cad2d_PointOnPlane) theLastPoint, Global_Handle(Cad2d_CurveOnPlane) theCurve);

			virtual ~Cad2d_EdgeOnPlane();

			virtual void Init(const Standard_Integer theIndex, const Global_Handle(Cad2d_PointOnPlane) theFirstPoint, const Global_Handle(Cad2d_PointOnPlane) theLastPoint, Global_Handle(Cad2d_CurveOnPlane) theCurve);

			virtual void Init(const Global_Handle(Cad2d_PointOnPlane) theFirstPoint, const Global_Handle(Cad2d_PointOnPlane) theLastPoint, Global_Handle(Cad2d_CurveOnPlane) theCurve);

			Global_Handle(Cad2d_CurveOnPlane) Curve() const;

			const Global_Handle(Cad2d_PointOnPlane) FirstPoint() const;

			const Global_Handle(Cad2d_PointOnPlane) LastPoint() const;

			const Global_Handle(Cad2d_WireOnPlane) Wire() const;

			Standard_Integer Index() const;

			GeoLib::Entity_Box2d BoundingBox(const Standard_Real theTolerance = 0.0) const;

			void SetIndex(const Standard_Integer theIndex);

			void SetWire(const Global_Handle(Cad2d_WireOnPlane) theWire);

			void Reverse();

			void Split(const Standard_Real theParameter, Global_Handle(Cad2d_PointOnPlane) thePoint, Global_Handle(Cad2d_EdgeOnPlane) theEdge1, Global_Handle(Cad2d_EdgeOnPlane) theEdge2) const;

			void Split(const TColStd_Ary1dOfReal& theParameters, TColCad2d_HAry1dOfPointOnPlane& thePoints, TColCad2d_HAry1dOfEdgeOnPlane& theEdges) const;

			void ExportToPlt(fstream& File) const;

			virtual Global_Handle(Cad2d_EdgeOnPlane) Copy() const;
		};
	}
}

#include <Cad2d_EdgeOnPlaneI.hxx>

#endif // !_Cad2d_EdgeOnPlane_Header
