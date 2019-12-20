#include <Cad2d_WireOnPlaneTools.hxx>

#include <Entity_Box2d.hxx>
#include <Entity_Box2dTools.hxx>
#include <Geometry_Tools.hxx>
#include <Entity_EdgeIndexTools.hxx>
#include <Entity_Polygon2d.hxx>
#include <Entity_Polygon2dTools.hxx>
#include <Entity_StaticChain2d.hxx>
#include <Cad2d_PointOnPlane.hxx>
#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_RingOnPlane.hxx>
#include <Cad2d_WireOnPlane.hxx>
#include <Cad2d_PointOnPlaneTools.hxx>
#include <Cad2d_EdgeOnPlaneTools.hxx>
#include <TColCad2d_HAry1dOfPointOnPlane.hxx>
#include <TColCad2d_HBasicQueueOfPointOnPlane.hxx>
#include <TColCad2d_HBasicQueueOfEdgeOnPlane.hxx>
#include <TColCad2d_HBasicQueueOfWireOnPlane.hxx>
#include <TColCad2d_HNumbAvlTreeOfPointOnPlane.hxx>
#include <TColCad2d_HNumbAvlTreeOfEdgeOnPlane.hxx>
#include <TColCad2d_HNumbAvlTreeOfWireOnPlane.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

namespace AutLib
{
	namespace CadLib
	{

		inline static Global_Handle(Cad2d_WireOnPlane) GetItemFrom(TColCad2d_HNumbAvlTreeOfWireOnPlane& theRegister)
		{
			if (theRegister.IsEmpty()) { THROW_STANDARD_EXCEPTION("Empty List"); }

			Global_Handle(Cad2d_WireOnPlane) Item;

			theRegister.Root(Item);
			Try_Exception_Handle_Exit(theRegister.Remove(Item));

			return Item;
		}

		inline static void RegisterWires(Global_Handle(Cad2d_WireOnPlane) InnerCandid, Global_Handle(Cad2d_WireOnPlane) OutterCandid, TColCad2d_HBasicQueueOfWireOnPlane& QInners, Global_Handle(Cad2d_WireOnPlane)& theOutter)
		{
			if (InnerCandid) QInners.EnQueue(InnerCandid);

			if (theOutter)
			{
				if (Entity_Box2dTools::IsBoxInsideBox(OutterCandid->BoundingBox(), theOutter->BoundingBox()))
				{
					QInners.EnQueue(OutterCandid);
				}
				else
				{
					Debug_If_Condition_Message(NOT Entity_Box2dTools::IsBoxInsideBox(theOutter->BoundingBox(), OutterCandid->BoundingBox()), "Conflict Data");

					QInners.EnQueue(theOutter);
					theOutter = OutterCandid;
				}
			}
			else
			{
				theOutter = OutterCandid;
			}
		}

		static void TrackBoundaries(TColCad2d_HNumbAvlTreeOfWireOnPlane& theRegister, TColCad2d_HBasicQueueOfWireOnPlane& QInners, Global_Handle(Cad2d_WireOnPlane)& theOutter)
		{
			if (theRegister.IsEmpty()) { return; }

			Global_Handle(Cad2d_WireOnPlane) Outter;
			Global_Handle(Cad2d_WireOnPlane) Inner;

			Outter = GetItemFrom(theRegister);

			if (theRegister.IsEmpty())
			{
				RegisterWires(NULL, Outter, QInners, theOutter);
				return;
			}

			Inner = GetItemFrom(theRegister);

			const Entity_Box2d& OutterBox = Outter->BoundingBox();
			const Entity_Box2d& InnerBox = Inner->BoundingBox();

			if (Entity_Box2dTools::IsBoxInsideBox(InnerBox, OutterBox))
			{
				RegisterWires(Inner, Outter, QInners, theOutter);
				TrackBoundaries(theRegister, QInners, theOutter);
			}
			else if (Entity_Box2dTools::IsBoxInsideBox(OutterBox, InnerBox))
			{
				RegisterWires(Outter, Inner, QInners, theOutter);
				TrackBoundaries(theRegister, QInners, theOutter);
			}
			else
			{
				QInners.EnQueue(Inner);
				QInners.EnQueue(Outter);
				TrackBoundaries(theRegister, QInners, theOutter);
			}
		}
	}
}

Standard_Boolean AutLib::CadLib::Cad2d_WireOnPlaneTools::IdentifyBoundaries
(
	const TColCad2d_HAry1dOfWireOnPlane & theWires,
	Cad2d_InnerBoundariesOnPlane & theInners,
	Cad2d_OutterBoundaryOnPlane & theOutter
)
{
	if (theWires.IsEmpty()) { THROW_STANDARD_EXCEPTION("Empty List"); }

	TColCad2d_HNumbAvlTreeOfWireOnPlane Register;
	Register.SetComparable(&Cad2d_WireOnPlaneTools::IsLess);

	Try_Exception_Handle_Exit(Register.Insert(theWires));

	Global_Handle(Cad2d_WireOnPlane) Outter(0);
	TColCad2d_HBasicQueueOfWireOnPlane QInners;
	::TrackBoundaries(Register, QInners, Outter);

	if (QInners.Size() + 1 NOT_EQUAL theWires.Size()) { THROW_STANDARD_EXCEPTION("Invalid Data"); }

	if (NOT Outter) { return Standard_False; }

	theOutter = Outter;
	QInners.RetrieveTo(theInners);

	Debug_Null_Pointer(Outter);

	Outter->SetOrientation(Cad2d_WireOnPlaneOrientation_CCW);

	forThose
	(
		Index,
		0, 
		MaxIndexOf(theInners)
	)
	{
		Debug_Null_Pointer(theInners[Index]);
		theInners[Index]->SetOrientation(Cad2d_WireOnPlaneOrientation_CW);
	}
	return Standard_True;
}

//Global_Handle(Cad2d_WireOnPlane) AutLib::CadLib::Cad2d_WireOnPlaneTools::MakeWire
//(
//	const TColCad2d_HAry1dOfEdgeOnPlane & theEdges,
//	const Cad2d_WireOnPlaneOrientationInfo theOrientation
//)
//{
//	if (theEdges.Size() < 1) { THROW_STANDARD_EXCEPTION("Empty list"); }
//	if (theEdges.Size() EQUAL 1)
//	{
//		Debug_Null_Pointer(theEdges[0]);
//		if (NOT Global_DownCast(Cad2d_RingOnPlane, theEdges[0])) { THROW_STANDARD_EXCEPTION("Not closed wire"); }
//
//		Get_Const_Object(Edge) = *theEdges[0];
//
//		if (::CheckRingOrientation(Edge, theOrientation))
//		{
//			theEdges[0]->Reverse();
//		}
//
//		Global_Handle(Cad2d_PointOnPlane) Point = new Cad2d_PointOnPlane(0, Edge.Curve()->FirstCoord());
//		Global_Handle(Cad2d_WireOnPlane) newWire = new Cad2d_WireOnPlane(0, theEdges[0]);
//
//		theEdges[0]->SetWire(newWire);
//	}
//
//	Standard_Integer K = 0;
//	TColGeom_Ary1dOfPnt2d Coords(theEdges.Size() * 2);
//	forThose
//	(
//		Index,
//		0,
//		MaxIndexOf(theEdges)
//	)
//	{
//		Debug_Null_Pointer(theEdges[Index]);
//		Debug_Null_Pointer(theEdges[Index]->Curve());
//
//		if (Global_DownCast(Cad2d_RingOnPlane, theEdges[Index])) { THROW_STANDARD_EXCEPTION("Not a manifold wire"); }
//
//		Get_Const_Object(Curve) = *theEdges[Index]->Curve();
//
//		Coords[K] = Curve.FirstCoord();
//		K++;
//
//		Coords[K] = Curve.LastCoord();
//		K++;
//	}
//
//	Entity_StaticChain2d Chain;
//	Chain.Init(Coords, Entity_EdgeIndexTools::OrderedList(theEdges.Size()));
//
//	Merge_Chain2d Merge;
//	Merge.Import(Chain);
//
//	Merge.Perform();
//
//	Get_Const_Object(Merged) = *Merge.Merged();
//
//	Get_Const_Object(MergedCoords) = Merged.Coords();
//	Get_Const_Object(MergedEdges) = Merged.Edges();
//
//	TColCad2d_HAry1dOfPointOnPlane Pts(MergedCoords.Size());
//	forThose(Index, 0, MaxIndexOf(Pts))
//		Pts[Index] = new Cad2d_PointOnPlane(Index + 1, MergedCoords[Index]);
//
//	forThose(Index, 0, MaxIndexOf(MergedEdges))
//	{
//		Get_Const_Object(Edge) = MergedEdges[Index];
//
//	}
//}

namespace AutLib
{
	namespace CadLib
	{
		static inline const Global_Handle(Cad2d_PointOnPlane) NextPoint(const TColCad2d_HNumbAvlTreeOfPointOnPlane& theRegister, const Global_Handle(Cad2d_PointOnPlane) Point)
		{
			TColCad2d_HAry1dOfEdgeOnPlane Edges;
			Point->RetrieveEdgesTo(Edges);

			if (Edges.Size() EQUAL 1 AND Point->IsRingPoint())
			{
				return NULL;
			}

			Debug_If_Condition(Edges.Size() NOT_EQUAL 2);

			const Global_Handle(Cad2d_PointOnPlane) Point1 = Edges[0]->FirstPoint();
			if (Point1 EQUAL Point) Point1 = Edges[0]->LastPoint();

			if (theRegister.IsContains((Global_Handle(Cad2d_PointOnPlane))Point1)) return Point1;

			const Global_Handle(Cad2d_PointOnPlane) Point2 = Edges[1]->FirstPoint();
			if (Point2 EQUAL Point) Point2 = Edges[1]->LastPoint();

			if (theRegister.IsContains((Global_Handle(Cad2d_PointOnPlane))Point2)) return Point2;

			return NULL;
		}

		static TColCad2d_HAry1dOfPointOnPlane TrackWirePoints(TColCad2d_HNumbAvlTreeOfPointOnPlane& theRegister)
		{
			if (theRegister.IsEmpty()) { THROW_STANDARD_EXCEPTION("The list is empty"); }

			Global_Handle(Cad2d_PointOnPlane) Start;
			theRegister.Root(Start);
			Try_Exception_Handle_Exit(theRegister.Remove(Start));

			TColCad2d_HBasicQueueOfPointOnPlane QPoints;
			QPoints.EnQueue(Start);
			while (Start)
			{
				Global_Handle(Cad2d_PointOnPlane) Next = (Global_Handle(Cad2d_PointOnPlane))NextPoint(theRegister, Start);

				if (NOT Next) break;

				Try_Exception_Handle_Exit(theRegister.Remove(Next));

				if (Next) QPoints.EnQueue(Next);
				Start = Next;
			}
			TColCad2d_HAry1dOfPointOnPlane List;
			QPoints.RetrieveTo(List);
			MOVE(List);
		}

		static void SyncWire(TColCad2d_HAry1dOfEdgeOnPlane& theEdges)
		{
			if (theEdges.Size() <= 2) return;
			if (theEdges[0]->LastPoint() NOT_EQUAL theEdges[1]->FirstPoint())
			{
				theEdges.Reverse();
			}
		}

		static Standard_Boolean CheckWire(const TColCad2d_HAry1dOfEdgeOnPlane& theEdges)
		{
			if (theEdges.Size() <= 1) return Standard_False;
			forThose
			(
				Index,
				0, 
				MaxIndexOf(theEdges) - 1
			)
			{
				if (theEdges[Index]->LastPoint() NOT_EQUAL theEdges[Index + 1]->FirstPoint())
				{
					return Standard_True;
				}
			}
			return Standard_False;
		}

		static TColCad2d_HAry1dOfEdgeOnPlane TrackWireEdges(const TColCad2d_HAry1dOfPointOnPlane& Points)
		{
			TColCad2d_HNumbAvlTreeOfEdgeOnPlane Compact;
			Compact.SetComparable(&Cad2d_EdgeOnPlaneTools::IsLess);

			forThose
			(
				Index, 
				0, 
				MaxIndexOf(Points)
			)
			{
				Debug_Null_Pointer(Points[Index]);

				TColCad2d_HAry1dOfEdgeOnPlane Edges;
				Points[Index]->RetrieveEdgesTo(Edges);

				Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Edges));
			}
			TColCad2d_HAry1dOfEdgeOnPlane List;
			Compact.RetrieveTo(List);
			MOVE(List);
		}
	}
}

Standard_Boolean AutLib::CadLib::Cad2d_WireOnPlaneTools::CheckRingOrientation
(
	const Cad2d_CurveOnPlane & theCurve, 
	const Cad2d_WireOnPlaneOrientationInfo theOrientation
)
{
	Geom_Pnt2d P0 = theCurve.FirstCoord();
	Geom_Pnt2d P1 = theCurve.NormalizedParameterValue(0.33);
	Geom_Pnt2d P2 = theCurve.NormalizedParameterValue(0.66);

	if (theOrientation EQUAL Cad2d_WireOnPlaneOrientation_CCW)
	{
		if (Geometry_Tools::FastOriented(P0, P1, P2) < 0) return Standard_False;
		return Standard_True;
	}

	if (theOrientation EQUAL Cad2d_WireOnPlaneOrientation_CW)
	{
		if (Geometry_Tools::FastOriented(P0, P1, P2) > 0) return Standard_False;
		return Standard_True;
	}

	THROW_STANDARD_EXCEPTION("Invalid Orientation");
}

TColCad2d_HAry1dOfWireOnPlane AutLib::CadLib::Cad2d_WireOnPlaneTools::MakeWire
(
	const TColCad2d_HAry1dOfEdgeOnPlane & theEdges,
	const Cad2d_WireOnPlaneOrientationInfo theOrientation
)
{
	if (theEdges.Size() < 1) { THROW_STANDARD_EXCEPTION("Empty list"); }
	
	TColCad2d_HAry1dOfPointOnPlane Points = Cad2d_EdgeOnPlaneTools::RetrievePointsFrom(theEdges);
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Points)
	)
	{
		Debug_Null_Pointer(Points[Index]);
		if (Points[Index]->NbEdges() NOT_EQUAL 2)
		{
			if (Points[Index]->NbEdges() EQUAL 1 AND Points[Index]->IsRingPoint()) { continue; }
			THROW_STANDARD_EXCEPTION("Invalid Wire");
		}
	}

	TColCad2d_HNumbAvlTreeOfPointOnPlane Register;
	Register.SetComparable(&Cad2d_PointOnPlaneTools::IsLess);

	Try_Exception_Handle_Exit(Register.Insert(Points));

	Standard_Integer K = 0;
	TColCad2d_HBasicQueueOfWireOnPlane QWire;
	while (NOT Register.IsEmpty())
	{
		TColCad2d_HAry1dOfEdgeOnPlane Edges = ::TrackWireEdges(::TrackWirePoints(Register));
		QWire.EnQueue(new Cad2d_WireOnPlane(++K, Edges));
	}
	TColCad2d_HAry1dOfWireOnPlane Wires;
	QWire.RetrieveTo(Wires);

	forThose
	(
		Index, 
		0, 
		MaxIndexOf(Wires)
	)
	{
		Debug_Null_Pointer(Wires[Index]);
		Wires[Index]->SetOrientation(theOrientation);
	}

	MOVE(Wires);
}

TColCad2d_HAry1dOfWireOnPlane AutLib::CadLib::Cad2d_WireOnPlaneTools::TrackWires(const TColCad2d_HAry1dOfEdgeOnPlane & theEdges)
{
	if (theEdges.Size() < 1) { THROW_STANDARD_EXCEPTION("Empty list"); }

	TColCad2d_HAry1dOfPointOnPlane Points = Cad2d_EdgeOnPlaneTools::RetrievePointsFrom(theEdges);
	forThose
	(
		Index,
		0,
		MaxIndexOf(Points)
	)
	{
		Debug_Null_Pointer(Points[Index]);

		if (Points[Index]->NbEdges() NOT_EQUAL 2)
		{
			if (Points[Index]->NbEdges() EQUAL 1 AND Points[Index]->IsRingPoint()) { continue; }
			THROW_STANDARD_EXCEPTION("Invalid Wire");
		}
	}

	TColCad2d_HNumbAvlTreeOfPointOnPlane Register;
	Register.SetComparable(&Cad2d_PointOnPlaneTools::IsLess);

	Try_Exception_Handle_Exit(Register.Insert(Points));

	Standard_Integer K = 0;
	TColCad2d_HBasicQueueOfWireOnPlane QWire;

	while (NOT Register.IsEmpty())
	{
		TColCad2d_HAry1dOfEdgeOnPlane Edges = ::TrackWireEdges(::TrackWirePoints(Register));

		/*::SyncWire(Edges);
		if (::CheckWire(Edges))
		{
			THROW_STANDARD_EXCEPTION("Something Wrong from wire structure");
		}*/
		QWire.EnQueue(new Cad2d_WireOnPlane(++K, Edges));
	}
	TColCad2d_HAry1dOfWireOnPlane Wires;
	QWire.RetrieveTo(Wires);
	MOVE(Wires);
}

//Global_Handle(Cad2d_WireOnPlane) AutLib::CadLib::Cad2d_WireOnPlaneTools::SplitEdgeOnWire
//(
//	const Standard_Real theParameter, 
//	const Cad2d_EdgeOnPlane & theEdge
//)
//{
//	if (NOT theEdge.Wire()) { THROW_STANDARD_EXCEPTION("Null Wire"); }
//
//	Get_Const_Object(Wire) = *theEdge.Wire();
//	Get_Const_Object(Edges) = Wire.Edges();
//
//	Standard_Integer MaxEdgeIndex = Wire.MaxEdgeIndex();
//	Standard_Integer MaxPointIndex = Wire.MaxPointIndex();
//
//	TColCad2d_HBasicQueueOfEdgeOnPlane QEdges;
//	forThose
//	(
//		Index,
//		0,
//		MaxIndexOf(Edges)
//	)
//	{
//		Debug_Null_Pointer(Edges[Index]);
//
//		if (Edges[Index] NOT_EQUAL &theEdge)
//			QEdges.EnQueue(Edges[Index]);
//		else
//		{
//			Global_Handle(Cad2d_EdgeOnPlane) Edge1 = new Cad2d_EdgeOnPlane;
//			Global_Handle(Cad2d_EdgeOnPlane) Edge2 = new Cad2d_EdgeOnPlane;
//
//			Global_Handle(Cad2d_PointOnPlane) Point = new Cad2d_PointOnPlane;
//
//			Point->SetIndex(MaxPointIndex + 1);
//
//			Edges[Index]->Split(theParameter, Point, Edge1, Edge2);
//
//			Edge1->SetIndex(MaxEdgeIndex + 1);
//			Edge2->SetIndex(MaxEdgeIndex + 2);
//
//			QEdges.EnQueue(Edge1);
//			QEdges.EnQueue(Edge2);
//		}
//	}
//
//	TColCad2d_HAry1dOfEdgeOnPlane newEdges;
//	QEdges.RetrieveTo(newEdges);
//
//	return new Cad2d_WireOnPlane(0, newEdges);
//}

Global_Handle(Cad2d_WireOnPlane) AutLib::CadLib::Cad2d_WireOnPlaneTools::SplitEdgeOnWire
(
	const TColStd_Ary1dOfReal & theParameters, 
	const Cad2d_EdgeOnPlane & theEdge
)
{
	if (NOT theEdge.Wire()) { THROW_STANDARD_EXCEPTION("Null Wire"); }

	Get_Const_Object(Wire) = *theEdge.Wire();
	Get_Const_Object(Edges) = Wire.Edges();

	TColCad2d_HAry1dOfEdgeOnPlane newEdges;
	TColCad2d_HAry1dOfPointOnPlane Points;

	theEdge.Split(theParameters, Points, newEdges);

	TColCad2d_HBasicQueueOfEdgeOnPlane QEdges;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		if (Edges[Index] NOT_EQUAL &theEdge)
			QEdges.EnQueue(Edges[Index]);
		else
		{
			QEdges.EnQueue(newEdges);
		}
	}
	QEdges.RetrieveTo(newEdges);

	return new Cad2d_WireOnPlane(Wire.Index(), newEdges);
}