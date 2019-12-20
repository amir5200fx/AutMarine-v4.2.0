#include <Cad2d_PlanePlaneIntersection.hxx>

#include <Cad2d_Plane.hxx>
#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_EdgeEdgeIntersection.hxx>
#include <TColCad2d_HAry1dOfCurveOnPlane.hxx>
#include <TColCad2d_HBasicQueueOfEdgeEdgeIntersection.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

using namespace AutLib;
using namespace CadLib;

static const Standard_Real DEFAULT_INTERSECTION_TOLERANCE = 1.0E-9;

AutLib::CadLib::Cad2d_PlanePlaneIntersection::Cad2d_PlanePlaneIntersection()
	: thePlane1_(NULL)
	, thePlane2_(NULL)
	, IsDone_(Standard_False)
	, HasIntersection_(Standard_False)
	, theTolerance_(DEFAULT_INTERSECTION_TOLERANCE)
{
}

AutLib::CadLib::Cad2d_PlanePlaneIntersection::Cad2d_PlanePlaneIntersection
(
	const Global_Handle(Cad2d_Plane) thePlane1,
	const Global_Handle(Cad2d_Plane) thePlane2
)
	: thePlane1_(thePlane1)
	, thePlane2_(thePlane2)
	, IsDone_(Standard_False)
	, HasIntersection_(Standard_False)
	, theTolerance_(DEFAULT_INTERSECTION_TOLERANCE)
{
}

AutLib::CadLib::Cad2d_PlanePlaneIntersection::~Cad2d_PlanePlaneIntersection()
{
	FreeMemory(theIntersection_);
}

void AutLib::CadLib::Cad2d_PlanePlaneIntersection::Init
(
	const Global_Handle(Cad2d_Plane) thePlane1,
	const Global_Handle(Cad2d_Plane) thePlane2
)
{
	thePlane1_ = thePlane1;
	thePlane2_ = thePlane2;
}

Standard_Boolean AutLib::CadLib::Cad2d_PlanePlaneIntersection::IsDone() const
{
	return IsDone_;
}

Standard_Boolean AutLib::CadLib::Cad2d_PlanePlaneIntersection::HasIntersection() const
{
	return HasIntersection_;
}

const TColCad2d_HAry1dOfEdgeEdgeIntersection & AutLib::CadLib::Cad2d_PlanePlaneIntersection::Intersections() const
{
	return theIntersection_;
}

void AutLib::CadLib::Cad2d_PlanePlaneIntersection::Perform()
{
	TColCad2d_HAry1dOfEdgeOnPlane Curves1, Curves2;

	Debug_Null_Pointer(thePlane1_);
	Debug_Null_Pointer(thePlane2_);

	thePlane1_->RetrieveEdgesTo(Curves1);
	thePlane2_->RetrieveEdgesTo(Curves2);

	TColCad2d_HBasicQueueOfEdgeEdgeIntersection QInfo;
	forThose
	(
		Iter1,
		0, 
		MaxIndexOf(Curves1)
	)
	{
		Debug_Null_Pointer(Curves1[Iter1]);

		forThose
		(
			Iter2,
			0, 
			MaxIndexOf(Curves2)
		)
		{
			Debug_Null_Pointer(Curves2[Iter2]);

			Global_Handle(Cad2d_EdgeEdgeIntersection) Intersection = new Cad2d_EdgeEdgeIntersection(Curves1[Iter1], Curves2[Iter2], theTolerance_);
			Intersection->Perform();

			Debug_If_Condition_Message(NOT Intersection->IsDone(), "Edge-Edge Intersection IS NOT performed");

			if (Intersection->HasIntersection())
			{
				QInfo.EnQueue(Intersection);
			}
			else
			{
				FreePointer(Intersection);
			}
		}
	}
	QInfo.RetrieveTo(theIntersection_);

	if (NOT theIntersection_.IsEmpty()) HasIntersection_ = Standard_True;

	IsDone_ = Standard_True;
}

void AutLib::CadLib::Cad2d_PlanePlaneIntersection::ExportToPlt(fstream & File) const
{
	if (NOT IsDone_) return;

	forThose
	(
		Index,
		0, 
		MaxIndexOf(theIntersection_)
	)
	{
		Debug_Null_Pointer(theIntersection_[Index]);

		theIntersection_[Index]->ExportToPlt(File);
	}
}