#include <Cad3d_WireOnPlaneTools.hxx>

#include <Entity_Box2dTools.hxx>
#include <Geometry_Tools.hxx>
#include <Cad3d_PointOnPlane.hxx>
#include <Cad3d_EdgeOnPlane.hxx>
#include <Cad3d_WireOnPlane.hxx>
#include <Cad3d_PointOnPlaneTools.hxx>
#include <Cad3d_EdgeOnPlaneTools.hxx>
#include <Cad3d_CurveOnPlaneTools.hxx>
#include <TColCad3d_HBasicQueueOfPointOnPlane.hxx>
#include <TColCad3d_HBasicQueueOfWireOnPlane.hxx>
#include <TColCad3d_HAdressAvlTreeOfWireOnPlane.hxx>
#include <TColCad3d_HNumbAvlTreeOfPointOnPlane.hxx>
#include <TColCad3d_HNumbAvlTreeOfEdgeOnPlane.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>

#define GET_DOMAIN_NAME theName;

namespace AutLib
{
	namespace CadLib
	{

		inline static Global_Handle(Cad3d_WireOnPlane) GetItemFrom(TColCad3d_HAdressAvlTreeOfWireOnPlane& theRegister)
		{
			if (theRegister.IsEmpty()) { THROW_STANDARD_EXCEPTION("Empty List"); }

			Global_Handle(Cad3d_WireOnPlane) Item;

			theRegister.Root(Item);
			Try_Exception_Handle_Exit(theRegister.Remove(Item));

			return Item;
		}

		inline static void RegisterWires(Global_Handle(Cad3d_WireOnPlane) InnerCandid, Global_Handle(Cad3d_WireOnPlane) OutterCandid, TColCad3d_HBasicQueueOfWireOnPlane& QInners, Global_Handle(Cad3d_WireOnPlane)& theOutter)
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

		static void TrackBoundaries(TColCad3d_HAdressAvlTreeOfWireOnPlane& theRegister, TColCad3d_HBasicQueueOfWireOnPlane& QInners, Global_Handle(Cad3d_WireOnPlane)& theOutter)
		{
			if (theRegister.IsEmpty()) { return; }

			Global_Handle(Cad3d_WireOnPlane) Outter;
			Global_Handle(Cad3d_WireOnPlane) Inner;

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

Standard_Boolean AutLib::CadLib::Cad3d_WireOnPlaneTools::IdentifyBoundaries(const TColCad3d_HAry1dOfWireOnPlane & theWires, Cad3d_InnerBoundariesOnPlane & theInners, Cad3d_OutterBoundaryOnPlane & theOutter)
{
	if (theWires.IsEmpty()) { THROW_STANDARD_EXCEPTION("Empty List"); }

	TColCad3d_HAdressAvlTreeOfWireOnPlane Register;
	Try_Exception_Handle_Exit(Register.Insert(theWires));

	Global_Handle(Cad3d_WireOnPlane) Outter(0);
	TColCad3d_HBasicQueueOfWireOnPlane QInners;
	::TrackBoundaries(Register, QInners, Outter);

	if (NOT Outter) { return Standard_False; }

	theOutter = Outter;
	QInners.RetrieveTo(theInners);

	Debug_Null_Pointer(Outter);
	Outter->SetOrientation(Cad3d_WireOnPlaneOrientation_CCW);

	forThose
	(
		Index,
		0,
		MaxIndexOf(theInners)
	)
	{
		Debug_Null_Pointer(theInners[Index]);
		theInners[Index]->SetOrientation(Cad3d_WireOnPlaneOrientation_CW);
	}
	return Standard_True;
}

Standard_Boolean AutLib::CadLib::Cad3d_WireOnPlaneTools::CheckRingOrientation
(
	const Cad3d_CurveOnPlane & theCurve,
	const Cad3d_WireOnPlaneOrientationInfo theOrientation
)
{
	Geom_Pnt2d P0 = theCurve.FirstCoord();
	Geom_Pnt2d P1 = theCurve.NormalizedParameterValue(0.33);
	Geom_Pnt2d P2 = theCurve.NormalizedParameterValue(0.66);

	if (theOrientation EQUAL Cad3d_WireOnPlaneOrientation_CCW)
	{
		if (Geometry_Tools::FastOriented(P0, P1, P2) < 0) return Standard_False;
		return Standard_True;
	}

	if (theOrientation EQUAL Cad3d_WireOnPlaneOrientation_CW)
	{
		if (Geometry_Tools::FastOriented(P0, P1, P2) > 0) return Standard_False;
		return Standard_True;
	}

	THROW_STANDARD_EXCEPTION("Invalid Orientation");
}

namespace AutLib
{
	namespace CadLib
	{
		static const Global_Handle(Cad3d_PointOnPlane) NextPoint(const TColCad3d_HNumbAvlTreeOfPointOnPlane& theRegister, const Global_Handle(Cad3d_PointOnPlane) Point)
		{
			TColCad3d_HAry1dOfEdgeOnPlane Edges;
			Point->RetrieveEdgesTo(Edges);

			if (Edges.Size() EQUAL 1 AND Point->IsRingPoint())
			{
				return NULL;
			}

			Debug_If_Condition(Edges.Size() NOT_EQUAL 2);

			const Global_Handle(Cad3d_PointOnPlane) Point1 = Edges[0]->FirstPoint();
			if (Point1 EQUAL Point) Point1 = Edges[0]->LastPoint();

			if (theRegister.IsContains((Global_Handle(Cad3d_PointOnPlane))Point1)) return Point1;

			const Global_Handle(Cad3d_PointOnPlane) Point2 = Edges[1]->FirstPoint();
			if (Point2 EQUAL Point) Point2 = Edges[1]->LastPoint();

			if (theRegister.IsContains((Global_Handle(Cad3d_PointOnPlane))Point2)) return Point2;

			return NULL;
		}

		static TColCad3d_HAry1dOfPointOnPlane TrackWirePoints(TColCad3d_HNumbAvlTreeOfPointOnPlane& theRegister)
		{
			if (theRegister.IsEmpty()) { THROW_STANDARD_EXCEPTION("The list is empty"); }

			Global_Handle(Cad3d_PointOnPlane) Start;
			theRegister.Root(Start);
			Try_Exception_Handle_Exit(theRegister.Remove(Start));

			TColCad3d_HBasicQueueOfPointOnPlane QPoints;
			QPoints.EnQueue(Start);
			while (Start)
			{
				Global_Handle(Cad3d_PointOnPlane) Next = (Global_Handle(Cad3d_PointOnPlane))NextPoint(theRegister, Start);

				if (NOT Next) break;

				Try_Exception_Handle_Exit(theRegister.Remove(Next));

				if (Next) QPoints.EnQueue(Next);
				Start = Next;
			}
			TColCad3d_HAry1dOfPointOnPlane List;
			QPoints.RetrieveTo(List);
			MOVE(List);
		}

		static void SyncEdges(TColCad3d_HAry1dOfEdgeOnPlane& theEdges)
		{
			if (theEdges.Size() < 2) return;
			if (theEdges[0]->FirstPoint() NOT_EQUAL theEdges[1]->LastPoint()) return;

			forThose(Index, 0, MaxIndexOf(theEdges))
			{
				theEdges[Index]->Reverse();
			}
		}

		static TColCad3d_HAry1dOfEdgeOnPlane TrackWireEdges(const TColCad3d_HAry1dOfPointOnPlane& Points)
		{
			TColCad3d_HNumbAvlTreeOfEdgeOnPlane Compact;
			Compact.SetComparable(&Cad3d_EdgeOnPlaneTools::IsLess);

			forThose
			(
				Index,
				0,
				MaxIndexOf(Points)
			)
			{
				Debug_Null_Pointer(Points[Index]);

				TColCad3d_HAry1dOfEdgeOnPlane Edges;
				Points[Index]->RetrieveEdgesTo(Edges);

				Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Edges));
			}
			TColCad3d_HAry1dOfEdgeOnPlane List;
			Compact.RetrieveTo(List);
			MOVE(List);
		}
	}
}

TColCad3d_HAry1dOfWireOnPlane AutLib::CadLib::Cad3d_WireOnPlaneTools::MakeWire
(
	const TColCad3d_HAry1dOfEdgeOnPlane & theEdges,
	const Cad3d_WireOnPlaneOrientationInfo theOrientation
)
{
	if (theEdges.Size() < 1) { THROW_STANDARD_EXCEPTION("Empty list"); }

	TColCad3d_HAry1dOfPointOnPlane Points = Cad3d_EdgeOnPlaneTools::RetrievePointsFrom(theEdges);
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

	TColCad3d_HNumbAvlTreeOfPointOnPlane Register;
	Register.SetComparable(&Cad3d_PointOnPlaneTools::IsLess);

	Try_Exception_Handle_Exit(Register.Insert(Points));

	Standard_Integer K = 0;
	TColCad3d_HBasicQueueOfWireOnPlane QWire;
	while (NOT Register.IsEmpty())
	{
		TColCad3d_HAry1dOfEdgeOnPlane Edges = ::TrackWireEdges(::TrackWirePoints(Register));
		::SyncEdges(Edges);
		QWire.EnQueue(new Cad3d_WireOnPlane(++K, Edges));
	}
	TColCad3d_HAry1dOfWireOnPlane Wires;
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

TColCad3d_HAry1dOfWireOnPlane AutLib::CadLib::Cad3d_WireOnPlaneTools::TrackWires
(
	const TColCad3d_HAry1dOfEdgeOnPlane & theEdges,
	const Standard_String theName
)
{
	if (theEdges.Size() < 1) { THROW_STANDARD_EXCEPTION("Empty list"); }

	/*Open_OutputFile_TecPlot(Plot, "test");
	forThose(Index, 0, MaxIndexOf(theEdges))
		if(theEdges[Index]) theEdges[Index]->ExportToPlt(Plot);*/

	TColCad3d_HAry1dOfPointOnPlane Points = Cad3d_EdgeOnPlaneTools::RetrievePointsFrom(theEdges);
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
			THROW_STANDARD_EXCEPTION("Bad Wire Detected!");
		}
	}

	TColCad3d_HNumbAvlTreeOfPointOnPlane Register;
	Register.SetComparable(&Cad3d_PointOnPlaneTools::IsLess);

	Try_Exception_Handle_Exit(Register.Insert(Points));

	Standard_Integer K = 0;
	TColCad3d_HBasicQueueOfWireOnPlane QWire;
	while (NOT Register.IsEmpty())
	{
		TColCad3d_HAry1dOfEdgeOnPlane Edges = ::TrackWireEdges(::TrackWirePoints(Register));
		::SyncEdges(Edges);
		QWire.EnQueue(new Cad3d_WireOnPlane(++K, Edges));
	}
	TColCad3d_HAry1dOfWireOnPlane Wires;
	QWire.RetrieveTo(Wires);

	MOVE(Wires);
}

TopoDS_Wire AutLib::CadLib::Cad3d_WireOnPlaneTools::Make_TopoDS_Wire
(
	const TColCad3d_HAry1dOfEdgeOnPlane & theEdges,
	const Handle(Geom_Surface)& theSurface
)
{
	BRepBuilderAPI_MakeWire MakeWire;
	forThose
	(
		Index, 
		0, 
		MaxIndexOf(theEdges)
	)
	{
		Debug_Null_Pointer(theEdges[Index]);
		TopoDS_Edge Edge = Cad3d_CurveOnPlaneTools::Get_TopoDS_Edge(*theEdges[Index]->Curve(), theSurface);
		MakeWire.Add(Edge);
	}
	THROW_STANDARD_EXCEPTION_IF(NOT MakeWire.IsDone(), "Invalid Data");
	return MakeWire.Wire();
}