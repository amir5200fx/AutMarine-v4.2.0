#pragma once
#ifndef _Cad2d_Plane_Header
#define _Cad2d_Plane_Header

#include <Cad2d_EdgesOnPlane.hxx>
#include <Cad2d_PointsOnPlane.hxx>
#include <Cad2d_OutterBoundaryOnPlane.hxx>
#include <Cad2d_InnerBoundariesOnPlane.hxx>
#include <TColCad2d_HAry1dOfWireOnPlane.hxx>
#include <TColCad2d_HAry1dOfEdgeOnPlane.hxx>
#include <TColCad2d_HAry1dOfPointOnPlane.hxx>
#include <TColCad2d_HAry1dOfCurveOnPlane.hxx>

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
		class Entity_StaticChain2d;
	}

	namespace CadLib
	{

		class Cad2d_Plane
		{

		protected:

			Standard_Integer theIndex_;

			Standard_String theName_;

			// Topological informations
			Global_Handle(Cad2d_EdgesOnPlane) theEdges_;
			Global_Handle(Cad2d_PointsOnPlane) theCorners_;

			Standard_Real theTolerance_;

			Cad2d_OutterBoundaryOnPlane theOutterWire_;

			Cad2d_InnerBoundariesOnPlane theInnerWires_;

		public:

			Cad2d_Plane();

			~Cad2d_Plane();

			//Throw an exception
			M_GEO Entity_Box2d BoundingBox(const Standard_Real Offset = 0.0) const;

			M_GEO Entity_StaticChain2d UniDiscrete(const Standard_Integer NbSegments) const;

			Global_Handle(Cad2d_EdgesOnPlane) Edges() const;

			Global_Handle(Cad2d_PointsOnPlane) Corners() const;

			Standard_Integer NbEdges() const;

			Standard_Integer NbCorners() const;

			Standard_Integer NbHoles() const;

			Standard_Integer NbFreeCorners() const;

			Standard_Boolean HasFreeCorner() const;

			void Make(const TColCad2d_HAry1dOfEdgeOnPlane& theEdges);

			void Make(const TColCad2d_HAry1dOfCurveOnPlane& theCurves, const Standard_Real theTolerance = 1.0E-6);

			void Make(const gp_Ax22d& A, const TColCad2d_HAry1dOfCurveOnPlane& theCurves, const Standard_Real theTolerance = 1.0E-6);

			void Make(const gp_Ax2d& A, const TColCad2d_HAry1dOfCurveOnPlane& theCurves, const Standard_Boolean Sense, const Standard_Real theTolerance = 1.0E-6);

			void SetName(const Standard_String Name);

			void RetrieveCornersTo(TColCad2d_HAry1dOfPointOnPlane& theCorners) const;

			void RetrieveEdgesTo(TColCad2d_HAry1dOfEdgeOnPlane& theEdges) const;

			void RetrieveCurvesTo(TColCad2d_HAry1dOfCurveOnPlane& theCurves) const;

			void CreateSharpCornerBlock(const Standard_Real theSharpAngle, const Standard_String theBlockName);

			void SplitByWires();

			void Mirror(const gp_Pnt2d& P);
							  
			void Mirror(const gp_Ax2d& A);
							  
			void Rotate(const gp_Pnt2d& P, const Standard_Real Ang);

			void Scale(const gp_Pnt2d& P, const Standard_Real S);

			void Translate(const gp_Vec2d& V);

			void Translate(const gp_Pnt2d& P1, const gp_Pnt2d& P2);

			void Transform(const gp_Trsf2d& T);

			void ExportToPlt(fstream& File) const;

			void Report(Standard_OStream& Ostream = cout) const;

			Global_Handle(Cad2d_Plane) Copy() const;

		protected:

			void CreateDefaultPatch(const TColCad2d_HAry1dOfEdgeOnPlane& Curves, const Standard_String theName = "Block Edge");

			void CreateDefaultPoints(const TColCad2d_HAry1dOfPointOnPlane& Points, const Standard_String theName = "Block Point");

			void CreateWires(const TColCad2d_HAry1dOfEdgeOnPlane& theEdges);

		};
	}
}

#include <Cad2d_PlaneI.hxx>

#endif // !_Cad2d_Plane_Header
