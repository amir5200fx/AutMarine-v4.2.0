#include <Cad2d_CurveCurveIntersection.hxx>

#include <Entity_Box2d.hxx>
#include <Entity_Box2dTools.hxx>
#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_PointIntersectionInfo.hxx>
#include <Cad2d_SegmentIntersectionInfo.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

#include <Geom2d_Curve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <Geom2dAdaptor_Curve.hxx>
#include <IntRes2d_Domain.hxx>
#include <IntRes2d_IntersectionSegment.hxx>
#include <Geom2dInt_GInter.hxx>
#include <Adaptor2d_Curve2d.hxx>

AutLib::CadLib::Cad2d_CurveCurveIntersection::Cad2d_CurveCurveIntersection()
	: theCurve1_(NULL)
	, theCurve2_(NULL)
	, theTolerance_(0)
	, HasIntersection_(Standard_False)
	, IsDone_(Standard_False)
{
}

AutLib::CadLib::Cad2d_CurveCurveIntersection::Cad2d_CurveCurveIntersection
(
	const Global_Handle(Cad2d_CurveOnPlane) theCurve1,
	const Global_Handle(Cad2d_CurveOnPlane) theCurve2, 
	const Standard_Real theTolerance
)
	: theCurve1_(theCurve1)
	, theCurve2_(theCurve2)
	, theTolerance_(theTolerance)
	, HasIntersection_(Standard_False)
	, IsDone_(Standard_False)
{
}

AutLib::CadLib::Cad2d_CurveCurveIntersection::~Cad2d_CurveCurveIntersection()
{
}

void AutLib::CadLib::Cad2d_CurveCurveIntersection::Init
(
	const Global_Handle(Cad2d_CurveOnPlane) theCurve1,
	const Global_Handle(Cad2d_CurveOnPlane) theCurve2, 
	const Standard_Real theTolerance
)
{
	theCurve1_ = theCurve1;
	theCurve2_ = theCurve2;

	theTolerance_ = theTolerance;
}

Standard_Boolean AutLib::CadLib::Cad2d_CurveCurveIntersection::IsDone() const
{
	return IsDone_;
}

Standard_Boolean AutLib::CadLib::Cad2d_CurveCurveIntersection::HasIntersection() const
{
	return HasIntersection_;
}

const Cad2d_IntersectionInfo & AutLib::CadLib::Cad2d_CurveCurveIntersection::Intersection() const
{
	return theIntersection_;
}

const Global_Handle(Cad2d_CurveOnPlane) AutLib::CadLib::Cad2d_CurveCurveIntersection::Curve1() const
{
	return theCurve1_;
}

const Global_Handle(Cad2d_CurveOnPlane) AutLib::CadLib::Cad2d_CurveCurveIntersection::Curve2() const
{
	return theCurve2_;
}

void AutLib::CadLib::Cad2d_CurveCurveIntersection::Perform()
{
	IsDone_ = Standard_True;

	Debug_Null_Pointer(theCurve1_);
	Debug_Null_Pointer(theCurve2_);

	Get_Const_Object(Curve1) = *theCurve1_;
	Get_Const_Object(Curve2) = *theCurve2_;

	Entity_Box2d Box1 = Curve1.BoundingBox(1.0E-6);
	Entity_Box2d Box2 = Curve2.BoundingBox(1.0E-6);

	if (NOT Entity_Box2dTools::IsIntersect(Box1, Box2)) return;

	/*Geom2dAPI_InterCurveCurve Intersection;
	Intersection.Init(Curve1.Curve(), Curve2.Curve(), theTolerance_);

	if (NOT Intersection.NbPoints()) return;
	if (NOT Intersection.NbSegments()) return;*/

	Geom2dAdaptor_Curve AdaptCurve1(Curve1.Curve(), Curve1.FirstParameter(), Curve1.LastParameter());
	Geom2dAdaptor_Curve AdaptCurve2(Curve2.Curve(), Curve2.FirstParameter(), Curve2.LastParameter());

	Geom2dInt_GInter Intersection;

	/*IntRes2d_Domain IntDomain1 = Intersection.ComputeDomain(AdaptCurve1, theTolerance_);
	IntRes2d_Domain IntDomain2 = Intersection.ComputeDomain(AdaptCurve2, theTolerance_);*/

	Intersection.Perform(AdaptCurve1, AdaptCurve2, theTolerance_, theTolerance_);
	
	TColCad2d_HAry1dOfPointIntersectionInfo Points;
	TColCad2d_HAry1dOfSegmentIntersectionInfo Segments;

	if (Intersection.NbPoints())
	{
		Points.Resize(Intersection.NbPoints());
		forThose
		(
			Index,
			1, 
			Intersection.NbPoints()
		)
		{
			Get_Const_Object(Info) = Intersection.Point(Index);
			Points[Index_Of(Index)] = new Cad2d_PointIntersectionInfo(Info.ParamOnFirst(), Info.ParamOnSecond(), Info.Value());
		}
	}

	if (Intersection.NbSegments())
	{
		Segments.Resize(Intersection.NbSegments());
		forThose
		(
			Index,
			1, 
			Intersection.NbSegments()
		)
		{
			Get_Const_Object(Info) = Intersection.Segment(Index);
			Get_Const_Object(IntP1) = Info.FirstPoint();
			Get_Const_Object(IntP2) = Info.LastPoint();

			Global_Handle(Cad2d_CurveOnPlane) IntCurve1 = new Cad2d_CurveOnPlane(IntP1.ParamOnFirst(), IntP2.ParamOnFirst(), Curve1.Curve());
			Global_Handle(Cad2d_CurveOnPlane) IntCurve2 = new Cad2d_CurveOnPlane(IntP1.ParamOnSecond(), IntP2.ParamOnSecond(), Curve2.Curve());

			Segments[Index_Of(Index)] = new Cad2d_SegmentIntersectionInfo(IntCurve1, IntCurve2);
		}
	}

	theIntersection_.Init(Points, Segments);

	if (Intersection.NbPoints() OR Intersection.NbSegments()) { HasIntersection_ = Standard_True; }
}

void AutLib::CadLib::Cad2d_CurveCurveIntersection::ExportToPlt(fstream & File) const
{
	theIntersection_.ExportToPlt(File);

	if (theCurve1_) theCurve1_->ExportToPlt(File);
	if (theCurve2_) theCurve2_->ExportToPlt(File);
}