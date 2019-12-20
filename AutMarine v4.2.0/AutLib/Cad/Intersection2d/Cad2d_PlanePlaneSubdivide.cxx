#include <Cad2d_PlanePlaneSubdivide.hxx>

#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_WireOnPlane.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_PointIntersectionInfo.hxx>
#include <Cad2d_IntersectionInfo.hxx>
#include <Cad2d_CurveCurveIntersection.hxx>
#include <Cad2d_EdgeEdgeIntersection.hxx>
#include <Cad2d_PlanePlaneIntersection.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColStd_BasicQueueOfReal.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColCad2d_HBasicQueueOfCurveOnPlane.hxx>
#include <TColCad2d_HBasicQueueOfEdgeOnPlane.hxx>
#include <TColCad2d_HAry1dOfCurveCurveIntersection.hxx>

using namespace AutLib;
using namespace CadLib;

#include <map>

AutLib::CadLib::Cad2d_PlanePlaneSubdivide::Cad2d_PlanePlaneSubdivide()
	: IsDone_(Standard_False)
	, AreSubdivided_(Standard_False)
	, thePlane1_(NULL)
	, thePlane2_(NULL)
{
}

AutLib::CadLib::Cad2d_PlanePlaneSubdivide::Cad2d_PlanePlaneSubdivide
(
	const Global_Handle(Cad2d_Plane) thePlane1, 
	const Global_Handle(Cad2d_Plane) thePlane2
)
	: IsDone_(Standard_False)
	, AreSubdivided_(Standard_False)
	, thePlane1_(thePlane1)
	, thePlane2_(thePlane2)
{
}

AutLib::CadLib::Cad2d_PlanePlaneSubdivide::~Cad2d_PlanePlaneSubdivide()
{
	//Clear();
}

void AutLib::CadLib::Cad2d_PlanePlaneSubdivide::Init
(
	const Global_Handle(Cad2d_Plane) thePlane1, 
	const Global_Handle(Cad2d_Plane) thePlane2
)
{
	thePlane1_ = thePlane1;
	thePlane2_ = thePlane2;
}

namespace AutLib
{
	typedef std::map<Global_Handle(M_CAD Cad2d_EdgeOnPlane), Global_Handle(TColStd_BasicQueueOfReal)> MapEdgeToQueueOfReal;
	typedef std::map<Global_Handle(M_CAD Cad2d_CurveOnPlane), Global_Handle(TColStd_BasicQueueOfReal)> MapCurveToQueueOfReal;
}

namespace AutLib
{
	namespace CadLib
	{
		static inline void IntersectionParameters(const Cad2d_EdgeEdgeIntersection& theInfo, MapCurveToQueueOfReal& theMap)
		{
			Debug_If_Condition(NOT theInfo.HasIntersection());

			Global_Handle(Cad2d_CurveOnPlane) Curve1 = (Global_Handle(Cad2d_CurveOnPlane))theInfo.Edge1()->Curve();
			Global_Handle(Cad2d_CurveOnPlane) Curve2 = (Global_Handle(Cad2d_CurveOnPlane))theInfo.Edge2()->Curve();

			Get_Const_Object(IntersectionInfo) = theInfo.Intersection();

			Global_Handle(TColStd_BasicQueueOfReal) QParameters1 = new TColStd_BasicQueueOfReal;
			Global_Handle(TColStd_BasicQueueOfReal) QParameters2 = new TColStd_BasicQueueOfReal;
			Standard_Integer NbPoints = IntersectionInfo.NbPoints();
			forThose
			(
				Index,
				1,
				NbPoints
			)
			{
				Get_Const_Object(IntPoint) = IntersectionInfo.Point(Index_Of(Index));

				QParameters1->EnQueue(IntPoint.Parameter1());
				QParameters2->EnQueue(IntPoint.Parameter2());
			}

			MapCurveToQueueOfReal::const_iterator Iter1 = theMap.find(Curve1);
			MapCurveToQueueOfReal::const_iterator Iter2 = theMap.find(Curve2);

			if (Iter1 EQUAL theMap.end())
			{
				std::pair<MapCurveToQueueOfReal::iterator, Standard_Boolean> Insert;
				Insert = theMap.insert(std::pair<Global_Handle(M_CAD Cad2d_CurveOnPlane), Global_Handle(TColStd_BasicQueueOfReal)>(Curve1, QParameters1));

				Debug_If_Condition_Message(NOT Insert.second, "Something Wrong to insert parameters");
			}
			else
			{
				Get_Object(QParameters) = *Iter1->second;
				QParameters.EnQueue(*QParameters1);

				FreePointer(QParameters1);
			}

			if (Iter2 EQUAL theMap.end())
			{
				std::pair<MapCurveToQueueOfReal::iterator, Standard_Boolean> Insert;
				Insert = theMap.insert(std::pair<Global_Handle(M_CAD Cad2d_CurveOnPlane), Global_Handle(TColStd_BasicQueueOfReal)>(Curve2, QParameters2));

				Debug_If_Condition_Message(NOT Insert.second, "Something Wrong to insert parameters");
			}
			else
			{
				Get_Object(QParameters) = *Iter2->second;
				QParameters.EnQueue(*QParameters2);

				FreePointer(QParameters2);
			}
		}

		/*static inline void IntersectionParameters(const Cad2d_EdgeEdgeIntersection& theInfo, MapEdgeToQueueOfReal& theMap)
		{
			Debug_If_Condition(NOT theInfo.HasIntersection());

			Global_Handle(Cad2d_EdgeOnPlane) Edge1 = (Global_Handle(Cad2d_EdgeOnPlane))theInfo.Edge1();
			Global_Handle(Cad2d_EdgeOnPlane) Edge2 = (Global_Handle(Cad2d_EdgeOnPlane))theInfo.Edge2();

			Get_Const_Object(IntersectionInfo) = theInfo.Intersection();

			Global_Handle(TColStd_BasicQueueOfReal) QParameters1 = new TColStd_BasicQueueOfReal;
			Global_Handle(TColStd_BasicQueueOfReal) QParameters2 = new TColStd_BasicQueueOfReal;
			Standard_Integer NbPoints = IntersectionInfo.NbPoints();
			forThose
			(
				Index,
				1, 
				NbPoints
			)
			{
				Get_Const_Object(IntPoint) = IntersectionInfo.Point(Index_Of(Index));

				QParameters1->EnQueue(IntPoint.Parameter1());
				QParameters2->EnQueue(IntPoint.Parameter2());
			}

			MapEdgeToQueueOfReal::const_iterator Iter1 = theMap.find(Edge1);
			MapEdgeToQueueOfReal::const_iterator Iter2 = theMap.find(Edge2);

			if (Iter1 EQUAL theMap.end())
			{
				std::pair<MapEdgeToQueueOfReal::iterator, Standard_Boolean> Insert;
				Insert = theMap.insert(std::pair<Global_Handle(M_CAD Cad2d_EdgeOnPlane), Global_Handle(TColStd_BasicQueueOfReal)>(Edge1, QParameters1));

				Debug_If_Condition_Message(NOT Insert.second, "Something Wrong to insert parameters");
			}
			else
			{
				Get_Object(QParameters) = *Iter1->second;
				QParameters.EnQueue(*QParameters1);

				FreePointer(QParameters1);
			}

			if (Iter2 EQUAL theMap.end())
			{
				std::pair<MapEdgeToQueueOfReal::iterator, Standard_Boolean> Insert;
				Insert = theMap.insert(std::pair<Global_Handle(M_CAD Cad2d_EdgeOnPlane), Global_Handle(TColStd_BasicQueueOfReal)>(Edge2, QParameters2));

				Debug_If_Condition_Message(NOT Insert.second, "Something Wrong to insert parameters");
			}
			else
			{
				Get_Object(QParameters) = *Iter2->second;
				QParameters.EnQueue(*QParameters2);

				FreePointer(QParameters2);
			}
			
		}*/

		/*static void IntersectionParameters(const TColCad2d_HAry1dOfEdgeEdgeIntersection& theInfo, MapEdgeToQueueOfReal& theMap)
		{
			forThose
			(
				Index,
				0, 
				MaxIndexOf(theInfo)
			)
			{
				Debug_Null_Pointer(theInfo[Index]);

				IntersectionParameters(*theInfo[Index], theMap);
			}
		}*/

		static void IntersectionParameters(const TColCad2d_HAry1dOfEdgeEdgeIntersection& theInfo, MapCurveToQueueOfReal& theMap)
		{
			forThose
			(
				Index,
				0,
				MaxIndexOf(theInfo)
			)
			{
				Debug_Null_Pointer(theInfo[Index]);

				IntersectionParameters(*theInfo[Index], theMap);
			}
		}
	}
}

void AutLib::CadLib::Cad2d_PlanePlaneSubdivide::Perform()
{
	Debug_Null_Pointer(thePlane1_);
	Debug_Null_Pointer(thePlane2_);

	Cad2d_PlanePlaneIntersection Intersection;
	Intersection.Init(thePlane1_, thePlane2_);

	Intersection.Perform();

	Debug_If_Condition_Message(NOT Intersection.IsDone(), " Intersection not performed");

	Get_Const_Object(Info) = Intersection.Intersections();

	IsDone_ = Standard_True;

	if (NOT Intersection.HasIntersection()) return;

	AreSubdivided_ = Standard_True;

	MapCurveToQueueOfReal Map;
	::IntersectionParameters(Intersection.Intersections(), Map);

	TColCad2d_HAry1dOfCurveOnPlane Curves1, Curves2;
	thePlane1_->RetrieveCurvesTo(Curves1);
	thePlane2_->RetrieveCurvesTo(Curves2);

	TColCad2d_HBasicQueueOfCurveOnPlane QCurves1;
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Curves1)
	)
	{
		Debug_Null_Pointer(Curves1[Index]);

		MapCurveToQueueOfReal::iterator Iter = Map.find(Curves1[Index]);
		if (Iter EQUAL Map.end())
		{
			QCurves1.EnQueue(Curves1[Index]->Copy());
		}
		else
		{
			TColStd_Ary1dOfReal Parameters;
			Iter->second->RetrieveTo(Parameters);

			Debug_If_Condition_Message(Parameters.IsEmpty(), "The List is empty");

			TColGeom_Ary1dOfPnt2d Coords;
			TColCad2d_HAry1dOfCurveOnPlane Curves;
			Curves1[Index]->Split(Parameters, Coords, Curves);

			QCurves1.EnQueue(Curves);

			FreePointer(Iter->second);
		}
	}

	TColCad2d_HBasicQueueOfCurveOnPlane QCurves2;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Curves2)
	)
	{
		Debug_Null_Pointer(Curves2[Index]);

		MapCurveToQueueOfReal::iterator Iter = Map.find(Curves2[Index]);
		if (Iter EQUAL Map.end())
		{
			QCurves2.EnQueue(Curves2[Index]->Copy());
		}
		else
		{
			TColStd_Ary1dOfReal Parameters;
			Iter->second->RetrieveTo(Parameters);

			Debug_If_Condition_Message(Parameters.IsEmpty(), "The List is empty");

			TColGeom_Ary1dOfPnt2d Coords;
			TColCad2d_HAry1dOfCurveOnPlane Curves;
			Curves2[Index]->Split(Parameters, Coords, Curves);

			QCurves2.EnQueue(Curves);

			FreePointer(Iter->second);
		}
	}

	theSubdivided1_ = new Cad2d_Plane;
	theSubdivided2_ = new Cad2d_Plane;

	QCurves1.RetrieveTo(Curves1);
	QCurves2.RetrieveTo(Curves2);

	theSubdivided1_->Make(Curves1);
	theSubdivided2_->Make(Curves2);
}

//void AutLib::CadLib::Cad2d_PlanePlaneSubdivide::Perform()
//{
//	Debug_Null_Pointer(thePlane1_);
//	Debug_Null_Pointer(thePlane2_);
//
//	Cad2d_PlanePlaneIntersection Intersection;
//	Intersection.Init(thePlane1_, thePlane2_);
//
//	Intersection.Perform();
//
//	Debug_If_Condition_Message(NOT Intersection.IsDone(), " Intersection not performed");
//
//	Get_Const_Object(Info) = Intersection.Intersections();
//
//	IsDone_ = Standard_True;
//
//	if (NOT Intersection.HasIntersection()) return;
//
//	AreSubdivided_ = Standard_True;
//
//	MapEdgeToQueueOfReal Map;
//	::IntersectionParameters(Intersection.Intersections(), Map);
//
//	TColCad2d_HAry1dOfEdgeOnPlane Edges1;
//	thePlane1_->RetrieveEdgesTo(Edges1);
//
//	TColCad2d_HBasicQueueOfEdgeOnPlane QEdges1;
//	forThose
//	(
//		Index,
//		0, 
//		MaxIndexOf(Edges1)
//	)
//	{
//		Debug_Null_Pointer(Edges1[Index]);
//
//		MapEdgeToQueueOfReal::const_iterator Iter = Map.find(Edges1[Index]);
//		if (Iter EQUAL Map.end())
//		{
//			QEdges1.EnQueue(Edges1[Index]);
//		}
//		else
//		{
//			TColStd_Ary1dOfReal Parameters;
//			Iter->second->RetrieveTo(Parameters);
//
//			Debug_If_Condition_Message(Parameters.IsEmpty(), "The List is empty");
//
//			TColCad2d_HAry1dOfPointOnPlane Points;
//			TColCad2d_HAry1dOfEdgeOnPlane Edges;
//			Edges1[Index]->Split(Parameters, Points, Edges);
//
//			QEdges1.EnQueue(Edges);
//		}
//	}
//
//	TColCad2d_HAry1dOfEdgeOnPlane Edges2;
//	thePlane1_->RetrieveEdgesTo(Edges2);
//
//	TColCad2d_HBasicQueueOfEdgeOnPlane QEdges2;
//	forThose
//	(
//		Index,
//		0,
//		MaxIndexOf(Edges2)
//	)
//	{
//		Debug_Null_Pointer(Edges2[Index]);
//
//		MapEdgeToQueueOfReal::const_iterator Iter = Map.find(Edges2[Index]);
//		if (Iter EQUAL Map.end())
//		{
//			QEdges2.EnQueue(Edges2[Index]);
//		}
//		else
//		{
//			TColStd_Ary1dOfReal Parameters;
//			Iter->second->RetrieveTo(Parameters);
//
//			Debug_If_Condition_Message(Parameters.IsEmpty(), "The List is empty");
//
//			TColCad2d_HAry1dOfPointOnPlane Points;
//			TColCad2d_HAry1dOfEdgeOnPlane Edges;
//			Edges2[Index]->Split(Parameters, Points, Edges);
//
//			QEdges2.EnQueue(Edges);
//		}
//	}
//
//	
//}

void AutLib::CadLib::Cad2d_PlanePlaneSubdivide::ExportToPlt(fstream & File) const
{
	theSubdivided1_->ExportToPlt(File);
	theSubdivided2_->ExportToPlt(File);
}

void AutLib::CadLib::Cad2d_PlanePlaneSubdivide::Clear()
{
	FreePointer(theSubdivided1_);
	FreePointer(theSubdivided2_);
}