#pragma once
#ifndef _Cad2d_Sketch_Header
#define _Cad2d_Sketch_Header

#include <Geom_ADTree2d.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColGeom_BasicQueueOfPnt2d.hxx>
#include <TColCad2d_HNumbAvlTreeOfPointOnPlane.hxx>
#include <TColCad2d_HNumbAvlTreeOfEdgeOnPlane.hxx>

class gp_Ax22d;
class gp_Ax2d;

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_PointOnPlane;
		class Cad2d_EdgeOnPlane;
		class Cad2d_Plane;

		class Cad2d_Sketch
		{

		private:

			GeoLib::Geom_ADTree2d<Cad2d_PointOnPlane*> theSearch_;

			TColCad2d_HNumbAvlTreeOfPointOnPlane thePoints_;
			TColCad2d_HNumbAvlTreeOfEdgeOnPlane theEdges_;

			Standard_Real theRadius_;

			Standard_Integer theNbPoints_;
			Standard_Integer theNbEdges_;

		public:

			Cad2d_Sketch();

			~Cad2d_Sketch();

			Global_Handle(Cad2d_PointOnPlane) CreatePoint(const Geom_Pnt2d& theCoord);

			Global_Handle(Cad2d_EdgeOnPlane) CreateLine(const Geom_Pnt2d& thePoint1, const Geom_Pnt2d& thePoint2);

			Standard_Boolean CreateRectangle(const Geom_Pnt2d& thePoint1, const Geom_Pnt2d& thePoint2);

			Standard_Boolean CreateCircle(const Geom_Pnt2d& theCentre, const Standard_Real theRadius, const Standard_Real theDegree);

			Standard_Boolean CreateEllipse(const Geom_Pnt2d& theCentre, const Standard_Real theMajorRadius, const Standard_Real theMinorRadius, const Standard_Real theDegree);

			Standard_Boolean CreateCircularArc(const Geom_Pnt2d& theCentre, const Standard_Real theRadius, const Standard_Real theDeg0, const Standard_Real theDeg1);

			Standard_Boolean CreatePolygon(const TColGeom_Ary1dOfPnt2d& thePoints);

			Standard_Boolean CreatePolygon(const TColGeom_BasicQueueOfPnt2d& thePoints);

			Standard_Boolean CreateInterpolation(const TColGeom_BasicQueueOfPnt2d& thePoints, const Standard_Integer theDeg = 2, const Standard_Real theTolerance = 1.0E-4);

			Standard_Boolean CreateInterpolation(const TColGeom_Ary1dOfPnt2d& thePoints, const Standard_Integer theDeg = 2, const Standard_Real theTolerance = 1.0E-4);

			Standard_Boolean RemovePoint(Global_Handle(Cad2d_PointOnPlane) thePoint);

			Global_Handle(Cad2d_Plane) MakePlane() const;

			Global_Handle(Cad2d_Plane) MakePlane(const gp_Ax22d & A) const;

			Global_Handle(Cad2d_Plane) MakePlane(const gp_Ax2d & A, const Standard_Boolean Sense = Standard_True) const;

			void Clear();

			void ExportToPlt(fstream& File) const;

		private:

			Global_Handle(Cad2d_PointOnPlane) CheckToInsert(const Global_Handle(Cad2d_PointOnPlane) thePoint) const;
		};
	}
}

#endif // !_Cad2d_Sketch_Header
