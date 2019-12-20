#pragma once
#ifndef _Cad3d_Plane_Header
#define _Cad3d_Plane_Header

#include <Cad3d_OutterBoundaryOnPlane.hxx>
#include <Cad3d_InnerBoundariesOnPlane.hxx>
#include <TColCad3d_HAry1dOfEdgeOnPlane.hxx>
#include <TColCad3d_HAry1dOfCurveOnPlane.hxx>
#include <TColCad3d_HAry1dOfPointOnPlane.hxx>

namespace AutLib
{

	namespace GeoLib
	{
		class Entity_Box2d;
		class Entity_StaticChain2d;
	}

	namespace CadLib
	{

		class Cad3d_Plane
		{

		private:

			Standard_Integer theIndex_;

			Standard_String theName_;

			Standard_Real theTolerance_;

			TColCad3d_HAry1dOfEdgeOnPlane theEdges_;
			TColCad3d_HAry1dOfPointOnPlane theCorners_;

			Cad3d_OutterBoundaryOnPlane theOutterWire_;

			Cad3d_InnerBoundariesOnPlane theInnerWires_;

		public:

			Cad3d_Plane();

			~Cad3d_Plane();

			M_GEO Entity_Box2d BoundingBox(const Standard_Real Offset = 0.0) const;

			M_GEO Entity_StaticChain2d UniDiscrete(const Standard_Integer NbSegments) const;

			const TColCad3d_HAry1dOfEdgeOnPlane& Edges() const;

			const TColCad3d_HAry1dOfPointOnPlane& Corners() const;

			const Cad3d_OutterBoundaryOnPlane& OutterWire() const;

			const Cad3d_InnerBoundariesOnPlane& InnerWires() const;

			const Global_Handle(Cad3d_WireOnPlane) InnerWire(const Standard_Integer theIndex) const;

			Standard_Integer NbEdges() const;

			Standard_Integer NbHoles() const;

			Standard_Integer NbFreeCorners() const;

			Standard_Boolean HasFreeCorner() const;

			//! Return true if there is a wire with wrong orientation
			Standard_Boolean CheckOrientations(const Standard_Boolean Reversed = Standard_False) const;

			void Make(const TColCad3d_HAry1dOfEdgeOnPlane& theEdges);

			void Make(const TColCad3d_HAry1dOfCurveOnPlane& theCurves, const Standard_Real theTolerance = 1.0E-6);

			void SetName(const Standard_String Name);

			void RetrieveCurvesTo(TColCad3d_HAry1dOfCurveOnPlane& theCurves) const;

			void ExportToPlt(fstream& File) const;

			void ExportWiresToPlt(fstream& File) const;

			void Report(Standard_OStream& Ostream = cout) const;

			Global_Handle(Cad3d_Plane) Copy() const;

		private:

			void CreateWires(const TColCad3d_HAry1dOfEdgeOnPlane& theEdges);
		};
	}
}

#include <Cad3d_PlaneI.hxx>

#endif // !_Cad3d_Plane_Header
