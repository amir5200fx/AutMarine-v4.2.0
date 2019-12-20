#include <Cad2d_PlaneTools.hxx>

#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_Plane.hxx>
#include <TColStd_Ary1dOfInteger.hxx>
#include <TColCad2d_HBasicQueueOfCurveOnPlane.hxx>

using namespace AutLib;
using namespace CadLib;

#include <BRep_Tool.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>
#include <TopExp_Explorer.hxx>
#include <ShapeFix_Wire.hxx>
#include <ShapeAnalysis_Wire.hxx>
#include <ShapeAnalysis_WireOrder.hxx>

Global_Handle(Cad2d_Plane) AutLib::CadLib::Cad2d_PlaneTools::GetPlane
(
	const TopoDS_Face & theSurface,
	const Standard_Real theTolerance,
	const Standard_Boolean theVerbose
)
{
	TColCad2d_HBasicQueueOfCurveOnPlane QCurves;
	Standard_Integer CurveIndex = 0;

	for (TopExp_Explorer Explorer(theSurface, TopAbs_WIRE); Explorer.More(); Explorer.Next())
	{
		TopoDS_Wire Wire = TopoDS::Wire(Explorer.Current());

		ShapeFix_Wire SFWF(Wire, theSurface, theTolerance);

		ShapeAnalysis_WireOrder WireOrder;
		ShapeAnalysis_Wire Analysis(Wire, theSurface, theTolerance);
		Analysis.Perform();

		if (theVerbose AND Analysis.CheckOrder())
		{
			cout << " The Wire Need ReOrder" << endl;
		}

		if (theVerbose AND Analysis.CheckClosed(theTolerance))
		{
			cout << " The Wire is not CLOSED: Need to be repaired" << endl;
		}

		if (Analysis.CheckSmall(theTolerance))
		{
			if (theVerbose) cout << "Small Edge detected" << endl;
			if (SFWF.FixSmall(Standard_False, theTolerance))
			{
				if (theVerbose) cout << "Small Edge Removed" << endl;
				//SFWF.FixReorder();
			}
		}
		SFWF.FixReorder();
		SFWF.Perform();
		Wire = SFWF.Wire();

		TColStd_Ary1dOfInteger Order(Analysis.NbEdges());
		Order.Init(1);

		//Analysis.CheckOrder(WireOrder, Standard_True, Standard_False);

		if (Analysis.CheckOrder(WireOrder, Standard_True, Standard_False))
		{
			forThose(Index, 0, MaxIndexOf(Order))
			{
				Standard_Integer Value = WireOrder.Ordered(Index + 1);
				Order[ABS(Value) - 1] = Value;
			}
		}

		Standard_Integer K = 0;

		for (TopExp_Explorer Explorer1(Wire, TopAbs_EDGE); Explorer1.More(); Explorer1.Next())
		{
			TopoDS_Edge Edge = TopoDS::Edge(Explorer1.Current());

			//cout << " Orientation = " << Edge.Orientation() << "  " << TopAbs_REVERSED << endl;


			TopLoc_Location Loc;
			Standard_Real First, Last;
			Handle(Geom2d_Curve) PCurve = BRep_Tool::CurveOnSurface(Edge, theSurface, First, Last);
			Handle(Geom2d_Curve) CopyOfPCurve = Handle(Geom2d_Curve)::DownCast(PCurve->Copy());

			Debug_Null_Pointer(CopyOfPCurve);

			if (Order[K] < 0)
			{
				CopyOfPCurve->Reverse();
				Standard_Real Temp = Last;
				Last = CopyOfPCurve->ReversedParameter(First);
				First = CopyOfPCurve->ReversedParameter(Temp);
			}

			K++;

			if (Edge.Orientation() EQUAL TopAbs_REVERSED)
			{
				CopyOfPCurve->Reverse();
				Standard_Real Temp = Last;
				Last = CopyOfPCurve->ReversedParameter(First);
				First = CopyOfPCurve->ReversedParameter(Temp);
			}

			Global_Handle(Cad2d_CurveOnPlane) CurveOnPlane = new Cad2d_CurveOnPlane(First, Last, CopyOfPCurve);
			QCurves.EnQueue(CurveOnPlane);
		}
	}

	TColCad2d_HAry1dOfCurveOnPlane Curves;
	QCurves.RetrieveTo(Curves);

	TColCad2d_HBasicQueueOfCurveOnPlane RemovedZeroLength;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Curves)
	)
	{
		Standard_Real U1 = Curves[Index]->FirstParameter();
		Standard_Real U2 = Curves[Index]->LastParameter();

		Geom_Pnt2d P1 = Curves[Index]->Curve()->Value(U1);
		Geom_Pnt2d P2 = Curves[Index]->Curve()->Value(U2);
		Geom_Pnt2d P3 = Curves[Index]->Curve()->Value(0.5*(U1 + U2));

		if (Distance(P1, P2) > EPS12 OR Distance(P1, P3) > EPS12)
		{
			RemovedZeroLength.EnQueue(Curves[Index]);
			continue;
		}
	}
	RemovedZeroLength.RetrieveTo(Curves);

	Global_Handle(Cad2d_Plane) Plane = new Cad2d_Plane;
	Try_Exception_Handle_Exit(Plane->Make(Curves));

	return Plane;
}