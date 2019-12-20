#include <Cad2d_EdgeOnPlane.hxx>

#include <Global_Debug.hxx>
#include <Entity_Box2d.hxx>
#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_PointOnPlane.hxx>
#include <Cad2d_WireOnPlane.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace CadLib;

AutLib::CadLib::Cad2d_EdgeOnPlane::Cad2d_EdgeOnPlane()
	: theIndex_(0)
	, theFirstPoint_(0)
	, theLastPoint_(0)
	, theCurve_(0)
{
}

AutLib::CadLib::Cad2d_EdgeOnPlane::Cad2d_EdgeOnPlane
(
	const Standard_Integer theIndex, 
	const Global_Handle(Cad2d_PointOnPlane) theFirstPoint, 
	const Global_Handle(Cad2d_PointOnPlane) theLastPoint,
	Global_Handle(Cad2d_CurveOnPlane) theCurve
)
	: theIndex_(theIndex)
	, theFirstPoint_(theFirstPoint)
	, theLastPoint_(theLastPoint)
	, theCurve_(theCurve)
{
}

AutLib::CadLib::Cad2d_EdgeOnPlane::~Cad2d_EdgeOnPlane()
{
	FreePointer(theCurve_);
}

void AutLib::CadLib::Cad2d_EdgeOnPlane::Init
(
	const Standard_Integer theIndex, 
	const Global_Handle(Cad2d_PointOnPlane) theFirstPoint,
	const Global_Handle(Cad2d_PointOnPlane) theLastPoint, 
	Global_Handle(Cad2d_CurveOnPlane) theCurve
)
{
	theIndex_ = theIndex;
	theFirstPoint_ = theFirstPoint;
	theLastPoint_ = theLastPoint;
	theCurve_ = theCurve;
}

void AutLib::CadLib::Cad2d_EdgeOnPlane::Init
(
	const Global_Handle(Cad2d_PointOnPlane) theFirstPoint, 
	const Global_Handle(Cad2d_PointOnPlane) theLastPoint, 
	Global_Handle(Cad2d_CurveOnPlane) theCurve
)
{
	theFirstPoint_ = theFirstPoint;
	theLastPoint_ = theLastPoint;
	theCurve_ = theCurve;
}

Entity_Box2d AutLib::CadLib::Cad2d_EdgeOnPlane::BoundingBox(const Standard_Real theTolerance) const
{
	return theCurve_->BoundingBox(theTolerance);
}

void AutLib::CadLib::Cad2d_EdgeOnPlane::SetIndex(const Standard_Integer theIndex)
{
	theIndex_ = theIndex;
}

void AutLib::CadLib::Cad2d_EdgeOnPlane::SetWire(const Global_Handle(Cad2d_WireOnPlane) theWire)
{
	theWire_ = theWire;
}

void AutLib::CadLib::Cad2d_EdgeOnPlane::Reverse()
{
	Debug_Null_Pointer(theCurve_);
	theCurve_->Reverse();
	SWAP(theFirstPoint_, theLastPoint_);
}

//void AutLib::CadLib::Cad2d_EdgeOnPlane::Split
//(
//	const Standard_Real theParameter,
//	Global_Handle(Cad2d_PointOnPlane) thePoint,
//	Global_Handle(Cad2d_EdgeOnPlane) theEdge1,
//	Global_Handle(Cad2d_EdgeOnPlane) theEdge2
//) const
//{
//	Debug_Null_Pointer(theEdge1);
//	Debug_Null_Pointer(theEdge2);
//	Debug_Null_Pointer(thePoint);
//
//	Debug_Null_Pointer(theCurve_);
//
//	Global_Handle(Cad2d_CurveOnPlane) Curve1 = new Cad2d_CurveOnPlane;
//	Global_Handle(Cad2d_CurveOnPlane) Curve2 = new Cad2d_CurveOnPlane;
//
//	Geom_Pnt2d Coord;
//
//	theCurve_->Split(theParameter, Coord, Curve1, Curve2);
//
//	thePoint->SetCoord(Coord);
//
//	theEdge1->Init(theFirstPoint_, thePoint, Curve1);
//	theEdge2->Init(thePoint, theLastPoint_, Curve2);
//
//	theEdge1->SetWire(theWire_);
//	theEdge2->SetWire(theWire_);
//}

void AutLib::CadLib::Cad2d_EdgeOnPlane::Split
(
	const TColStd_Ary1dOfReal & theParameters,
	TColCad2d_HAry1dOfPointOnPlane & thePoints,
	TColCad2d_HAry1dOfEdgeOnPlane & theEdges
) const
{
	Debug_Null_Pointer(theCurve_);

	Standard_Integer MaxEdgeIndex = 0;
	Standard_Integer MaxPointIndex = 0;

	if (theWire_)
	{
		MaxEdgeIndex = theWire_->MaxEdgeIndex();
		MaxPointIndex = theWire_->MaxPointIndex();
	}

	TColGeom_Ary1dOfPnt2d Coords;
	TColCad2d_HAry1dOfCurveOnPlane Curves;

	theCurve_->Split(theParameters, Coords, Curves);

	thePoints.Resize(Coords.Size());
	forThose(Index, 0, MaxIndexOf(thePoints))
		thePoints[Index] = new Cad2d_PointOnPlane(NOT MaxPointIndex ? 0 : MaxPointIndex + Index + 1, Coords[Index]);

	TColCad2d_HAry1dOfPointOnPlane Points(thePoints.Size() + 2);
	Points.First() = (Global_Handle(Cad2d_PointOnPlane))theFirstPoint_;
	Points.Last() = (Global_Handle(Cad2d_PointOnPlane))theLastPoint_;

	forThose(Index, 0, MaxIndexOf(thePoints))
		Points[Index + 1] = thePoints[Index];


	theEdges.Resize(theEdges.Size());
	forThose
	(
		Index, 
		0, 
		MaxIndexOf(Curves)
	)
	{
		theEdges[Index] = new Cad2d_EdgeOnPlane(MaxEdgeIndex + Index + 1, Points[Index], Points[Index + 1], Curves[Index]);

		Try_Exception_Handle_Exit(Points[Index]->ImportEdge(theEdges[Index]));
		Try_Exception_Handle_Exit(Points[Index + 1]->ImportEdge(theEdges[Index]));

		theEdges[Index]->SetWire(theWire_);
	}
}

void AutLib::CadLib::Cad2d_EdgeOnPlane::ExportToPlt(fstream & File) const
{
	if (theCurve_) theCurve_->ExportToPlt(File);
}

Global_Handle(Cad2d_EdgeOnPlane) AutLib::CadLib::Cad2d_EdgeOnPlane::Copy() const
{
	/*Global_Handle(Cad2d_PointOnPlane) Point1 = theFirstPoint_->Copy();
	Global_Handle(Cad2d_PointOnPlane) Point2 = theLastPoint_->Copy();
	Global_Handle(Cad2d_EdgeOnPlane) Copy = new Cad2d_EdgeOnPlane(theIndex_, Point1, Point2, theCurve_->Copy());*/

	/*Try_Exception_Handle_Exit(Point1->ImportEdge(Copy));
	Try_Exception_Handle_Exit(Point2->ImportEdge(Copy));*/   // Debug: June 19, 2018

	Global_Handle(Cad2d_EdgeOnPlane) Copy = new Cad2d_EdgeOnPlane(theIndex_, NULL, NULL, theCurve_->Copy());   // Modify: June 19, 2018

	return Copy;
}