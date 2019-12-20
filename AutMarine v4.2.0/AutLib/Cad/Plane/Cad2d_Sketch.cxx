#include <Cad2d_Sketch.hxx>

#include <Entity_Box2dTools.hxx>
#include <Cad2d_PointOnPlane.hxx>
#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_MakeCurveOnPlane.hxx>
#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_RingOnPlane.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_PointOnPlaneTools.hxx>
#include <Cad2d_EdgeOnPlaneTools.hxx>
#include <Cad2d_SketchMaxCoords.hxx>
#include <IO_Tecplot.hxx>
#include <TColCad2d_HAry1dOfPointOnPlane.hxx>
#include <TColCad2d_HAry1dOfCurveOnPlane.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

#include <gp_Ax22d.hxx>

static const Standard_Real DEFAULT_Radius = 1.0E-3;

AutLib::CadLib::Cad2d_Sketch::Cad2d_Sketch()
	: theNbPoints_(0)
	, theNbEdges_(0)
	, theRadius_(DEFAULT_Radius)
{
	Entity_Box2d Domain(Cad2d_SketchMaxCoords::MinXCoord(), Cad2d_SketchMaxCoords::MaxXCoord(), Cad2d_SketchMaxCoords::MinYCoord(), Cad2d_SketchMaxCoords::MaxYCoord());

	theSearch_.SetRegion(Domain);
	theSearch_.SetCoordinateFunction(&Cad2d_PointOnPlaneTools::CoordOf);

	thePoints_.SetComparable(&Cad2d_PointOnPlaneTools::IsLess);

	theEdges_.SetComparable(&Cad2d_EdgeOnPlaneTools::IsLess);
}

AutLib::CadLib::Cad2d_Sketch::~Cad2d_Sketch()
{
	Clear();
}

Global_Handle(Cad2d_PointOnPlane) AutLib::CadLib::Cad2d_Sketch::CreatePoint(const Geom_Pnt2d & theCoord)
{
	Global_Handle(Cad2d_PointOnPlane) Point = new Cad2d_PointOnPlane(theNbPoints_ + 1, theCoord);
	Global_Handle(Cad2d_PointOnPlane) Created = CheckToInsert(Point);

	if (Created)
	{
		FreePointer(Point);
		return Created;
	}

	theSearch_.Insert(Point);
	Try_Exception_Handle_Exit(thePoints_.Insert(Point));

	theNbPoints_++;

	return Point;
}

Global_Handle(Cad2d_EdgeOnPlane) AutLib::CadLib::Cad2d_Sketch::CreateLine(const Geom_Pnt2d & thePoint1, const Geom_Pnt2d & thePoint2)
{
	Global_Handle(Cad2d_PointOnPlane) Point1 = CreatePoint(thePoint1);
	Global_Handle(Cad2d_PointOnPlane) Point2 = CreatePoint(thePoint2);

	Global_Handle(Cad2d_MakeCurveOnPlane) newCurve = new Cad2d_MakeCurveOnPlane;
	newCurve->LineSegment(Point1->Coord(), Point2->Coord());

	Global_Handle(Cad2d_EdgeOnPlane) newEdge = new Cad2d_EdgeOnPlane(theNbEdges_ + 1, Point1, Point2, newCurve);

	theNbEdges_++;

	Point1->ImportEdge(newEdge);
	Point2->ImportEdge(newEdge);

	Try_Exception_Handle_Exit(theEdges_.Insert(newEdge));

	return newEdge;
}

Standard_Boolean AutLib::CadLib::Cad2d_Sketch::CreateRectangle
(
	const Geom_Pnt2d & thePoint1,
	const Geom_Pnt2d & thePoint2
)
{
	Geom_Pnt2d P0 = thePoint1;
	Geom_Pnt2d P1 = Geom_Pnt2d(thePoint2.X(), thePoint1.Y());
	Geom_Pnt2d P2 = thePoint2;
	Geom_Pnt2d P3 = Geom_Pnt2d(thePoint1.X(), thePoint2.Y());

	Global_Handle(Cad2d_PointOnPlane) Point0 = CreatePoint(P0);
	Global_Handle(Cad2d_PointOnPlane) Point1 = CreatePoint(P1);
	Global_Handle(Cad2d_PointOnPlane) Point2 = CreatePoint(P2);
	Global_Handle(Cad2d_PointOnPlane) Point3 = CreatePoint(P3);

	CreateLine(P0, P1);
	CreateLine(P1, P2);
	CreateLine(P2, P3);
	CreateLine(P3, P0);

	return Standard_True;
}

Standard_Boolean AutLib::CadLib::Cad2d_Sketch::CreateCircle
(
	const Geom_Pnt2d & theCentre, 
	const Standard_Real theRadius, 
	const Standard_Real theDegree
)
{
	Geom_Pnt2d P0 = theCentre;
	Geom_Pnt2d P1 = P0 + Geom_Pnt2d(theRadius*cos(Geometry_Tools::DegToRadian(theDegree)), theRadius*sin(Geometry_Tools::DegToRadian(theDegree)));

	Global_Handle(Cad2d_PointOnPlane) Point = CreatePoint(P1);

	gp_Ax22d A(P0, gp_Dir2d(gp_Vec2d(P0, P1)));

	Global_Handle(Cad2d_MakeCurveOnPlane) newCurve = new Cad2d_MakeCurveOnPlane;
	newCurve->CircularArc(A, theRadius, 0, 360);

	Global_Handle(Cad2d_RingOnPlane) Ring = new Cad2d_RingOnPlane(theNbEdges_ + 1, Point, newCurve);
	theNbEdges_++;

	Point->ImportEdge(Ring);

	Try_Exception_Handle_Exit(theEdges_.Insert(Ring));

	return Standard_True;
}

Standard_Boolean AutLib::CadLib::Cad2d_Sketch::CreateEllipse
(
	const Geom_Pnt2d & theCentre,
	const Standard_Real theMajorRadius,
	const Standard_Real theMinorRadius,
	const Standard_Real theDegree
)
{
	Geom_Pnt2d P0 = theCentre;
	Geom_Pnt2d P1 = P0 + Geom_Pnt2d(theMajorRadius*cos(Geometry_Tools::DegToRadian(theDegree)), theMajorRadius*sin(Geometry_Tools::DegToRadian(theDegree)));

	Global_Handle(Cad2d_PointOnPlane) Point = CreatePoint(P1);

	gp_Ax22d A(P0, gp_Dir2d(gp_Vec2d(P0, P1)));

	Global_Handle(Cad2d_MakeCurveOnPlane) newCurve = new Cad2d_MakeCurveOnPlane;
	newCurve->Ellipse(A, theMajorRadius, theMinorRadius);

	Global_Handle(Cad2d_RingOnPlane) Ring = new Cad2d_RingOnPlane(theNbEdges_ + 1, Point, newCurve);
	theNbEdges_++;

	Point->ImportEdge(Ring);

	Try_Exception_Handle_Exit(theEdges_.Insert(Ring));

	return Standard_True;
}

Standard_Boolean AutLib::CadLib::Cad2d_Sketch::CreateCircularArc
(
	const Geom_Pnt2d & theCentre,
	const Standard_Real theRadius,
	const Standard_Real theDeg0,
	const Standard_Real theDeg1
)
{
	Geom_Pnt2d P0 = theCentre;
	Geom_Pnt2d P1 = P0 + Geom_Pnt2d(theRadius*cos(Geometry_Tools::DegToRadian(theDeg0)), theRadius*sin(Geometry_Tools::DegToRadian(theDeg0)));
	Geom_Pnt2d P2 = P0 + Geom_Pnt2d(theRadius*cos(Geometry_Tools::DegToRadian(theDeg1)), theRadius*sin(Geometry_Tools::DegToRadian(theDeg1)));

	gp_Ax22d A(P0, gp_Dir2d(gp_Vec2d(P0, P1)));

	if (Distance(P1, P2) <= theRadius_) { return CreateCircle(theCentre, theRadius, theDeg0); }

	Global_Handle(Cad2d_PointOnPlane) Point1 = CreatePoint(P1);
	Global_Handle(Cad2d_PointOnPlane) Point2 = CreatePoint(P2);

	Global_Handle(Cad2d_MakeCurveOnPlane) newCurve = new Cad2d_MakeCurveOnPlane;
	newCurve->CircularArc(A, theRadius, theDeg0, theDeg1);

	Global_Handle(Cad2d_EdgeOnPlane) newEdge = new Cad2d_EdgeOnPlane(theNbEdges_ + 1, Point1, Point2, newCurve);

	theNbEdges_++;

	Point1->ImportEdge(newEdge);
	Point2->ImportEdge(newEdge);

	Try_Exception_Handle_Exit(theEdges_.Insert(newEdge));

	return newEdge;
}

Standard_Boolean AutLib::CadLib::Cad2d_Sketch::CreatePolygon(const TColGeom_Ary1dOfPnt2d & thePoints)
{
	forThose(Index, 0, MaxIndexOf(thePoints) - 1)
		CreateLine(thePoints[Index], thePoints[Index + 1]);
	return Standard_True;
}

Standard_Boolean AutLib::CadLib::Cad2d_Sketch::CreatePolygon(const TColGeom_BasicQueueOfPnt2d & thePoints)
{
	TColGeom_Ary1dOfPnt2d Points;
	thePoints.RetrieveTo(Points);

	return CreatePolygon(Points);
}

Standard_Boolean AutLib::CadLib::Cad2d_Sketch::CreateInterpolation
(
	const TColGeom_BasicQueueOfPnt2d & thePoints,
	const Standard_Integer theDeg, 
	const Standard_Real theTolerance
)
{
	TColGeom_Ary1dOfPnt2d Points;
	thePoints.RetrieveTo(Points);

	return CreateInterpolation(Points, theDeg, theTolerance);
}

Standard_Boolean AutLib::CadLib::Cad2d_Sketch::CreateInterpolation
(
	const TColGeom_Ary1dOfPnt2d & thePoints, 
	const Standard_Integer theDeg,
	const Standard_Real theTolerance
)
{
	Global_Handle(Cad2d_CurveOnPlane) Curve = new Cad2d_CurveOnPlane;
	Curve->Interpolation(thePoints, theDeg, theTolerance);

	Geom_Pnt2d P1 = Curve->FirstCoord();
	Geom_Pnt2d P2 = Curve->LastCoord();

	Global_Handle(Cad2d_PointOnPlane) Point1 = CreatePoint(P1);
	Global_Handle(Cad2d_PointOnPlane) Point2 = CreatePoint(P2);

	Global_Handle(Cad2d_EdgeOnPlane) newEdge = new Cad2d_EdgeOnPlane(theNbEdges_ + 1, Point1, Point2, Curve);

	theNbEdges_++;

	Point1->ImportEdge(newEdge);
	Point2->ImportEdge(newEdge);

	Try_Exception_Handle_Exit(theEdges_.Insert(newEdge));

	return newEdge;
}

Standard_Boolean AutLib::CadLib::Cad2d_Sketch::RemovePoint(Global_Handle(Cad2d_PointOnPlane) thePoint)
{
	Debug_Null_Pointer(thePoint);

	if (NOT thePoint->IsOrphan()) { return Standard_False; }

	Try_Exception_Handle_Exit(theSearch_.Remove(thePoint));
	Try_Exception_Handle_Exit(thePoints_.Remove(thePoint));

	return Standard_True;
}

namespace AutLib
{
	namespace CadLib
	{

		Standard_Boolean CheckValidShell(const TColCad2d_HAry1dOfEdgeOnPlane& theEdges)
		{
			forThose
			(
				Index,
				0,
				MaxIndexOf(theEdges)
			)
			{
				Debug_Null_Pointer(theEdges[Index]);

				Get_Const_Object(Point1) = theEdges[Index]->FirstPoint();
				Get_Const_Object(Point2) = theEdges[Index]->LastPoint();

				if (Point1->IsFree()) { return Standard_True; }
				if (Point2->IsFree()) { return Standard_True; }
			}

			return Standard_False;
		}
	}
}

Global_Handle(Cad2d_Plane) AutLib::CadLib::Cad2d_Sketch::MakePlane() const
{
	TColCad2d_HAry1dOfEdgeOnPlane Edges;
	theEdges_.RetrieveTo(Edges);

	if (::CheckValidShell(Edges)) { THROW_STANDARD_EXCEPTION("Invalid Shell"); }

	TColCad2d_HAry1dOfCurveOnPlane Curves(Edges.Size());
	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		Curves[Index] = Edges[Index]->Curve()->Copy();
	}

	Global_Handle(Cad2d_Plane) newPlane = new Cad2d_Plane;
	newPlane->Make(Curves);
	return newPlane;
}

Global_Handle(Cad2d_Plane) AutLib::CadLib::Cad2d_Sketch::MakePlane(const gp_Ax22d & A) const
{
	TColCad2d_HAry1dOfEdgeOnPlane Edges;
	theEdges_.RetrieveTo(Edges);

	if (::CheckValidShell(Edges)) { THROW_STANDARD_EXCEPTION("Invalid Shell"); }

	TColCad2d_HAry1dOfCurveOnPlane Curves(Edges.Size());
	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		Curves[Index] = Edges[Index]->Curve()->Copy();
	}

	Global_Handle(Cad2d_Plane) newPlane = new Cad2d_Plane;
	newPlane->Make(A, Curves);
	return newPlane;
}

Global_Handle(Cad2d_Plane) AutLib::CadLib::Cad2d_Sketch::MakePlane
(
	const gp_Ax2d & A, 
	const Standard_Boolean Sense
) const
{
	TColCad2d_HAry1dOfEdgeOnPlane Edges;
	theEdges_.RetrieveTo(Edges);

	if (::CheckValidShell(Edges)) { THROW_STANDARD_EXCEPTION("Invalid Shell"); }

	TColCad2d_HAry1dOfCurveOnPlane Curves(Edges.Size());
	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		Curves[Index] = Edges[Index]->Curve()->Copy();
	}

	Global_Handle(Cad2d_Plane) newPlane = new Cad2d_Plane;
	newPlane->Make(A, Curves, Sense);
	return newPlane;
}

void AutLib::CadLib::Cad2d_Sketch::Clear()
{
	TColCad2d_HAry1dOfPointOnPlane Points;
	thePoints_.RetrieveTo(Points);

	TColCad2d_HAry1dOfEdgeOnPlane Edges;
	theEdges_.RetrieveTo(Edges);

	FreeMemory(Points);
	FreeMemory(Edges);
}

void AutLib::CadLib::Cad2d_Sketch::ExportToPlt(fstream & File) const
{
	TColCad2d_HAry1dOfPointOnPlane Points;
	thePoints_.RetrieveTo(Points);

	TColCad2d_HAry1dOfEdgeOnPlane Edges;
	theEdges_.RetrieveTo(Edges);

	M_IO IO_TecPlot::ExportPoints(Cad2d_PointOnPlaneTools::GetCoordsOf(Points), File);

	forThose(Index, 0, MaxIndexOf(Edges))
	{
		Debug_Null_Pointer(Edges[Index]);
		Edges[Index]->ExportToPlt(File);
	}
}

Global_Handle(Cad2d_PointOnPlane) AutLib::CadLib::Cad2d_Sketch::CheckToInsert(const Global_Handle(Cad2d_PointOnPlane) thePoint) const
{
	TColCad2d_HAry1dOfPointOnPlane Points;
	theSearch_.Search(Entity_Box2dTools::BoxOf(thePoint->Coord(), theRadius_), Points);

	if (Points.IsEmpty()) { return NULL; }

	forThose(Index, 0, MaxIndexOf(Points))
		if (Distance(Points[Index]->Coord(), thePoint->Coord()) <= theRadius_) { return Points[Index]; }
	return NULL;
}